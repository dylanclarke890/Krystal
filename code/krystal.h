#pragma once

#include "types.h"

struct Game_OffscreenBuffer
{
  void *Memory;
  int Width;
  int Height;
  int Pitch;
};

internal void GameUpdateAndRender(Game_OffscreenBuffer *);