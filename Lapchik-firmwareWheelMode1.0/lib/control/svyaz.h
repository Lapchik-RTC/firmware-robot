#pragma once
#include <Arduino.h>

#define SERIAL1_RX_BUFFER_SIZE 256

struct GamePad {
    // Кнопки и D-Pad
    bool A, B, X, Y;
    bool DPad_Up, DPad_Down, DPad_Left, DPad_Right;
    
    // Стики
    int16_t LeftThumbX;
    int16_t LeftThumbY;
    int16_t RightThumbX;
    int16_t RightThumbY;
    
    // Дополнительные кнопки
    bool LeftThumbPress;
    bool RightThumbPress;
    bool LB;
    bool RB;
    bool LeftTrigger;
    bool RightTrigger;
    bool Start;
    bool Back;
    
    // Статус ошибки
    bool CRC_Error;
};

GamePad gamePad;

uint16_t crc16_ccitt(const uint8_t* gamePad, uint8_t length) {
    uint16_t crc = 0xFFFF;
    for (uint8_t i = 0; i < length; ++i) {
        crc ^= (uint16_t)gamePad[i] << 8;
        for (uint8_t j = 0; j < 8; ++j) {
            crc = crc & 0x8000 ? (crc << 1) ^ 0x1021 : crc << 1;
        }
    }
    return crc;
}

bool readPacket() {
    static uint8_t packet[13];
    static uint8_t index = 0;
    static unsigned long lastByteTime = 0;
    
    while (Serial1.available()) {
        uint8_t b = Serial1.read();
        // Serial.print("читаем");
        
        // Сброс при длительном простое
        if (millis() - lastByteTime > 50) index = 0;
        lastByteTime = millis();
        
        // Поиск стартового байта
        if (index == 0 && b != 0x0A) continue;
        
        packet[index++] = b;
        
        // Полный пакет
        if (index >= 13) {
            index = 0;
            // Serial.print(packet[1]);
            // Проверка CRC (байты 1-11)
            uint16_t receivedCrc = (packet[11] << 8) | packet[12];
            uint16_t calculatedCrc = crc16_ccitt(&packet[1], 10);
            
            if (receivedCrc != calculatedCrc) {
                gamePad.CRC_Error = true;
                return false;
            }
            
            // Распаковка данных
            gamePad.A          = packet[1] & 0x40;
            gamePad.B          = packet[1] & 0x80;
            gamePad.X          = packet[1] & 0x10;
            gamePad.Y          = packet[1] & 0x20;
            gamePad.DPad_Up    = packet[1] & 0x08;
            gamePad.DPad_Down  = packet[1] & 0x04;
            gamePad.DPad_Left  = packet[1] & 0x02;
            gamePad.DPad_Right = packet[1] & 0x01;
            
            gamePad.LeftThumbX  = (packet[2] << 8) | packet[3];
            gamePad.LeftThumbY  = (packet[4] << 8) | packet[5];
            gamePad.RightThumbX = (packet[6] << 8) | packet[7];
            gamePad.RightThumbY = (packet[8] << 8) | packet[9];
            
            gamePad.LeftThumbPress  = packet[10] & 0x80;
            gamePad.RightThumbPress = packet[10] & 0x40;
            gamePad.LB              = packet[10] & 0x20;
            gamePad.RB              = packet[10] & 0x10;
            // gamePad.LeftTrigger     = packet[10] & 0x08 ? 255 : 0;
            gamePad.LeftTrigger     = packet[10] & 0x08;
            gamePad.RightTrigger    = packet[10] & 0x04;
            gamePad.Start           = packet[10] & 0x02;
            gamePad.Back            = packet[10] & 0x01;
            
            gamePad.CRC_Error = false;
            return true;
        }
    }
    // Serial.print("NO");
    return false;
}

void printPacket2() {
  // Serial.println("Valid packet:");
  if (readPacket()) {
    Serial.println("Valid packet:");
    Serial.print("LeftThumbX: "); Serial.print(gamePad.LeftThumbX);
    Serial.print(" LeftThumbY: "); Serial.print(gamePad.LeftThumbY);
    if(gamePad.LeftThumbPress) Serial.println("  Левый стик нажат! ");
    else Serial.println("  Левый НЕ стик нажат! ");

    Serial.print("RightThumbX: "); Serial.print(gamePad.RightThumbX);
    Serial.print(" RightThumbY: "); Serial.print(gamePad.RightThumbY);
    if(gamePad.RightThumbPress) Serial.println("  Правый стик нажат! ");
    else Serial.println("  Правый НЕ стик нажат! ");
    Serial.print("Buttons: ");
    if(gamePad.A) Serial.print("A ");
    if(gamePad.B) Serial.print("B ");
    if(gamePad.X) Serial.print("X ");
    if(gamePad.Y) Serial.print("Y; ");
    if(gamePad.DPad_Up) Serial.print("DPad_Up ");
    if(gamePad.DPad_Down) Serial.print("DPad_Down ");
    if(gamePad.DPad_Left) Serial.print("DPad_Left ");
    if(gamePad.DPad_Right) Serial.println("DPad_Right ");
  } else if(gamePad.CRC_Error) {
    Serial.println("CRC Error!");
  }
// delay(20);
}


void printPacket() {
    if (readPacket()) {
      // Serial.println("Valid packet:");
      // Serial.print("LeftThumbX: "); Serial.print(gamePad.LeftThumbX);
      // Serial.print(" LeftThumbY: "); Serial.print(gamePad.LeftThumbY);
      // if(gamePad.LeftThumbPress) Serial.println("  Левый стик нажат! ");
      // else Serial.println("  Левый НЕ стик нажат! ");
  
      Serial.print("RightThumbX: "); Serial.print(gamePad.RightThumbX);
      Serial.print(" RightThumbY: "); Serial.print(gamePad.RightThumbY);
      // if(gamePad.RightThumbPress) Serial.println("  Правый стик нажат! ");
      // else Serial.println("  Правый НЕ стик нажат! ");
      // Serial.print("Buttons: ");
      // if(gamePad.A) Serial.print("A ");
      // if(gamePad.B) Serial.print("B ");
      // if(gamePad.X) Serial.print("X ");
      // if(gamePad.Y) Serial.print("Y; ");
      // if(gamePad.DPad_Up) Serial.print("DPad_Up ");
      // if(gamePad.DPad_Down) Serial.print("DPad_Down ");
      // if(gamePad.DPad_Left) Serial.print("DPad_Left ");
      // if(gamePad.DPad_Right) Serial.println("DPad_Right ");
    } else {
      Serial.println("CRC Error!");
    }
  // delay(20);
  }
/////////////////////////   Проверка конкретных кнопок   /////////////////////////

int luft = 20000;
// enum RecState
// {
//   normal = 0,
//   kringe = 1
// };

bool nado_rabotat() {
  if (
    (gamePad.RightThumbY >= -luft) && (gamePad.RightThumbY <= luft) &&
    (gamePad.RightThumbX >= -luft) && (gamePad.RightThumbX <= luft) &&
    (!gamePad.B) && (!gamePad.A) && (!gamePad.X) && (!gamePad.Y) &&
    (!gamePad.DPad_Up)

  ) {  
    
    return false;
  }
  else {
    return true;
  }
} 

bool calibr()
{
  if( gamePad.A )
    {      
        return 1;
    }
    else
    {
        return 0;
    }
}

bool vpered() {
    if( gamePad.RightThumbY >= luft)
    {
        return 1;
    }
    else
    {
        return 0;
    }
  }

  bool nazad() {
    if( gamePad.RightThumbY <= -luft)
    {
        return 1;
    }
    else
    {
        return 0;
    }
  }

//   int invertThumbX = 1;
  
  bool vpravo() {
    if( gamePad.RightThumbX >= luft)
    {
        return 1;
    }
    else
    {
        return 0;
    }
  }
  
  bool shift()
  {
    if( gamePad.LB )
    {
      
        return 1;
    }
    else
    {
        return 0;
    }
  }
  bool silentShift()
  {
    if( gamePad.RB )
    {
        return 1;
    }
    else
    {
        return 0;
    }
  }


  bool vlevo() {
    if(gamePad.RightThumbX <= -luft)
    {
        return 1;
    }
    else
    {
        return 0;
    }
  }

  bool ladmode()
  {
    if( gamePad.Y )
    {
      
        return 1;
    }
    else
    {
        return 0;
    }
  }
  bool delsec_N()
  {
    if( gamePad.X )
    {
      
        return 1;
    }
    else
    {
        return 0;
    }
  }