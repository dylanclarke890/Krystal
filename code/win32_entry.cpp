#include <windows.h>
#include "types.h"

global_variable bool IsRunning;
global_variable Win32_OffscreenBuffer BackBuffer;

struct Win32_OffscreenBuffer
{
  BITMAPINFO Info;
  void *Memory;
  int Width;
  int Height;
  int Pitch;
};

struct Win32_WindowDimensions
{
  int Width;
  int Height;
};

local_to_file Win32_WindowDimensions Win32_GetWindowDimensions(HWND window)
{
  Win32_WindowDimensions result;

  RECT clientRect;
  GetClientRect(window, &clientRect);
  result.Width = clientRect.right - clientRect.left;
  result.Height = clientRect.bottom - clientRect.top;

  return result;
}

local_to_file void RenderWeirdGradient(Win32_OffscreenBuffer buffer, int xOffset, int yOffset)
{
  uint8 *row = (uint8 *)buffer.Memory;

  for (int y = 0; y < buffer.Height; y++)
  {
    uint32 *pixel = (uint32 *)row;
    for (int x = 0; x < buffer.Width; x++)
    {
      uint8 blue = (uint8)(x + xOffset);
      uint8 green = (uint8)(y + yOffset);
      *pixel++ = (green << 8) | blue;
    }

    row += buffer.Pitch;
  }
}

local_to_file void Win32_ResizeDIBSection(Win32_OffscreenBuffer *buffer, int width, int height)
{
  if (buffer->Memory)
    VirtualFree(buffer->Memory, 0, MEM_RELEASE);

  buffer->Width = width;
  buffer->Height = height;
  int bytesPerPixel = 4;
  buffer->Pitch = buffer->Width * bytesPerPixel;

  buffer->Info.bmiHeader.biSize = sizeof(buffer->Info.bmiHeader);
  buffer->Info.bmiHeader.biWidth = buffer->Width;
  buffer->Info.bmiHeader.biHeight = -buffer->Height; // Creates a top-down DIB
  buffer->Info.bmiHeader.biPlanes = 1;
  buffer->Info.bmiHeader.biBitCount = 32;
  buffer->Info.bmiHeader.biCompression = BI_RGB;

  int bitMapMemorySize = (width * height) * bytesPerPixel;
  buffer->Memory = VirtualAlloc(0, bitMapMemorySize, MEM_COMMIT, PAGE_READWRITE);

  // TODO: clear to black
}

local_to_file void Win32_UpdateWindow(HDC deviceContext, Win32_WindowDimensions dimensions, Win32_OffscreenBuffer buffer)
{
  StretchDIBits(
      deviceContext,
      0, 0, dimensions.Width, dimensions.Height,
      0, 0, buffer.Width, buffer.Height,
      buffer.Memory,
      &buffer.Info,
      DIB_RGB_COLORS, SRCCOPY);
}

LRESULT Win32_WindowCallback(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
  LRESULT result = 0;

  switch (message)
  {
  case WM_SIZE:
  {
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
    Win32_WindowDimensions dimensions = Win32_GetWindowDimensions(window);
    Win32_UpdateWindow(deviceContext, dimensions, BackBuffer);
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
  windowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
  windowClass.lpfnWndProc = Win32_WindowCallback;
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
      HDC deviceContext = GetDC(window); // Specified CS_OWNDC so we don't need to release this.
      Win32_WindowDimensions dimensions = Win32_GetWindowDimensions(window);
      Win32_ResizeDIBSection(&BackBuffer, dimensions.Width, dimensions.Height);

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

        RenderWeirdGradient(BackBuffer, xOffset, yOffset);
        xOffset++;

        Win32_WindowDimensions dimensions = Win32_GetWindowDimensions(window);
        Win32_UpdateWindow(deviceContext, dimensions, BackBuffer);
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