#pragma once

#include <array>
#include <unordered_map>

#include "Core.h"
#include "Graphics/Graphics.h"
#include "Graphics/GraphicsContext.h"

namespace Krys
{
  class LightManager
  {
    typedef std::array<SpotLight, LIGHTING_MAX_SPOT_LIGHTS> SpotLightArray;
    typedef std::array<SpotLightShadowCaster, LIGHTING_MAX_SPOT_LIGHT_SHADOW_CASTERS> SpotLightShadowCasterArray;

    typedef std::array<PointLight, LIGHTING_MAX_POINT_LIGHTS> PointLightArray;
    typedef std::array<PointLightShadowCaster, LIGHTING_MAX_POINT_LIGHT_SHADOW_CASTERS> PointLightShadowCasterArray;

    typedef std::array<DirectionalLight, LIGHTING_MAX_DIRECTIONAL_LIGHTS> DirectionalLightArray;
    typedef std::array<DirectionalShadowCaster, LIGHTING_MAX_DIRECTIONAL_SHADOW_CASTERS> DirectionalShadowCasterArray;

    typedef std::unordered_map<int, Ref<Framebuffer>> ShadowMap2DFramebufferPool;
    typedef std::unordered_map<int, Ref<Framebuffer>> ShadowMapCubemapFramebufferPool;

  private:
    Ref<GraphicsContext> Context;
    Ref<UniformBuffer> LightsBuffer;

    SpotLightArray SpotLights;
    SpotLightShadowCasterArray SpotLightShadowCasters;
    uint SpotLightIndex, SpotLightShadowCasterIndex;

    PointLightArray PointLights;
    PointLightShadowCasterArray PointLightShadowCasters;
    uint PointLightIndex, PointLightShadowCasterIndex;

    DirectionalLightArray DirectionalLights;
    DirectionalShadowCasterArray DirectionalShadowCasters;
    uint DirectionalLightIndex, DirectionalShadowCasterIndex;

    ShadowMap2DFramebufferPool ShadowMaps;
    ShadowMapCubemapFramebufferPool ShadowCubeMaps;

    LightingModel ActiveLightingModel;

  public:
    LightManager() noexcept
        : Context(nullptr), LightsBuffer(nullptr),
          SpotLights({}), SpotLightShadowCasters({}), SpotLightIndex(0), SpotLightShadowCasterIndex(0),
          PointLights({}), PointLightShadowCasters({}), PointLightIndex(0), PointLightShadowCasterIndex(0),
          DirectionalLights({}), DirectionalShadowCasters({}), DirectionalLightIndex(0), DirectionalShadowCasterIndex(0),
          ShadowMaps({}), ShadowCubeMaps({}), ActiveLightingModel(LightingModel::Phong) {}

    void Init(Ref<GraphicsContext> context, const ActiveTextureUnits &textureUnits) noexcept
    {
      Context = context;

      LightsBuffer = Context->CreateUniformBuffer(UNIFORM_BUFFER_BINDING_LIGHTS, UNIFORM_BUFFER_LAYOUT_LIGHTS);

      int reservedSlotIndex = textureUnits.Texture2D.GetReservedSlotIndex(RESERVED_TEXTURE_SLOT__DIRECTIONAL_SHADOW_MAP);
      LightsBuffer->SetData("u_DirectionalShadowMapSlotIndex", reservedSlotIndex);

      reservedSlotIndex = textureUnits.Texture2D.GetReservedSlotIndex(RESERVED_TEXTURE_SLOT__SPOT_LIGHT_SHADOW_MAP);
      LightsBuffer->SetData("u_SpotLightShadowMapSlotIndex", reservedSlotIndex);

      reservedSlotIndex = textureUnits.TextureCubemap.GetReservedSlotIndex(RESERVED_TEXTURE_SLOT__POINT_LIGHT_SHADOW_CUBEMAP);
      LightsBuffer->SetData("u_PointLightShadowMapSlotIndex", reservedSlotIndex);
    }

    NO_DISCARD const DirectionalLightArray &GetDirectionalLights() const noexcept { return DirectionalLights; }
    NO_DISCARD const SpotLightArray &GetSpotLights() const noexcept { return SpotLights; }
    NO_DISCARD const PointLightArray &GetPointLights() const noexcept { return PointLights; }
    NO_DISCARD const Ref<UniformBuffer> GetLightUniformBuffer() const noexcept { return LightsBuffer; }

    void AddLight(const DirectionalLight &light, const LightSettings &settings) noexcept
    {
      auto index = DirectionalLightIndex++;
      DirectionalLights[index] = light;

      string prefix = "u_DirectionalLights[" + std::to_string(index) + "].";
      LightsBuffer->SetData(prefix + "Ambient", light.Ambient);
      LightsBuffer->SetData(prefix + "Diffuse", light.Diffuse);
      LightsBuffer->SetData(prefix + "Specular", light.Specular);
      LightsBuffer->SetData(prefix + "Enabled", light.Enabled);
      LightsBuffer->SetData(prefix + "Intensity", light.Intensity);
      LightsBuffer->SetData(prefix + "Direction", light.Direction);

      if (settings.CastShadows)
      {
        DirectionalShadowCaster caster;
        caster.LightIndex = index;

        index = DirectionalShadowCasterIndex++;
        DirectionalShadowCasters[index] = caster;

        Mat4 projection = glm::ortho(caster.Bounds.Left, caster.Bounds.Right, caster.Bounds.Bottom, caster.Bounds.Top, caster.NearFarPlane.x, caster.NearFarPlane.y);
        Mat4 view = glm::lookAt(-light.Direction * 10.0f, Vec3(0.0f), Vec3(1.0f, 0.0f, 0.0f)); // TODO: configurable target/up vectors

        caster.LightSpaceMatrix = projection * view;

        prefix = "u_DirectionalShadowCasters[" + std::to_string(index) + "].";
        LightsBuffer->SetData(prefix + "Bias", caster.Bias);
        LightsBuffer->SetData(prefix + "LightIndex", caster.LightIndex);
        LightsBuffer->SetData(prefix + "ShadowMapResolution", caster.ShadowMapResolution);
        LightsBuffer->SetData(prefix + "NearFarPlane", caster.NearFarPlane);
        LightsBuffer->SetData(prefix + "LightSpaceMatrix", caster.LightSpaceMatrix);

        LightsBuffer->SetData("u_DirectionalShadowCasterCount", static_cast<int>(DirectionalShadowCasterIndex));
      }
      LightsBuffer->SetData("u_DirectionalLightCount", static_cast<int>(DirectionalLightIndex));
    }

    void AddLight(const PointLight &light, const LightSettings &settings) noexcept
    {
      auto index = PointLightIndex++;
      PointLights[index] = light;

      string prefix = "u_PointLights[" + std::to_string(index) + "].";
      LightsBuffer->SetData(prefix + "Ambient", light.Ambient);
      LightsBuffer->SetData(prefix + "Diffuse", light.Diffuse);
      LightsBuffer->SetData(prefix + "Specular", light.Specular);
      LightsBuffer->SetData(prefix + "Constant", light.Constant);
      LightsBuffer->SetData(prefix + "Linear", light.Linear);
      LightsBuffer->SetData(prefix + "Quadratic", light.Quadratic);
      LightsBuffer->SetData(prefix + "Enabled", light.Enabled);
      LightsBuffer->SetData(prefix + "Intensity", light.Intensity);
      LightsBuffer->SetData(prefix + "FarPlane", light.FarPlane);
      LightsBuffer->SetData(prefix + "Position", light.Position);

      if (settings.CastShadows)
      {
        PointLightShadowCaster caster;
        caster.LightIndex = index;

        index = PointLightShadowCasterIndex++;
        PointLightShadowCasters[index] = caster;

        float aspectRatio = static_cast<float>(caster.ShadowMapResolution) / static_cast<float>(caster.ShadowMapResolution);
        Mat4 projection = glm::perspective(glm::radians(90.0f), aspectRatio, caster.NearFarPlane.x, caster.NearFarPlane.y);

        caster.LightSpaceMatrices[0] = projection * glm::lookAt(light.Position, light.Position + Vec3(1.0, 0.0, 0.0), Vec3(0.0, -1.0, 0.0));
        caster.LightSpaceMatrices[1] = projection * glm::lookAt(light.Position, light.Position + Vec3(-1.0, 0.0, 0.0), Vec3(0.0, -1.0, 0.0));
        caster.LightSpaceMatrices[2] = projection * glm::lookAt(light.Position, light.Position + Vec3(0.0, 1.0, 0.0), Vec3(0.0, 0.0, 1.0));
        caster.LightSpaceMatrices[3] = projection * glm::lookAt(light.Position, light.Position + Vec3(0.0, -1.0, 0.0), Vec3(0.0, 0.0, -1.0));
        caster.LightSpaceMatrices[4] = projection * glm::lookAt(light.Position, light.Position + Vec3(0.0, 0.0, 1.0), Vec3(0.0, -1.0, 0.0));
        caster.LightSpaceMatrices[5] = projection * glm::lookAt(light.Position, light.Position + Vec3(0.0, 0.0, -1.0), Vec3(0.0, -1.0, 0.0));

        prefix = "u_PointLightShadowCasters[" + std::to_string(index) + "].";
        LightsBuffer->SetData(prefix + "Bias", caster.Bias);
        LightsBuffer->SetData(prefix + "LightIndex", caster.LightIndex);
        LightsBuffer->SetData(prefix + "ShadowMapResolution", caster.ShadowMapResolution);
        LightsBuffer->SetData(prefix + "NearFarPlane", caster.NearFarPlane);
        for (uint i = 0; i < 6; i++)
          LightsBuffer->SetData(prefix + "LightSpaceMatrices[" + std::to_string(i) + "]", caster.LightSpaceMatrices[i]);

        LightsBuffer->SetData("u_PointLightShadowCasterCount", static_cast<int>(PointLightShadowCasterIndex));
      }
      LightsBuffer->SetData("u_PointLightCount", static_cast<int>(PointLightIndex));
    }

    void AddLight(const SpotLight &light, const LightSettings &settings) noexcept
    {
      auto index = SpotLightIndex++;
      SpotLights[index] = light;

      string prefix = "u_SpotLights[" + std::to_string(index) + "].";
      LightsBuffer->SetData(prefix + "Ambient", light.Ambient);
      LightsBuffer->SetData(prefix + "Diffuse", light.Diffuse);
      LightsBuffer->SetData(prefix + "Specular", light.Specular);
      LightsBuffer->SetData(prefix + "Enabled", light.Enabled);
      LightsBuffer->SetData(prefix + "Intensity", light.Intensity);
      LightsBuffer->SetData(prefix + "Constant", light.Constant);
      LightsBuffer->SetData(prefix + "Linear", light.Linear);
      LightsBuffer->SetData(prefix + "Quadratic", light.Quadratic);
      LightsBuffer->SetData(prefix + "InnerCutoff", glm::cos(light.InnerCutoff));
      LightsBuffer->SetData(prefix + "OuterCutoff", glm::cos(light.OuterCutoff));
      LightsBuffer->SetData(prefix + "Direction", light.Direction);
      LightsBuffer->SetData(prefix + "Position", light.Position);

      if (settings.CastShadows)
      {
        SpotLightShadowCaster caster;
        caster.LightIndex = index;

        index = SpotLightShadowCasterIndex++;
        SpotLightShadowCasters[index] = caster;

        float aspectRatio = static_cast<float>(caster.ShadowMapResolution) / static_cast<float>(caster.ShadowMapResolution);
        Mat4 projection = glm::perspective(light.OuterCutoff * 2.0f, aspectRatio, caster.NearFarPlane.x, caster.NearFarPlane.y);
        Mat4 view = glm::lookAt(light.Position, light.Position + light.Direction, Vec3(1.0, 0.0, 0.0));
        caster.LightSpaceMatrix = projection * view;

        prefix = "u_SpotLightShadowCasters[" + std::to_string(index) + "].";
        LightsBuffer->SetData(prefix + "Bias", caster.Bias);
        LightsBuffer->SetData(prefix + "LightIndex", caster.LightIndex);
        LightsBuffer->SetData(prefix + "ShadowMapResolution", caster.ShadowMapResolution);
        LightsBuffer->SetData(prefix + "NearFarPlane", caster.NearFarPlane);
        LightsBuffer->SetData(prefix + "LightSpaceMatrix", caster.LightSpaceMatrix);

        LightsBuffer->SetData("u_SpotLightShadowCasterCount", static_cast<int>(SpotLightShadowCasterIndex));
      }
      LightsBuffer->SetData("u_SpotLightCount", static_cast<int>(SpotLightIndex));
    }

    void SetLightingModel(LightingModel model) noexcept
    {
      ActiveLightingModel = model;
      LightsBuffer->SetData("u_UseBlinnLightingModel", model == LightingModel::BlinnPhong);
    }

    void EnableLighting(bool enabled = true) noexcept
    {
      LightsBuffer->SetData("u_LightingEnabled", enabled);
    }

    void EnableShadows(bool enabled = true) noexcept
    {
      LightsBuffer->SetData("u_ShadowsEnabled", enabled);
    }
  };
}