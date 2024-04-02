#include "krystal.h"

internal void RenderWeirdGradient(Game_OffscreenBuffer *buffer, int xOffset, int yOffset)
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

internal void GameUpdateAndRender(Game_OffscreenBuffer *buffer)
{
  RenderWeirdGradient(buffer, 0, 0);
}