#include <windows.h>
#include "main.h"

LRESULT CALLBACK 
Win32WindowProc(HWND hwnd,
                UINT uMsg,
                WPARAM wParam,
                LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_DESTROY:
        {
            PostQuitMessage(0);
            return 0;
        } break;
        
        default: 
        {
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
        } break;
    }
}

internal int
_handle_window_process(HWND* hwnd, char* WINDOW_NAME, HINSTANCE hInstance)
{
    *hwnd = CreateWindowEx(0, "_WNDCLASS", WINDOW_NAME, WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, hInstance, 0);
    
    if(!*hwnd)
    {
        MessageBox(NULL, TEXT("An error has been encountred during the window creation process"), 
                   NULL, MB_ICONERROR);
        return EXIT_FAILURE;
    }
    return 0;
}

internal int
_create_window_class(WNDCLASS* wnd, HINSTANCE hInstance, char* CLASS_NAME)
{
    wnd->lpfnWndProc = Win32WindowProc;
    wnd->hInstance = hInstance;
    wnd->lpszClassName = CLASS_NAME;
    
    
    if (!RegisterClass(wnd))
    {
        MessageBox(NULL, TEXT("Could not register window class"), 
                   NULL, MB_ICONERROR);
        return EXIT_FAILURE;
    }
    
    return 0;
}

INT CALLBACK
WinMain(HINSTANCE hInstance,
        HINSTANCE hPrevInstance,
        PSTR lpCmdLine, INT nCmdShow)
{
    WNDCLASS* wnd  = {0};
    HWND*     hwnd = {0};
    
    _create_window_class(wnd, hInstance, "_WNDCLASS");
    _handle_window_process(hwnd, "GL-WINAPI", hInstance);
    
    return 0;
}