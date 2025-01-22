#include "Graphics/OpenGL/OpenGLSampler.hpp"
#include "Core/Debug/Macros.hpp"

namespace Krys::Gfx::OpenGL
{
  /// @brief Convert an engine address mode to an OpenGL address mode.
  /// @param mode Engine address mode.
  constexpr GLenum ToOpenGLEnum(SamplerAddressMode mode)
  {
    switch (mode)
    {
      case SamplerAddressMode::Repeat:        return GL_REPEAT;
      case SamplerAddressMode::Mirror:        return GL_MIRRORED_REPEAT;
      case SamplerAddressMode::ClampToEdge:   return GL_CLAMP_TO_EDGE;
      case SamplerAddressMode::ClampToBorder: return GL_CLAMP_TO_BORDER;
      default:                                KRYS_ASSERT(false, "Unknown enum value: OpenGL address mode"); return 0;
    }
  }

  /// @brief Convert an engine filter to an OpenGL filter.
  /// @param filter Engine filter.
  constexpr GLenum ToOpenGLEnum(SamplerFilter filter)
  {
    switch (filter)
    {
      case SamplerFilter::Nearest: return GL_NEAREST;
      case SamplerFilter::Linear:  return GL_LINEAR;
      default:                     KRYS_ASSERT(false, "Unknown enum value: OpenGL filter mode"); return 0;
    }
  }

  /// @brief Convert an engine filter to an OpenGL filter, but for mipmaps.
  /// @param min Min filter.
  /// @param mip Mipmap filter.
  constexpr GLenum ToOpenGLEnum(SamplerFilter min, SamplerFilter mip)
  {
    switch (min)
    {
      case SamplerFilter::Nearest:
        return mip == SamplerFilter::Nearest ? GL_NEAREST_MIPMAP_NEAREST : GL_NEAREST_MIPMAP_LINEAR;
      case SamplerFilter::Linear:
        return mip == SamplerFilter::Nearest ? GL_LINEAR_MIPMAP_NEAREST : GL_LINEAR_MIPMAP_LINEAR;
      default: KRYS_ASSERT(false, "Unknown enum value: OpenGL filter mode"); return 0;
    }
  }

  OpenGLSampler::OpenGLSampler(SamplerHandle handle, const SamplerDescriptor &descriptor) noexcept
      : Sampler(handle, descriptor)
  {
    ::glCreateSamplers(1u, &_sampler);

    ::glSamplerParameteri(_sampler, GL_TEXTURE_WRAP_S, ToOpenGLEnum(descriptor.AddressModeS));
    ::glSamplerParameteri(_sampler, GL_TEXTURE_WRAP_T, ToOpenGLEnum(descriptor.AddressModeT));
    ::glSamplerParameteri(_sampler, GL_TEXTURE_WRAP_R, ToOpenGLEnum(descriptor.AddressModeR));

    ::glSamplerParameterfv(_sampler, GL_TEXTURE_BORDER_COLOR, &descriptor.BorderColour.r);

    ::glSamplerParameteri(_sampler, GL_TEXTURE_MAG_FILTER, ToOpenGLEnum(descriptor.MagFilter));
    ::glSamplerParameteri(_sampler, GL_TEXTURE_MIN_FILTER,
                          descriptor.UseMipmaps ? ToOpenGLEnum(descriptor.MinFilter, descriptor.MipmapFilter)
                                                : ToOpenGLEnum(descriptor.MinFilter));
  }

  OpenGLSampler::~OpenGLSampler() noexcept
  {
    ::glDeleteSamplers(1u, &_sampler);
  }

  GLuint OpenGLSampler::GetNativeHandle() const noexcept
  {
    return _sampler;
  }
}