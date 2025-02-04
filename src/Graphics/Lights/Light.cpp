#include "Graphics/Lights/Light.hpp"

namespace Krys::Gfx
{
  Light::Light(LightHandle handle, LightType type) noexcept : _handle(handle), _type(type)
  {
  }

  LightHandle Light::GetHandle() const noexcept
  {
    return _handle;
  }

  LightType Light::GetType() const noexcept
  {
    return _type;
  }
}