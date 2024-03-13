#include <Windows.h>
#include <mmsystem.h>

#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")

#pragma comment(lib, "winmm.lib")

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

COLORREF colors[] = { RGB(0, 150, 255), RGB(255, 0, 0), RGB(255, 255, 0)};
int currentColorIndex = 0;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmsdLine, int nShowCmd)
{
    static TCHAR szClassName[] = TEXT("The Standard Window");
    static TCHAR szWindowTitle[] = TEXT("DORAEMON");

    WNDCLASSEX wnd;
    MSG msg;

    HWND hWnd;

    wnd.cbSize = sizeof(WNDCLASSEX);
    wnd.cbClsExtra = 0;
    wnd.cbWndExtra = 0;
    wnd.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wnd.hCursor = LoadCursor(NULL, IDC_ARROW);
    wnd.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wnd.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wnd.hInstance = hInstance;
    wnd.lpfnWndProc = WndProc;
    wnd.lpszClassName = szClassName;
    wnd.lpszMenuName = NULL;
    wnd.style = CS_VREDRAW | CS_HREDRAW;

    if(!RegisterClassEx(&wnd))
    {
        MessageBox(NULL, TEXT("Error in registering window!"), TEXT("RegisterClassEx"), MB_ICONERROR | MB_TOPMOST);
        ExitProcess(EXIT_FAILURE);
    }

    hWnd = CreateWindowEx(WS_EX_APPWINDOW, szClassName, szWindowTitle, WS_OVERLAPPEDWINDOW,
                            CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                            NULL, NULL, hInstance, NULL);

    if(hWnd == NULL)
    {
        MessageBox(NULL, TEXT("Error in creating window"), TEXT("CreateWindowEx"), MB_ICONERROR | MB_TOPMOST);
        ExitProcess(EXIT_FAILURE);
    }

    UpdateWindow(hWnd);
    ShowWindow(hWnd, nShowCmd);

    sndPlaySound("C:\\Users\\Admin\\Documents\\Win32SDK\\SELF_PROJECT\\Doreamon_theme_song.wav", SND_FILENAME | SND_ASYNC | SND_LOOP);

    SetTimer(hWnd, 1, 2000, NULL);

    while(GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    sndPlaySound(NULL, 0);

    KillTimer(hWnd, 1);

    return (msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        case WM_TIMER:
            currentColorIndex = (currentColorIndex + 1) % 3;
            InvalidateRect(hWnd, NULL, TRUE);
            break;

        case WM_PAINT:
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            RECT rect;
            GetClientRect(hWnd, &rect);

            int centerX = (rect.right - rect.left) / 2;
            int centerY = (rect.bottom - rect.top) / 2;

            // Outer circle of the face (create and set color to the light blue)
            HBRUSH hBrush = CreateSolidBrush(colors[currentColorIndex]);
            HBRUSH holdBrush = (HBRUSH)SelectObject(hdc, hBrush);

            Ellipse(hdc, centerX - 300, centerY - 300, centerX + 300, centerY + 300);

            SelectObject(hdc, holdBrush);
            DeleteObject(hBrush);

            // Inside circle of the face
            Ellipse(hdc, centerX - 260, centerY - 130, centerX + 260, centerY + 290);

            // Outer part of EYES
            Ellipse(hdc, centerX - 150, centerY - 240, centerX - 150 + 145, centerY - 240 + 230);
            Ellipse(hdc, centerX - 5, centerY - 240, centerX - 5 + 145, centerY - 240 + 230);

            // Inner part of EYES (create and set color to black)
            HBRUSH hEyeBrush = CreateSolidBrush(RGB(0, 0, 0));
            HBRUSH holdEyeBrush = (HBRUSH)SelectObject(hdc, hEyeBrush);

            Ellipse(hdc, centerX - 70, centerY - 150, centerX - 15, centerY - 65);
            Ellipse(hdc, centerX + 5, centerY - 150, centerX + 60, centerY - 65);

            SelectObject(hdc, holdEyeBrush);
            DeleteObject(hEyeBrush);

            // NOSE (create and set color to red)
            HBRUSH hNoseBrush = CreateSolidBrush(RGB(255, 0, 0));
            HBRUSH holdNoseBrush = (HBRUSH)SelectObject(hdc, hNoseBrush);

            Ellipse(hdc, centerX - 50, centerY - 50, centerX + 50, centerY + 60);

            SelectObject(hdc, holdNoseBrush);
            DeleteObject(hNoseBrush);

            // MOUTH (create and set color to light red)

            HBRUSH hMouthBrush = CreateSolidBrush(RGB(255, 75, 50));
            HBRUSH holdMouthBrush = (HBRUSH)SelectObject(hdc, hMouthBrush);

            Pie(hdc, centerX - 200, centerY + 250, centerX + 200, centerY - 50, 
                    centerX - 200, centerY + 100, centerX + 200, centerY + 100);

            SelectObject(hdc, holdMouthBrush);
            DeleteObject(hMouthBrush);

            // Line between nose and mouth
            MoveToEx(hdc, centerX-5, centerY+99, NULL);
            LineTo(hdc, centerX-5, centerY+57);

            // Left side chya mishya
            MoveToEx(hdc, centerX-225, centerY-40, NULL);
            LineTo(hdc, centerX-65, centerY+10);

            MoveToEx(hdc, centerX-240, centerY+20, NULL);
            LineTo(hdc, centerX-65, centerY+20);

            MoveToEx(hdc, centerX-230, centerY+80, NULL);
            LineTo(hdc, centerX-65, centerY+30);

            // Right side chya mishya
            MoveToEx(hdc, centerX+65, centerY+10, NULL);
            LineTo(hdc, centerX+225, centerY-40);

            MoveToEx(hdc, centerX+65, centerY+20, NULL);
            LineTo(hdc, centerX+240, centerY+20);

            MoveToEx(hdc, centerX+65, centerY+30, NULL);
            LineTo(hdc, centerX+230, centerY+80);

            EndPaint(hWnd, &ps);
            break;

        default:
            return (DefWindowProc(hWnd, uMsg, wParam, lParam));
    }

    return (0);
}