#include "Graphics/Lights/Light.hpp"

namespace Krys::Gfx
{
  Light::Light(LightHandle handle) noexcept : _handle(handle)
  {
  }

  LightHandle Light::GetHandle() const noexcept
  {
    return _handle;
  }
}