#pragma once

#include "Base/Types.hpp"
#include "Graphics/Handles.hpp"
#include "Graphics/Textures/TextureType.hpp"

namespace Krys::Gfx
{
  struct TextureDescriptor
  {
    string Name;
    TextureType Type {TextureType::Image};
    uint32 Width {0}, Height {0}, Channels {0};
    SamplerHandle Sampler;
  };
}