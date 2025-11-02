#include <iostream>
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#include <string>
#include <cmath>
#include <locale>
#include <cstdint>
#include <cstdlib>
#include <conio.h>

using namespace std;

// Структура для установки локали
struct SetLocale {
    SetLocale() {
        try {
            locale::global(locale(""));
        } catch (const runtime_error&) {
            locale::global(locale("C"));
        }
    }
} setLocale;

// Функция вывода ошибок
void PrintError(const wstring& message) {
    DWORD error = GetLastError();
    LPWSTR lpMsgBuf = nullptr;

    FormatMessageW(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        error,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPWSTR)&lpMsgBuf,
        0,
        NULL
    );

    wcerr << message << L": " << (lpMsgBuf ? lpMsgBuf : L"Unknown error") << endl;

    if (lpMsgBuf) LocalFree(lpMsgBuf);
}

// Функция расчета CRC16
uint16_t crc16_ccitt(const uint8_t* data, int length) {
    uint16_t crc = 0xFFFF;
    
    for (int i = 1; i < length; ++i) {
        crc ^= static_cast<uint16_t>(data[i]) << 8;
        
        for (int j = 0; j < 8; ++j) {
            crc = (crc & 0x8000) ? ((crc << 1) ^ 0x1021) : (crc << 1);
        }
    }
    
    return crc;
}

// Состояние управления с клавиатуры
struct KeyboardState {
    bool A, B, X, Y;
    bool LB, RB;
    bool LeftThumb, RightThumb;  
    bool Start, Back;
    bool DPad_Up, DPad_Down, DPad_Left, DPad_Right;

    int16_t LeftThumbX, LeftThumbY;
    int16_t RightThumbX, RightThumbY;
    uint8_t LeftTrigger, RightTrigger;
};

// Получение состояния клавиатуры
bool GetKeyboardState(KeyboardState& state) {
    // Обнуление состояния
    ZeroMemory(&state, sizeof(KeyboardState));
    
    // Основные кнопки управления (WASD и другие)
    state.DPad_Up = GetAsyncKeyState('W') & 0x8000;     // W - вперед
    state.DPad_Down = GetAsyncKeyState('S') & 0x8000;   // S - назад  
    state.DPad_Left = GetAsyncKeyState('A') & 0x8000;   // A - влево
    state.DPad_Right = GetAsyncKeyState('D') & 0x8000;  // D - вправо
    
    // Кнопки действия
    state.A = GetAsyncKeyState('J') & 0x8000;      // J - кнопка A
    state.B = GetAsyncKeyState('K') & 0x8000;      // K - кнопка B  
    state.X = GetAsyncKeyState('U') & 0x8000;      // U - кнопка X
    state.Y = GetAsyncKeyState('I') & 0x8000;      // I - кнопка Y
    
    // Плечевые кнопки
    state.LB = GetAsyncKeyState('Q') & 0x8000;     // Q - левая плечевая
    state.RB = GetAsyncKeyState('E') & 0x8000;     // E - правая плечевая
    
    // Стики (нажатие)
    state.LeftThumb = GetAsyncKeyState('F') & 0x8000;   // F - левый стик
    state.RightThumb = GetAsyncKeyState('G') & 0x8000;  // G - правый стик
    
    // Сервисные кнопки
    state.Start = GetAsyncKeyState(VK_RETURN) & 0x8000;  // Enter - Start
    state.Back = GetAsyncKeyState(VK_BACK) & 0x8000;     // Backspace - Back
    
    // Триггеры
    state.LeftTrigger = GetAsyncKeyState('Z') & 0x8000 ? 255 : 0;  // Z - левый триггер
    state.RightTrigger = GetAsyncKeyState('C') & 0x8000 ? 255 : 0; // C - правый триггер
    
    // Эмуляция аналоговых стиков на основе цифрового ввода
    const int16_t MAX_STICK_VALUE = 32767;
    
    // Левый стик (на основе WASD)
    if (state.DPad_Left) state.LeftThumbX = -MAX_STICK_VALUE;
    else if (state.DPad_Right) state.LeftThumbX = MAX_STICK_VALUE;
    else state.LeftThumbX = 0;
    
    if (state.DPad_Up) state.LeftThumbY = MAX_STICK_VALUE;
    else if (state.DPad_Down) state.LeftThumbY = -MAX_STICK_VALUE;
    else state.LeftThumbY = 0;
    
    // Правый стик (на основе стрелок)
    if (GetAsyncKeyState(VK_LEFT) & 0x8000) state.RightThumbX = -MAX_STICK_VALUE;
    else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) state.RightThumbX = MAX_STICK_VALUE;
    else state.RightThumbX = 0;
    
    if (GetAsyncKeyState(VK_UP) & 0x8000) state.RightThumbY = MAX_STICK_VALUE;
    else if (GetAsyncKeyState(VK_DOWN) & 0x8000) state.RightThumbY = -MAX_STICK_VALUE;
    else state.RightThumbY = 0;

    return true;
}

int main() {
    // Настройка консоли
    _setmode(_fileno(stdout), _O_U8TEXT);
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    // Открытие COM-порта
    HANDLE hSerial = CreateFileW(
        L"\\\\.\\COM1",
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        FILE_FLAG_OVERLAPPED,
        NULL
    );

    if (hSerial == INVALID_HANDLE_VALUE) {
        PrintError(L"Ошибка открытия COM-порта");
        return 1;
    }

    // Настройка параметров порта
    DCB dcb = {0};
    dcb.DCBlength = sizeof(DCB);
    if (!GetCommState(hSerial, &dcb)) {
        PrintError(L"Ошибка получения параметров порта");
        CloseHandle(hSerial);
        return 1;
    }

    dcb.BaudRate = CBR_19200;
    dcb.ByteSize = 8;
    dcb.Parity = NOPARITY;
    dcb.StopBits = ONESTOPBIT;

    if (!SetCommState(hSerial, &dcb)) {
        PrintError(L"Ошибка настройки параметров порта");
        CloseHandle(hSerial);
        return 1;
    }

    // Подготовка структуры для асинхронной записи
    OVERLAPPED ov = {0};
    ov.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    if (!ov.hEvent) {
        PrintError(L"Ошибка создания события");
        CloseHandle(hSerial);
        return 1;
    }

    wcout << L"Программа управления с клавиатуры запущена.\n";
    wcout << L"Управление:\n";
    wcout << L"WASD - основное движение (DPad)\n";
    wcout << L"Стрелки - правый стик\n";
    wcout << L"J,K,U,I - кнопки A,B,X,Y\n";
    wcout << L"Q,E - плечевые кнопки LB,RB\n";
    wcout << L"Z,C - триггеры\n";
    wcout << L"F,G - нажатие стиков\n";
    wcout << L"Enter - Start, Backspace - Back\n";
    wcout << L"Нажмите ESC для выхода...\n";

    // Главный цикл
    while (true) {
        if (_kbhit() && _getch() == 27) break; // Выход по ESC

        KeyboardState state;
        GetKeyboardState(state);

        // Формирование пакета данных
        uint8_t buffer[13] = {0};

        buffer[0] = 0x0A; // Заголовок пакета

        // Байт 1: основные кнопки
        buffer[1] |= state.A << 7;          // кнопка А
        buffer[1] |= state.B << 6;          // кнопка В
        buffer[1] |= state.X << 5;          // кнопка Х
        buffer[1] |= state.Y << 4;          // кнопка Y
        buffer[1] |= state.DPad_Up << 3;    // DPad вверх
        buffer[1] |= state.DPad_Down << 2;  // DPad вниз
        buffer[1] |= state.DPad_Left << 1;  // DPad влево
        buffer[1] |= state.DPad_Right;      // DPad вправо

        // Стики
        buffer[2] = (state.LeftThumbX >> 8) & 0xFF;     // левый стик Х
        buffer[3] = state.LeftThumbX & 0xFF;            // левый стик Х (младшие)
        buffer[4] = (state.LeftThumbY >> 8) & 0xFF;     // левый стик Y
        buffer[5] = state.LeftThumbY & 0xFF;            // левый стик Y (младшие)
                                                    
        buffer[6] = (state.RightThumbX >> 8) & 0xFF;    // правый стик Х
        buffer[7] = state.RightThumbX & 0xFF;           // правый стик Х (младшие)
        buffer[8] = (state.RightThumbY >> 8) & 0xFF;    // правый стик Y
        buffer[9] = state.RightThumbY & 0xFF;           // правый стик Y (младшие)

        // Байт 10: дополнительные кнопки
        buffer[10] |= state.LeftThumb << 7;
        buffer[10] |= state.RightThumb << 6;
        buffer[10] |= state.LB << 5;
        buffer[10] |= state.RB << 4;
        buffer[10] |= (state.LeftTrigger > 0) << 3;
        buffer[10] |= (state.RightTrigger > 0) << 2;
        buffer[10] |= state.Start << 1;
        buffer[10] |= state.Back;
		
        // Расчет CRC
        uint16_t crc = crc16_ccitt(buffer, 11);
        buffer[11] = (crc >> 8) & 0xFF;
        buffer[12] = crc & 0xFF;

        // Отправка данных
        DWORD bytesWritten;
        if (!WriteFile(hSerial, buffer, sizeof(buffer), &bytesWritten, &ov)) {
            if (GetLastError() != ERROR_IO_PENDING) {
                PrintError(L"Ошибка отправки данных");
                break;
            }
            WaitForSingleObject(ov.hEvent, INFINITE);
            ResetEvent(ov.hEvent);
        }

        Sleep(30); // Задержка для следующего опроса
    }

    // Очистка ресурсов
    CloseHandle(ov.hEvent);
    CloseHandle(hSerial);
    wcout << L"Программа завершена.\n";
    return 0;
}