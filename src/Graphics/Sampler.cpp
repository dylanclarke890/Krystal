#include "Graphics/Sampler.hpp"

namespace Krys::Gfx
{
  Sampler::Sampler(SamplerHandle handle, const SamplerDescriptor &descriptor) noexcept
      : _handle(handle), _descriptor(descriptor)
  {
  }

  const SamplerDescriptor &Sampler::GetDescriptor() const noexcept
  {
    return _descriptor;
  }

  SamplerHandle Sampler::GetHandle() const noexcept
  {
    return _handle;
  }
}