#include "pch.h"
#include "Window.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) 
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

namespace Engine
{
    Window::Window(UINT _ScreenWidth, UINT _ScreenHeight)
        : WindowHandle(nullptr)
        , ScreenWidth(_ScreenWidth)
        , ScreenHeight(_ScreenHeight)
    {

    }
    Window::~Window()
    {

    }
    bool Window::Init()
    {
        HINSTANCE hInstance = GetModuleHandle(NULL);

        WNDCLASS wc = {};
        wc.lpfnWndProc = WindowProc;
        wc.hInstance = hInstance;
        wc.lpszClassName = L"MyWindowClass";

        if (!RegisterClass(&wc))
        {
            MessageBox(NULL, L"", L"Error", MB_ICONERROR);
            return false;
        }

        WindowHandle = CreateWindowEx(
            0,
            L"MyWindowClass",
            L"Main",
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT,
            ScreenWidth, ScreenHeight,
            NULL,
            NULL,
            hInstance,
            NULL
        );

        if (WindowHandle == NULL)
        {
            MessageBox(NULL, L"", L"Error", MB_ICONERROR);
            return false;
        }

        return true;
    }

}