#pragma once

#include "Graphics/Camera.hpp"
#include "MTL/Vectors/Vec2.hpp"
#include "MTL/Vectors/Vec3.hpp"

namespace Krys::Gfx
{
  class ArcballCamera
  {
  public:
    ArcballCamera(const Vec3 &position, const Vec3 &target, const Vec2ui &viewport) noexcept;
    ~ArcballCamera() noexcept = default;

    void Update(float dx, float dy) noexcept;

    Camera &GetCamera() noexcept;

  private:
    Camera _camera;
    Vec2ui _viewport;
    Vec3 _target;
  };
}