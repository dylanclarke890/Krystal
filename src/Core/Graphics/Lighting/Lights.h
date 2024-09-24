#pragma once

#include "Maths/Maths.h"
#include "Graphics/BufferLayout.h"
#include "Graphics/Constants.h"

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

  static UniformStructLayout DirectionalLightStructLayout = {
      {{UniformDataType::Vec3, "Ambient"},
       {UniformDataType::Vec3, "Diffuse"},
       {UniformDataType::Vec3, "Specular"},

       {UniformDataType::Scalar, "Enabled"},
       {UniformDataType::Scalar, "Intensity"},

       {UniformDataType::Vec3, "Direction"}}};

  static UniformStructLayout PointLightStructLayout = {
      {{UniformDataType::Vec3, "Ambient"},
       {UniformDataType::Vec3, "Diffuse"},
       {UniformDataType::Vec3, "Specular"},

       {UniformDataType::Scalar, "Constant"},
       {UniformDataType::Scalar, "Linear"},
       {UniformDataType::Scalar, "Quadratic"},

       {UniformDataType::Scalar, "Enabled"},
       {UniformDataType::Scalar, "Intensity"},

       {UniformDataType::Vec3, "Position"}}};

  static UniformStructLayout SpotLightStructLayout = {
      {UniformDataType::Vec3, "Ambient"},
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
      {UniformDataType::Scalar, "OuterCutoff"}};

  static UniformBufferLayout LightBufferLayout = {
      {UniformDataType::Struct, "u_DirectionalLights", DirectionalLightStructLayout, LIGHTING_MAX_DIRECTIONAL_LIGHTS},
      {UniformDataType::Struct, "u_PointLights", PointLightStructLayout, LIGHTING_MAX_POINT_LIGHTS},
      {UniformDataType::Struct, "u_SpotLights", SpotLightStructLayout, LIGHTING_MAX_SPOT_LIGHTS},
      {UniformDataType::Scalar, "u_DirectionalLightCount"},
      {UniformDataType::Scalar, "u_PointLightCount"},
      {UniformDataType::Scalar, "u_SpotLightCount"},
      {UniformDataType::Scalar, "u_UseBlinnLightingModel"},
      {UniformDataType::Scalar, "u_LightingEnabled"},
      {UniformDataType::Scalar, "u_Texture2DShadowMapSlotIndex"},
      {UniformDataType::Scalar, "u_CubemapShadowMapSlotIndex"}};
}