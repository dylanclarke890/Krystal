#include <windows.h>
#include <xinput.h>
#include <dsound.h>
#include "types.h"

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

global_variable bool IsRunning;
global_variable Win32_OffscreenBuffer BackBuffer;
global_variable LPDIRECTSOUNDBUFFER SecondaryBuffer;

#define X_INPUT_GET_STATE(name) DWORD WINAPI name(DWORD dwUserIndex, XINPUT_STATE *pState)
typedef X_INPUT_GET_STATE(XInputGetStateDecl);
X_INPUT_GET_STATE(XInputGetStateStub)
{
  return ERROR_DEVICE_NOT_CONNECTED;
}
global_variable XInputGetStateDecl *XInputGetState_ = XInputGetStateStub;
#define XInputGetState XInputGetState_

#define X_INPUT_SET_STATE(name) DWORD WINAPI name(DWORD dwUserIndex, XINPUT_STATE *pVibration)
typedef X_INPUT_SET_STATE(XInputSetStateDecl);
X_INPUT_SET_STATE(XInputSetStateStub)
{
  return ERROR_DEVICE_NOT_CONNECTED;
}
global_variable XInputSetStateDecl *XInputSetState_ = XInputSetStateStub;
#define XInputSetState XInputSetState_

internal void Win32_LoadXInput(void)
{
  HMODULE xInputLib = LoadLibraryA("xinput1_4.dll");
  if (!xInputLib)
  {
    // TODO: logging
    xInputLib = LoadLibraryA("xinput1_3.dll");
  }

  if (xInputLib)
  {
    XInputGetState = (XInputGetStateDecl *)GetProcAddress(xInputLib, "XInputGetState");
    XInputSetState = (XInputSetStateDecl *)GetProcAddress(xInputLib, "XInputSetState");
  }
  else
  {
    // TODO: logging
  }
}

#define DIRECT_SOUND_CREATE(name) HRESULT WINAPI name(LPCGUID pcGuidDevice, LPDIRECTSOUND *ppDS, LPUNKNOWN pUnkOuter)
typedef DIRECT_SOUND_CREATE(DirectSoundCreateDecl);

internal void Win32_InitDirectSound(HWND window, uint32 samplesPerSecond, uint32 bufferSize)
{
  HMODULE dSoundLib = LoadLibraryA("dsound.dll");
  if (!dSoundLib)
  {
    return;
  }

  DirectSoundCreateDecl *DirectSoundCreate =
      (DirectSoundCreateDecl *)GetProcAddress(dSoundLib, "DirectSoundCreate");

  LPDIRECTSOUND directSound;
  if (DirectSoundCreate && SUCCEEDED(DirectSoundCreate(0, &directSound, 0)))
  {
    WAVEFORMATEX waveFormat;
    waveFormat.wFormatTag = WAVE_FORMAT_PCM;
    waveFormat.nChannels = 2;
    waveFormat.nSamplesPerSec = samplesPerSecond;
    waveFormat.wBitsPerSample = 16;
    waveFormat.nBlockAlign = (waveFormat.nChannels * waveFormat.wBitsPerSample) / 8;
    waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
    waveFormat.cbSize = 0;

    if (SUCCEEDED(directSound->SetCooperativeLevel(window, DSSCL_PRIORITY)))
    {
      DSBUFFERDESC bufferDesc = {};
      bufferDesc.dwSize = sizeof(bufferDesc);
      bufferDesc.dwFlags = DSBCAPS_PRIMARYBUFFER;

      LPDIRECTSOUNDBUFFER primaryBuffer;
      if (SUCCEEDED(directSound->CreateSoundBuffer(&bufferDesc, &primaryBuffer, 0)))
      {
        OutputDebugStringA("Primary buffer was successfully created. \n");
        if (SUCCEEDED(primaryBuffer->SetFormat(&waveFormat)))
        {
          OutputDebugStringA("Primary buffer format was set. \n");
        }
        else
        {
          // TODO: logging
        }
      }
    }
    else
    {
      // TODO: logging
    }

    DSBUFFERDESC bufferDesc = {};
    bufferDesc.dwSize = sizeof(bufferDesc);
    bufferDesc.dwBufferBytes = bufferSize;
    bufferDesc.lpwfxFormat = &waveFormat;

    if (SUCCEEDED(directSound->CreateSoundBuffer(&bufferDesc, &SecondaryBuffer, 0)))
    {
      OutputDebugStringA("Secondary buffer was successfully created. \n");
    }
  }
  else
  {
    // TODO: logging
  }

  // Create a secondary buffer
  // Start it playing
}

internal Win32_WindowDimensions Win32_GetWindowDimensions(HWND window)
{
  Win32_WindowDimensions result;

  RECT clientRect;
  GetClientRect(window, &clientRect);
  result.Width = clientRect.right - clientRect.left;
  result.Height = clientRect.bottom - clientRect.top;

  return result;
}

internal void RenderWeirdGradient(Win32_OffscreenBuffer *buffer, int xOffset, int yOffset)
{
  uint8 *row = (uint8 *)buffer->Memory;

  for (int y = 0; y < buffer->Height; y++)
  {
    uint32 *pixel = (uint32 *)row;
    for (int x = 0; x < buffer->Width; x++)
    {
      uint8 blue = (uint8)(x + xOffset);
      uint8 green = (uint8)(y + yOffset);
      *pixel++ = (green << 8) | blue;
    }

    row += buffer->Pitch;
  }
}

internal void Win32_ResizeDIBSection(Win32_OffscreenBuffer *buffer, int width, int height)
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
  buffer->Memory = VirtualAlloc(0, bitMapMemorySize, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

  // TODO: clear to black
}

internal void Win32_UpdateWindow(Win32_OffscreenBuffer *buffer, Win32_WindowDimensions dimensions, HDC deviceContext)
{
  StretchDIBits(
      deviceContext,
      0, 0, dimensions.Width, dimensions.Height,
      0, 0, buffer->Width, buffer->Height,
      buffer->Memory,
      &buffer->Info,
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
    break;
  }
  case WM_DESTROY:
  case WM_CLOSE:
  {
    IsRunning = false;
    OutputDebugStringA("WM_DESTROY\n");
    break;
  }
  case WM_ACTIVATEAPP:
  {
    OutputDebugStringA("WM_ACTIVATEAPP\n");
    break;
  }
  case WM_PAINT:
  {
    PAINTSTRUCT paint;
    HDC deviceContext = BeginPaint(window, &paint);
    Win32_WindowDimensions dimensions = Win32_GetWindowDimensions(window);
    Win32_UpdateWindow(&BackBuffer, dimensions, deviceContext);
    EndPaint(window, &paint);
    break;
  }
  case WM_KEYUP:
  case WM_KEYDOWN:
  case WM_SYSKEYUP:
  case WM_SYSKEYDOWN:
  {
    uint32 vkCode = wParam;
    bool wasDown = ((lParam & (1 << 30))) != 0;
    bool isDown = ((lParam & (1 << 31))) == 0;

    if (wasDown != isDown)
    {
      switch (vkCode)
      {
      case 'W':
      case 'A':
      case 'S':
      case 'D':
      case 'Q':
      case 'E':
      case VK_LEFT:
      case VK_RIGHT:
      case VK_UP:
      case VK_DOWN:
      case VK_ESCAPE:
      case VK_SPACE:
        break;
      case VK_F4:
      {
        bool altKeyWasDown = (lParam & (1 << 29)) != 0;
        if (altKeyWasDown)
        {
          IsRunning = false;
        }
        break;
      }
      }
    }
  }
  default:
  {
    result = DefWindowProc(window, message, wParam, lParam);
    break;
  }
  }

  return result;
}

void ErrorExit()
{
  LPVOID lpMsgBuf;
  DWORD dw = GetLastError();

  auto dwFlags = FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS;
  FormatMessageA(dwFlags, 0, dw, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&lpMsgBuf, 0, 0);

  OutputDebugStringA((LPSTR)lpMsgBuf);
}

int WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR commandLine, int showCode)
{
  Win32_LoadXInput();

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
      int samplesPerSecond = 48000;
      int bytesPerSample = sizeof(int16) * 2;
      int toneHertz = 256, toneVolume = 4000;
      int runningSampleIndex = 0;
      int squareWavePeriod = samplesPerSecond / toneHertz;
      int halfSquareWavePeriod = squareWavePeriod / 2;
      int bufferSize = samplesPerSecond * bytesPerSample;

      Win32_InitDirectSound(window, samplesPerSecond, bufferSize);
      SecondaryBuffer->Play(0, 0, DSBPLAY_LOOPING);
      HDC deviceContext = GetDC(window); // Specified CS_OWNDC so we don't need to release this.
      Win32_WindowDimensions dimensions = Win32_GetWindowDimensions(window);
      Win32_ResizeDIBSection(&BackBuffer, dimensions.Width, dimensions.Height);

      int xOffset = 0, yOffset = 0;

      MSG msg;
      IsRunning = true;
      while (IsRunning)
      {
        while (PeekMessageA(&msg, 0, 0, 0, PM_REMOVE))
        {
          TranslateMessage(&msg);
          DispatchMessageA(&msg);
        }

        // TODO: should we poll this more frequently
        for (DWORD controllerIndex = 0; controllerIndex < XUSER_MAX_COUNT; controllerIndex++)
        {
          XINPUT_STATE controllerState;
          if (XInputGetState(controllerIndex, &controllerState) == ERROR_SUCCESS)
          {
            // Controller is plugged in
            XINPUT_GAMEPAD *pad = &controllerState.Gamepad;

            bool up = (pad->wButtons & XINPUT_GAMEPAD_DPAD_UP);
            bool down = (pad->wButtons & XINPUT_GAMEPAD_DPAD_DOWN);
            bool left = (pad->wButtons & XINPUT_GAMEPAD_DPAD_LEFT);
            bool right = (pad->wButtons & XINPUT_GAMEPAD_DPAD_RIGHT);

            bool start = (pad->wButtons & XINPUT_GAMEPAD_START);
            bool back = (pad->wButtons & XINPUT_GAMEPAD_BACK);

            bool leftShoulder = (pad->wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER);
            bool rightShoulder = (pad->wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER);

            bool aBtn = (pad->wButtons & XINPUT_GAMEPAD_A);
            bool bBtn = (pad->wButtons & XINPUT_GAMEPAD_B);
            bool xBtn = (pad->wButtons & XINPUT_GAMEPAD_X);
            bool yBtn = (pad->wButtons & XINPUT_GAMEPAD_Y);

            int16 StickX = pad->sThumbLX;
            int16 StickY = pad->sThumbLY;
          }
          else
          {
            // Controller is not available
          }
        }

        RenderWeirdGradient(&BackBuffer, xOffset, yOffset);
        xOffset++;

        // Direct sound output test
        DWORD playCursor;
        DWORD writeCursor;
        if (SUCCEEDED(SecondaryBuffer->GetCurrentPosition(&playCursor, &writeCursor)))
        {
          DWORD byteToLock = runningSampleIndex * bytesPerSample % bufferSize;
          DWORD bytesToWrite;
          if (byteToLock == playCursor)
          {
            bytesToWrite = bufferSize;
          }
          else if (byteToLock > playCursor)
          {
            bytesToWrite = bufferSize - byteToLock;
            bytesToWrite += playCursor;
          }
          else
          {
            bytesToWrite = playCursor - byteToLock;
          }

          VOID *region1;
          DWORD region1Size;
          VOID *region2;
          DWORD region2Size;
          if (SUCCEEDED(SecondaryBuffer->Lock(byteToLock, bytesToWrite, &region1, &region1Size, &region2, &region2Size, 0)))
          {
            // TODO: assert region size is valid
            int16 *sampleOut = (int16 *)region1;
            DWORD region1SampleCount = region1Size / bytesPerSample;
            for (DWORD sampleIndex = 0; sampleIndex < region1SampleCount; sampleIndex++)
            {
              int16 sampleValue = (runningSampleIndex++ / halfSquareWavePeriod) % 2 ? toneVolume : -toneVolume;
              *sampleOut++ = sampleValue;
              *sampleOut++ = sampleValue;
            }

            sampleOut = (int16 *)region2;
            DWORD region2SampleCount = region2Size / bytesPerSample;
            for (DWORD sampleIndex = 0; sampleIndex < region2SampleCount; sampleIndex++)
            {
              int16 sampleValue = (runningSampleIndex++ / halfSquareWavePeriod) % 2 ? toneVolume : -toneVolume;
              *sampleOut++ = sampleValue;
              *sampleOut++ = sampleValue;
            }

            SecondaryBuffer->Unlock(region1, region1Size, region2, region2Size);
          }
        }

        Win32_WindowDimensions dimensions = Win32_GetWindowDimensions(window);
        Win32_UpdateWindow(&BackBuffer, dimensions, deviceContext);
      }
    }
    else
    {
      ErrorExit();
    }
  }
  else
  {
    ErrorExit();
  }
  return 0;
}