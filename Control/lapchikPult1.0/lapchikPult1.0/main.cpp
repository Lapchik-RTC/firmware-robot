#include <iostream>
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#include <string>
#include <XInput.h>
#include <cmath>
#include <locale>
#include <cstdint>
#include <cstdlib>
#include <conio.h>

using namespace std;

#pragma comment(lib, "XInput.lib")

// ��������� ��� ��������� ������
struct SetLocale {
    SetLocale() {
        try {
            locale::global(locale(""));
        }
        catch (const runtime_error&) {
            locale::global(locale("C"));
        }
    }
} setLocale;

// ������� ������ ������
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

// ������� ������� CRC16
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

// ��������� ��������
struct GamepadState {
    bool A, B, X, Y;
    bool LB, RB;
    bool LeftThumb, RightThumb;
    bool Start, Back;
    bool DPad_Up, DPad_Down, DPad_Left, DPad_Right;

    int16_t LeftThumbX, LeftThumbY;
    int16_t RightThumbX, RightThumbY;
    uint8_t LeftTrigger, RightTrigger;
};

// ������������ �������� ������
int16_t normalizeStickValue(SHORT rawValue, SHORT deadZone = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) {
    if (abs(rawValue) < deadZone) return 0;
    return rawValue;
}

// ��������� ��������� ��������
bool GetGamepadState(int controllerIndex, GamepadState& state) {
    XINPUT_STATE xState;
    ZeroMemory(&xState, sizeof(XINPUT_STATE));

    if (XInputGetState(controllerIndex, &xState) != ERROR_SUCCESS)
        return false;

    // ������
    state.A = xState.Gamepad.wButtons & XINPUT_GAMEPAD_A;
    state.B = xState.Gamepad.wButtons & XINPUT_GAMEPAD_B;
    state.X = xState.Gamepad.wButtons & XINPUT_GAMEPAD_X;
    state.Y = xState.Gamepad.wButtons & XINPUT_GAMEPAD_Y;
    state.LB = xState.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER;
    state.RB = xState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER;
    state.LeftThumb = xState.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB;
    state.RightThumb = xState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB;
    state.Start = xState.Gamepad.wButtons & XINPUT_GAMEPAD_START;
    state.Back = xState.Gamepad.wButtons & XINPUT_GAMEPAD_BACK;

    // D-Pad
    state.DPad_Up = xState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP;
    state.DPad_Down = xState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN;
    state.DPad_Left = xState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT;
    state.DPad_Right = xState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT;

    // �����
    state.LeftThumbX = normalizeStickValue(xState.Gamepad.sThumbLX);
    state.LeftThumbY = normalizeStickValue(xState.Gamepad.sThumbLY);
    state.RightThumbX = normalizeStickValue(xState.Gamepad.sThumbRX);
    state.RightThumbY = normalizeStickValue(xState.Gamepad.sThumbRY);

    // ��������
    state.LeftTrigger = xState.Gamepad.bLeftTrigger;
    state.RightTrigger = xState.Gamepad.bRightTrigger;

    return true;
}

int main() {
    // ��������� �������
    _setmode(_fileno(stdout), _O_U8TEXT);
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    // ������������� XInput
    HMODULE hXInput = LoadLibraryW(L"XInput1_4.dll");
    if (!hXInput) hXInput = LoadLibraryW(L"XInput9_1_0.dll");
    if (!hXInput) {
        PrintError(L"������ �������� XInput");
        return 1;
    }

    // �������� COM-�����
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
        PrintError(L"������ �������� COM-�����");
        FreeLibrary(hXInput);
        return 1;
    }

    // ��������� ���������� �����
    DCB dcb = { 0 };
    dcb.DCBlength = sizeof(DCB);
    if (!GetCommState(hSerial, &dcb)) {
        PrintError(L"������ ��������� ���������� �����");
        CloseHandle(hSerial);
        FreeLibrary(hXInput);
        return 1;
    }

    dcb.BaudRate = CBR_19200;
    dcb.ByteSize = 8;
    dcb.Parity = NOPARITY;
    dcb.StopBits = ONESTOPBIT;

    if (!SetCommState(hSerial, &dcb)) {
        PrintError(L"������ ��������� ���������� �����");
        CloseHandle(hSerial);
        FreeLibrary(hXInput);
        return 1;
    }

    // ���������� ��������� ��� ����������� ������
    OVERLAPPED ov = { 0 };
    ov.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    if (!ov.hEvent) {
        PrintError(L"������ �������� �������");
        CloseHandle(hSerial);
        FreeLibrary(hXInput);
        return 1;
    }

    wcout << L"��������� ��������. ������� ESC ��� ������...\n";

    // ������� ����
    while (true) {
        if (_kbhit() && _getch() == 27) break; // ����� �� ESC

        GamepadState state;
        if (!GetGamepadState(0, state)) {
            wcout << L"������� �� ���������!\n";
            Sleep(1000);
            continue;
        }

        // ������������ ������ ������
        uint8_t buffer[13] = { 0 };

        buffer[0] = 0x0A; // ��������� ������

        // ���� 1: �������� ������
        buffer[1] |= state.A << 7;          //������ �
        buffer[1] |= state.B << 6;          //������ �
        buffer[1] |= state.X << 5;          //������ �
        buffer[1] |= state.Y << 4;          //������ Y
        buffer[1] |= state.DPad_Up << 3;    // DPad �����
        buffer[1] |= state.DPad_Down << 2;  // DPad ����
        buffer[1] |= state.DPad_Left << 1;  // D Pad �����
        buffer[1] |= state.DPad_Right;      // D Pad ������

        // �����
        buffer[2] = (state.LeftThumbX >> 8) & 0xFF;     //  ����� ���� �
        buffer[3] = state.LeftThumbX & 0xFF;            //  ����� ���� � (�������)
        buffer[4] = (state.LeftThumbY >> 8) & 0xFF;     //  ����� ���� Y
        buffer[5] = state.LeftThumbY & 0xFF;            //  ����� ���� Y (�������)

        buffer[6] = (state.RightThumbX >> 8) & 0xFF;    //  ������ ���� �
        buffer[7] = state.RightThumbX & 0xFF;           //  ������ ���� � (�������)
        buffer[8] = (state.RightThumbY >> 8) & 0xFF;    //  ������ ���� Y
        buffer[9] = state.RightThumbY & 0xFF;           //  ������ ���� Y (�������)

        // ���� 10: �������������� ������
        buffer[10] |= state.LeftThumb << 7;
        buffer[10] |= state.RightThumb << 6;
        buffer[10] |= state.LB << 5;
        buffer[10] |= state.RB << 4;
        buffer[10] |= (state.LeftTrigger > 0) << 3;
        buffer[10] |= (state.RightTrigger > 0) << 2;
        buffer[10] |= state.Start << 1;
        buffer[10] |= state.Back;

        // ������ CRC
        uint16_t crc = crc16_ccitt(buffer, 11);
        buffer[11] = (crc >> 8) & 0xFF;
        buffer[12] = crc & 0xFF;

        // �������� ������
        DWORD bytesWritten;
        if (!WriteFile(hSerial, buffer, sizeof(buffer), &bytesWritten, &ov)) {
            if (GetLastError() != ERROR_IO_PENDING) {
                PrintError(L"������ �������� ������");
                break;
            }
            WaitForSingleObject(ov.hEvent, INFINITE);
        }

        Sleep(30); // �������� ��� ���������� ������
    }

    // ������� ��������
    CloseHandle(ov.hEvent);
    CloseHandle(hSerial);
    FreeLibrary(hXInput);
    wcout << L"��������� ���������.\n";
    return 0;
}

////#include <iostream>
////#include <windows.h>
////#include <string>
////
////int main() {
////     wcout << L"�������� ����������� COM-������:\n";
////
////    for (int i = 1; i <= 256; i++) {
////        // ��������� ��� �����
////         wstring portName = L"COM" +  to_wstring(i);
////        HANDLE hComm = CreateFile(portName.c_str(),
////            GENERIC_READ | GENERIC_WRITE,
////            0,
////            NULL,
////            OPEN_EXISTING,
////            0,
////            NULL);
////        if (hComm != INVALID_HANDLE_VALUE) {
////             wcout << L"��������: " << portName <<  endl;
////            CloseHandle(hComm);
////        }
////    }
////    return 0;
////}
