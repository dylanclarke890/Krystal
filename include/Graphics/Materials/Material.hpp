#pragma once

#include "Base/Attributes.hpp"
#include "Base/Types.hpp"
#include "Graphics/Handles.hpp"
#include "Graphics/Materials/MaterialType.hpp"
#include "MTL/Matrices/Mat4x4.hpp"
#include "MTL/Vectors/Vec2.hpp"
#include "MTL/Vectors/Vec4.hpp"

namespace Krys::Gfx
{
  template <typename T>
  concept MaterialCustomProperty =
    std::is_same_v<T, float> || std::is_same_v<T, int64> || std::is_same_v<T, Vec2> || std::is_same_v<T, Vec4>
    || std::is_same_v<T, Mat4> || std::is_same_v<T, TextureHandle>;

  class Material
  {
  public:
    virtual ~Material() noexcept = default;

    NO_DISCARD MaterialHandle GetHandle() const noexcept;

    NO_DISCARD ProgramHandle GetProgram() const noexcept;

    NO_DISCARD MaterialType GetType() const noexcept;

    template <MaterialCustomProperty T>
    void SetCustomProperty(const string &name, T value) noexcept
    {
      if constexpr (std::is_same_v<T, float>)
        _f32s[name] = value;
      else if constexpr (std::is_same_v<T, int64>)
        _i64s[name] = value;
      else if constexpr (std::is_same_v<T, Vec2>)
        _vec2fs[name] = value;
      else if constexpr (std::is_same_v<T, Vec4>)
        _vec4fs[name] = value;
      else if constexpr (std::is_same_v<T, Mat4>)
        _mat4fs[name] = value;
      else if constexpr (std::is_same_v<T, TextureHandle>)
        _textures[name] = value;
    }

    template <MaterialCustomProperty T>
    NO_DISCARD Nullable<std::reference_wrapper<const T>>
      GetCustomPropertyValue(const string &name) const noexcept
    {
      auto FindInMap = [&](const auto &map) -> Nullable<std::reference_wrapper<const T>>
      {
        if (const auto it = map.find(name); it != map.end())
          return std::cref(it->second);
        return std::nullopt;
      };

      if constexpr (std::is_same_v<T, float>)
        return FindInMap(_f32s);
      else if constexpr (std::is_same_v<T, int64>)
        return FindInMap(_i64s);
      else if constexpr (std::is_same_v<T, Vec2>)
        return FindInMap(_vec2fs);
      else if constexpr (std::is_same_v<T, Vec4>)
        return FindInMap(_vec4fs);
      else if constexpr (std::is_same_v<T, Mat4>)
        return FindInMap(_mat4fs);
      else if constexpr (std::is_same_v<T, TextureHandle>)
        return FindInMap(_textures);

      return std::nullopt;
    }

  protected:
    Material(MaterialType type, MaterialHandle handle, ProgramHandle program) noexcept;

    MaterialHandle _handle;
    ProgramHandle _program;
    MaterialType _type;

    Map<string, float> _f32s;
    Map<string, int64> _i64s;
    Map<string, Vec2> _vec2fs;
    Map<string, Vec4> _vec4fs;
    Map<string, Mat4> _mat4fs;
    Map<string, TextureHandle> _textures;
  };
}