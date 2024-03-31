#include <windows.h>
#include "types.h"

global_variable bool IsRunning;

global_variable BITMAPINFO BitmapInfo{};
global_variable void *BitmapMemory{};
global_variable int BitmapWidth;
global_variable int BitmapHeight;
global_variable int bytesPerPixel = 4;

local_to_file void RenderWeirdGradient(int xOffset, int yOffset)
{

  int pitch = BitmapWidth * bytesPerPixel;
  uint8 *row = (uint8 *)BitmapMemory;

  for (int y = 0; y < BitmapHeight; y++)
  {
    uint32 *pixel = (uint32 *)row;
    for (int x = 0; x < BitmapWidth; x++)
    {
      uint8 blue = (uint8)(x + xOffset);
      uint8 green = (uint8)(y + yOffset);
      *pixel++ = (green << 8) | blue;
    }

    row += pitch;
  }
}

local_to_file void Win32ResizeDIBSection(int width, int height)
{
  int bitMapMemorySize = (width * height) * bytesPerPixel;
  if (BitmapMemory)
  {
    VirtualFree(BitmapMemory, 0, MEM_RELEASE);
  }

  BitmapWidth = width;
  BitmapHeight = height;

  BitmapInfo.bmiHeader.biSize = sizeof(BitmapInfo.bmiHeader);
  BitmapInfo.bmiHeader.biWidth = BitmapWidth;
  BitmapInfo.bmiHeader.biHeight = -BitmapHeight; // Create a top-down DIB
  BitmapInfo.bmiHeader.biPlanes = 1;
  BitmapInfo.bmiHeader.biBitCount = 32;
  BitmapInfo.bmiHeader.biCompression = BI_RGB;

  BitmapMemory = VirtualAlloc(0, bitMapMemorySize, MEM_COMMIT, PAGE_READWRITE);

  // TODO: clear to black
}

local_to_file void Win32UpdateWindow(HDC deviceContext, RECT *windowRect, int x, int y, int width, int height)
{
  int windowWidth = windowRect->right - windowRect->left;
  int windowHeight = windowRect->bottom - windowRect->top;

  StretchDIBits(
      deviceContext,
      0, 0, BitmapWidth, BitmapHeight,
      x, y, windowWidth, windowHeight,
      BitmapMemory,
      &BitmapInfo,
      DIB_RGB_COLORS, SRCCOPY);
}

LRESULT Win32WindowCallback(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
  LRESULT result = 0;

  switch (message)
  {
  case WM_SIZE:
  {
    RECT clientRect;
    GetClientRect(window, &clientRect);

    int width = clientRect.right - clientRect.left;
    int height = clientRect.bottom - clientRect.top;
    Win32ResizeDIBSection(width, height);

    OutputDebugStringA("WM_SIZE\n");
  }
  break;
  case WM_DESTROY:
  case WM_CLOSE:
  {
    IsRunning = false;
    OutputDebugStringA("WM_DESTROY\n");
  }
  break;
  case WM_ACTIVATEAPP:
  {
    OutputDebugStringA("WM_ACTIVATEAPP\n");
  }
  break;
  case WM_PAINT:
  {
    PAINTSTRUCT paint;
    HDC deviceContext = BeginPaint(window, &paint);

    int x = paint.rcPaint.left;
    int y = paint.rcPaint.top;
    int width = paint.rcPaint.right - paint.rcPaint.left;
    int height = paint.rcPaint.bottom - paint.rcPaint.top;

    RECT clientRect;
    GetClientRect(window, &clientRect);
    Win32UpdateWindow(deviceContext, &clientRect, x, y, width, height);

    EndPaint(window, &paint);
  }
  break;
  default:
  {
    result = DefWindowProc(window, message, wParam, lParam);
  }
  break;
  }

  return result;
}

int WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR commandLine, int showCode)
{
  WNDCLASSA windowClass = {};

  // TODO: check if these flags still matter
  windowClass.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;

  windowClass.lpfnWndProc = Win32WindowCallback;
  windowClass.hInstance = instance;
  windowClass.lpszClassName = "HandmadeHeroWindowClass";

  if (RegisterClassA(&windowClass))
  {
    HWND window = CreateWindowExA(
        0, windowClass.lpszClassName, "Handmade Hero",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        0, 0, instance, 0);

    if (window)
    {
      IsRunning = true;
      int xOffset = 0, yOffset = 0;
      MSG msg;
      while (IsRunning)
      {
        while (PeekMessageA(&msg, 0, 0, 0, PM_REMOVE))
        {
          TranslateMessage(&msg);
          DispatchMessageA(&msg);
        }

        RenderWeirdGradient(xOffset, yOffset);

        HDC deviceContext = GetDC(window);
        RECT clientRect;
        GetClientRect(window, &clientRect);
        int windowWidth = clientRect.right - clientRect.left;
        int windowHeight = clientRect.bottom - clientRect.top;
        Win32UpdateWindow(deviceContext, &clientRect, 0, 0, windowWidth, windowHeight);
        ReleaseDC(window, deviceContext);

        xOffset++;
      }
    }
    else
    {
      // TODO: logging
    }
  }
  else
  {
    // TODO: logging
  }
  return 0;
}