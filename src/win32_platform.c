#include "win32_platform.h"

global_variable b32 gIsRunning = 1;

LRESULT CALLBACK 
Win32WindowProc(HWND hwnd,
                UINT uMsg,
                WPARAM wParam,
                LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_CLOSE:
        {
            gIsRunning = 0;
        } break;
        
        case WM_DESTROY:
        {
            PostQuitMessage(0);
        } break;
        
        default: 
        {
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
        } break;
    }
    
    return 0;
}

internal int
_handle_window_process(HWND* hwnd,
                       const char* CLASS_NAME,
                       const char* WINDOW_NAME,
                       HINSTANCE hInstance)
{
    *hwnd = CreateWindowEx(0, CLASS_NAME, WINDOW_NAME, WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                           0, 0, hInstance, 0);
    
    if(!*hwnd)
    {
        MessageBox(NULL, TEXT("An error has been encountered during the window creation process"), 
                   NULL, MB_ICONERROR);
        
        return EXIT_FAILURE;
    }
    
    return 0;
}

internal int
_create_window_class(WNDCLASS* wnd,
                     HINSTANCE hInstance,
                     const char* CLASS_NAME)
{
    memset(wnd, 0, sizeof *wnd);
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
	LPWNDCLASS lpwnd = malloc(sizeof(WNDCLASS));
	HWND* hwnd = malloc(sizeof(HWND));
	char       CLASS_NAME[] = "_WNDCLASS";
    
	_create_window_class(lpwnd, hInstance, CLASS_NAME);
	_handle_window_process(hwnd, CLASS_NAME, TEXT("GL-WINAPI"), hInstance);
    
	//ShowWindow(*hwnd, nCmdShow);
    
	while (gIsRunning > 0)
	{
		MSG msg;
		while (PeekMessage(&msg, *hwnd, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
        
        
        Sleep(1);
		//TODO: Process user inputs
		//TODO: Process rendering
	}
    
	return 0;
}