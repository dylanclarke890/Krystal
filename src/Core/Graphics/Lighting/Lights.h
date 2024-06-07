#pragma once

#include "Maths/Maths.h"
#include "Graphics/BufferLayout.h"

namespace Krys
{
  struct DirectionalLight
  {
    Vec3 Ambient;
    Vec3 Diffuse;
    Vec3 Specular;

    bool Enabled;
    float Intensity;

    Vec3 Direction;
  };

  struct PointLight
  {
    Vec3 Ambient;
    Vec3 Diffuse;
    Vec3 Specular;

    float Constant;
    float Linear;
    float Quadratic;

    bool Enabled;
    float Intensity;

    Vec3 Position;
  };

  struct SpotLight
  {
    Vec3 Ambient;
    Vec3 Diffuse;
    Vec3 Specular;

    float Constant;
    float Linear;
    float Quadratic;

    bool Enabled;
    float Intensity;

    Vec3 Direction;
    Vec3 Position;

    float InnerCutoff;
    float OuterCutoff;
  };

  constexpr uint32 DirectionalLightBufferBinding = 7;
  constexpr uint32 PointLightBufferBinding = 8;
  constexpr uint32 SpotLightBufferBinding = 9;
  constexpr uint32 LightCountsBufferBinding = 10;

  static UniformBufferLayout DirectionalLightBufferLayout =
      UniformBufferLayout({{UniformDataType::Vec3, "Ambient"},
                           {UniformDataType::Vec3, "Diffuse"},
                           {UniformDataType::Vec3, "Specular"},

                           {UniformDataType::Scalar, "Enabled"},
                           {UniformDataType::Scalar, "Intensity"},

                           {UniformDataType::Vec3, "Direction"}},
                          5);

  static UniformBufferLayout PointLightBufferLayout =
      UniformBufferLayout({{UniformDataType::Vec3, "Ambient"},
                           {UniformDataType::Vec3, "Diffuse"},
                           {UniformDataType::Vec3, "Specular"},

                           {UniformDataType::Scalar, "Constant"},
                           {UniformDataType::Scalar, "Linear"},
                           {UniformDataType::Scalar, "Quadratic"},

                           {UniformDataType::Scalar, "Enabled"},
                           {UniformDataType::Scalar, "Intensity"},

                           {UniformDataType::Vec3, "Position"}},
                          32);

  static UniformBufferLayout SpotLightBufferLayout =
      UniformBufferLayout({{UniformDataType::Vec3, "Ambient"},
                           {UniformDataType::Vec3, "Diffuse"},
                           {UniformDataType::Vec3, "Specular"},

                           {UniformDataType::Scalar, "Constant"},
                           {UniformDataType::Scalar, "Linear"},
                           {UniformDataType::Scalar, "Quadratic"},

                           {UniformDataType::Scalar, "Enabled"},
                           {UniformDataType::Scalar, "Intensity"},

                           {UniformDataType::Vec3, "Direction"},
                           {UniformDataType::Vec3, "Position"},

                           {UniformDataType::Scalar, "InnerCutoff"},
                           {UniformDataType::Scalar, "OuterCutoff"}},
                          32);

  static UniformBufferLayout LightCountsBufferLayout =
      UniformBufferLayout({{UniformDataType::Scalar, "DirectionalLightCount"},
                           {UniformDataType::Scalar, "PointLightCount"},
                           {UniformDataType::Scalar, "SpotLightCount"}},
                          1);
}