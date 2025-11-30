#include <windows.h>
#include <gdiplus.h>
#include <string>
#include <vector>

// Link with gdiplus.lib for Visual Studio
#pragma comment (lib,"Gdiplus.lib")

using namespace Gdiplus;

// Global Variables
HHOOK hKeyboardHook = NULL;
bool isSoftwareActive = false; // Start in "Off" state
HWND hGlobalWnd = NULL;

// Function to send Ctrl + [Key]
void SendCtrlKey(WORD vkCode) {
    INPUT inputs[4] = {};
    ZeroMemory(inputs, sizeof(inputs));

    // Press Ctrl
    inputs[0].type = INPUT_KEYBOARD;
    inputs[0].ki.wVk = VK_CONTROL;

    // Press Key
    inputs[1].type = INPUT_KEYBOARD;
    inputs[1].ki.wVk = vkCode;

    // Release Key
    inputs[2].type = INPUT_KEYBOARD;
    inputs[2].ki.wVk = vkCode;
    inputs[2].ki.dwFlags = KEYEVENTF_KEYUP;

    // Release Ctrl
    inputs[3].type = INPUT_KEYBOARD;
    inputs[3].ki.wVk = VK_CONTROL;
    inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;

    SendInput(4, inputs, sizeof(INPUT));
}

// Low-Level Keyboard Hook
LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION && (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN)) {
        KBDLLHOOKSTRUCT* p = (KBDLLHOOKSTRUCT*)lParam;

        // Ignore injected keys (sent by our own software) to prevent infinite loops
        if (p->flags & LLKHF_INJECTED) {
            return CallNextHookEx(hKeyboardHook, nCode, wParam, lParam);
        }

        // 'S' Key Logic (Toggle)
        if (p->vkCode == 'S') {
            if (isSoftwareActive) {
                // If active, S turns it OFF
                isSoftwareActive = false;
                InvalidateRect(hGlobalWnd, NULL, FALSE); // Redraw GUI
                return 1; // Block the 'S' keystroke
            }
            // If inactive, S acts as normal 's', so we do nothing here
        }

        // Logic for other keys ONLY if software is Active
        if (isSoftwareActive) {
            switch (p->vkCode) {
            case 'C':
                SendCtrlKey('C'); // Copy
                return 1; // Swallow original 'C'
            case 'V':
                SendCtrlKey('V'); // Paste
                return 1;
            case 'X':
                SendCtrlKey('X'); // Cut
                return 1;
            case 'Z':
                SendCtrlKey('Z'); // Undo
                return 1;
            case 'A':
                SendCtrlKey('Y'); // Redo (Standard Windows is Ctrl+Y)
                return 1;
            // Note: 'S' is handled above
            }
        }
    }
    return CallNextHookEx(hKeyboardHook, nCode, wParam, lParam);
}

// Drawing Logic
void OnPaint(HDC hdc) {
    Graphics graphics(hdc);
    graphics.SetSmoothingMode(SmoothingModeAntiAlias);

    RECT rect;
    GetClientRect(hGlobalWnd, &rect);
    int width = rect.right;
    int height = rect.bottom;

    // 1. Draw Background (Black)
    SolidBrush bgBrush(Color(255, 10, 10, 10)); // Deep Black
    graphics.FillRectangle(&bgBrush, 0, 0, width, height);

    // Button Geometry
    int btnSize = 150;
    int btnX = (width - btnSize) / 2;
    int btnY = (height - btnSize) / 2;

    // 2. Draw Glow/Blur Effect
    // We simulate blur by drawing multiple semi-transparent circles
    Color glowColor = Color(100, 138, 43, 226); // Purple with alpha
    if (!isSoftwareActive) {
        glowColor = Color(50, 100, 100, 100); // Grayish when off
    }

    for (int i = 0; i < 20; i++) {
        int offset = i * 2;
        int alpha = 100 - (i * 5); 
        if (alpha < 0) alpha = 0;
        
        Color fadeColor(alpha, glowColor.GetR(), glowColor.GetG(), glowColor.GetB());
        SolidBrush blurBrush(fadeColor);
        graphics.FillEllipse(&blurBrush, btnX - offset, btnY - offset, btnSize + (offset * 2), btnSize + (offset * 2));
    }

    // 3. Draw Main Circle Button
    Color mainColor = isSoftwareActive ? Color(255, 138, 43, 226) : Color(255, 40, 40, 40); // Purple if On, Dark Gray if Off
    SolidBrush btnBrush(mainColor);
    graphics.FillEllipse(&btnBrush, btnX, btnY, btnSize, btnSize);

    // 4. Draw Text
    FontFamily fontFamily(L"Arial");
    Font font(&fontFamily, 24, FontStyleBold, UnitPixel);
    SolidBrush textBrush(Color(255, 255, 255, 255));
    StringFormat stringFormat;
    stringFormat.SetAlignment(StringAlignmentCenter);
    stringFormat.SetLineAlignment(StringAlignmentCenter);

    std::wstring statusText = isSoftwareActive ? L"STOP" : L"START";
    
    // Check if user has clicked "Stop" (which means currently On), we show "Stop" so they know clicking it stops.
    // Logic: 
    // If Active -> Button says STOP (to stop it)
    // If Inactive -> Button says START (to start it)

    RectF textArea((REAL)btnX, (REAL)btnY, (REAL)btnSize, (REAL)btnSize);
    graphics.DrawString(statusText.c_str(), -1, &font, textArea, &stringFormat, &textBrush);

    // 5. Status Indicator Text
    Font statusFont(&fontFamily, 14, FontStyleRegular, UnitPixel);
    SolidBrush statusBrush(Color(255, 180, 180, 180));
    RectF statusArea(0, (REAL)(height - 40), (REAL)width, 40);
    std::wstring subText = isSoftwareActive ? L"Keyboard Shortcuts Active" : L"Keyboard Normal Mode";
    graphics.DrawString(subText.c_str(), -1, &statusFont, statusArea, &stringFormat, &statusBrush);
}

// Window Procedure
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        OnPaint(hdc);
        EndPaint(hWnd, &ps);
    }
    break;

    case WM_LBUTTONDOWN:
    {
        // Simple hit testing for the center circle
        RECT rect;
        GetClientRect(hWnd, &rect);
        int width = rect.right;
        int height = rect.bottom;
        int centerX = width / 2;
        int centerY = height / 2;
        int clickX = LOWORD(lParam);
        int clickY = HIWORD(lParam);

        // Calculate distance from center
        double dist = sqrt(pow(clickX - centerX, 2) + pow(clickY - centerY, 2));
        
        // If clicked inside radius (75px)
        if (dist < 75) {
            isSoftwareActive = !isSoftwareActive;
            InvalidateRect(hWnd, NULL, FALSE); // Force redraw
        }
    }
    break;

    case WM_ERASEBKGND:
        return 1; // Prevent flickering

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Main Entry Point
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // 1. Initialize GDI+
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    // 2. Register Window Class
    WNDCLASSEX wc;
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = L"ShortcutMapperClass";
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wc)) {
        MessageBox(NULL, L"Window Registration Failed!", L"Error", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    // 3. Create Window
    // Fixed size window, not resizable for simplicity
    hGlobalWnd = CreateWindowEx(
        WS_EX_LAYERED, // Optional: for transparency if needed later, but standard opaque here
        L"ShortcutMapperClass",
        L"LazyKey",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT, 400, 400,
        NULL, NULL, hInstance, NULL);

    if (hGlobalWnd == NULL) {
        MessageBox(NULL, L"Window Creation Failed!", L"Error", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    SetLayeredWindowAttributes(hGlobalWnd, 0, 255, LWA_ALPHA); // Ensure opacity

    ShowWindow(hGlobalWnd, nCmdShow);
    UpdateWindow(hGlobalWnd);

    // 4. Install Keyboard Hook
    hKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, hInstance, 0);
    if (hKeyboardHook == NULL) {
        MessageBox(NULL, L"Failed to install keyboard hook!", L"Error", MB_ICONERROR);
    }

    // 5. Message Loop
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // 6. Cleanup
    if (hKeyboardHook) UnhookWindowsHookEx(hKeyboardHook);
    GdiplusShutdown(gdiplusToken);

    return (int)msg.wParam;
}