#pragma once

#include <array>
#include <span>

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

    LightingModel ActiveLightingModel;
    Ref<ActiveTextureUnits> TextureUnits;

  public:
    LightManager() noexcept
        : Context(nullptr), LightsBuffer(nullptr),
          SpotLights({}), SpotLightShadowCasters({}), SpotLightIndex(0), SpotLightShadowCasterIndex(0),
          PointLights({}), PointLightShadowCasters({}), PointLightIndex(0), PointLightShadowCasterIndex(0),
          DirectionalLights({}), DirectionalShadowCasters({}), DirectionalLightIndex(0), DirectionalShadowCasterIndex(0),
          ActiveLightingModel(LightingModel::Phong), TextureUnits(nullptr) {}

    void Init(Ref<GraphicsContext> context, Ref<ActiveTextureUnits> textureUnits) noexcept
    {
      Context = context;
      LightsBuffer = Context->CreateUniformBuffer(UNIFORM_BUFFER_BINDING_LIGHTS, UNIFORM_BUFFER_LAYOUT_LIGHTS);
      TextureUnits = textureUnits;
    }

    void AddLight(const DirectionalLight &light, const LightSettings &settings) noexcept
    {
      auto index = DirectionalLightIndex++;
      DirectionalLights[index] = light;
      LightsBuffer->SetData("u_DirectionalLightCount", static_cast<int>(DirectionalLightIndex));

      string prefix = "u_DirectionalLights[" + std::to_string(index) + "].";
      SetSharedLightData(light, prefix);
      LightsBuffer->SetData(prefix + "Direction", light.Direction);

      if (settings.CastShadows)
      {
        DirectionalShadowCaster caster{};
        caster.Enabled = true;
        caster.LightIndex = index;
        caster.NearFarPlane = settings.NearFarPlane;
        index = DirectionalShadowCasterIndex++;

        Vec3 direction = -light.Direction;
        Vec3 up = Vec3(0.0f, 1.0f, 0.0f);

        // Check if the direction is parallel or anti-parallel to the up vector
        if (glm::abs(glm::dot(glm::normalize(direction), glm::normalize(up))) > 0.999f)
          up = Vec3(1.0f, 0.0f, 0.0f);

        Mat4 projection = glm::ortho(caster.Bounds.Left, caster.Bounds.Right, caster.Bounds.Bottom, caster.Bounds.Top, caster.NearFarPlane.x, caster.NearFarPlane.y);
        Mat4 view = glm::lookAt(direction * 10.0f, Vec3(0.0f), up);
        caster.LightSpaceMatrix = projection * view;

        prefix = "u_DirectionalShadowCasters[" + std::to_string(index) + "].";
        auto reservedSlot = TextureUnits->ReserveSlot(ReservedSlotType::DirectionalShadowMap);
        caster.ShadowMapSlotIndex = reservedSlot.second;

        SetSharedShadowCasterData(caster, prefix);
        LightsBuffer->SetData(prefix + "LightSpaceMatrix", caster.LightSpaceMatrix);

        caster.ShadowMapFramebuffer = CreateDepthFramebuffer(caster, reservedSlot.first);

        DirectionalShadowCasters[index] = caster;
        LightsBuffer->SetData("u_DirectionalShadowCasterCount", static_cast<int>(DirectionalShadowCasterIndex));
      }
    }

    void AddLight(const PointLight &light, const LightSettings &settings) noexcept
    {
      auto index = PointLightIndex++;
      PointLights[index] = light;
      LightsBuffer->SetData("u_PointLightCount", static_cast<int>(PointLightIndex));

      string prefix = "u_PointLights[" + std::to_string(index) + "].";
      SetSharedLightData(light, prefix);
      LightsBuffer->SetData(prefix + "Constant", light.Constant);
      LightsBuffer->SetData(prefix + "Linear", light.Linear);
      LightsBuffer->SetData(prefix + "Quadratic", light.Quadratic);
      LightsBuffer->SetData(prefix + "Position", light.Position);

      if (settings.CastShadows)
      {
        PointLightShadowCaster caster{};
        caster.Enabled = true;
        caster.LightIndex = index;
        caster.NearFarPlane = settings.NearFarPlane;
        index = PointLightShadowCasterIndex++;

        float aspectRatio = static_cast<float>(caster.ShadowMapResolution) / static_cast<float>(caster.ShadowMapResolution);
        Mat4 projection = glm::perspective(glm::radians(90.0f), aspectRatio, caster.NearFarPlane.x, caster.NearFarPlane.y);
        caster.LightSpaceMatrices[0] = projection * glm::lookAt(light.Position, light.Position + Vec3(1.0, 0.0, 0.0), Vec3(0.0, -1.0, 0.0));
        caster.LightSpaceMatrices[1] = projection * glm::lookAt(light.Position, light.Position + Vec3(-1.0, 0.0, 0.0), Vec3(0.0, -1.0, 0.0));
        caster.LightSpaceMatrices[2] = projection * glm::lookAt(light.Position, light.Position + Vec3(0.0, 1.0, 0.0), Vec3(0.0, 0.0, 1.0));
        caster.LightSpaceMatrices[3] = projection * glm::lookAt(light.Position, light.Position + Vec3(0.0, -1.0, 0.0), Vec3(0.0, 0.0, -1.0));
        caster.LightSpaceMatrices[4] = projection * glm::lookAt(light.Position, light.Position + Vec3(0.0, 0.0, 1.0), Vec3(0.0, -1.0, 0.0));
        caster.LightSpaceMatrices[5] = projection * glm::lookAt(light.Position, light.Position + Vec3(0.0, 0.0, -1.0), Vec3(0.0, -1.0, 0.0));

        prefix = "u_PointLightShadowCasters[" + std::to_string(index) + "].";
        auto reservedSlot = TextureUnits->ReserveSlot(ReservedSlotType::PointLightShadowMap);
        caster.ShadowMapSlotIndex = reservedSlot.second;

        SetSharedShadowCasterData(caster, prefix);
        for (uint i = 0; i < 6; i++)
          LightsBuffer->SetData(prefix + "LightSpaceMatrices[" + std::to_string(i) + "]", caster.LightSpaceMatrices[i]);

        caster.ShadowMapFramebuffer = CreateDepthFramebuffer(caster, reservedSlot.first, true);

        PointLightShadowCasters[index] = caster;
        LightsBuffer->SetData("u_PointLightShadowCasterCount", static_cast<int>(PointLightShadowCasterIndex));
      }
    }

    void AddLight(const SpotLight &light, const LightSettings &settings) noexcept
    {
      auto index = SpotLightIndex++;
      SpotLights[index] = light;
      LightsBuffer->SetData("u_SpotLightCount", static_cast<int>(SpotLightIndex));

      string prefix = "u_SpotLights[" + std::to_string(index) + "].";
      SetSharedLightData(light, prefix);
      LightsBuffer->SetData(prefix + "Constant", light.Constant);
      LightsBuffer->SetData(prefix + "Linear", light.Linear);
      LightsBuffer->SetData(prefix + "Quadratic", light.Quadratic);
      LightsBuffer->SetData(prefix + "InnerCutoff", glm::cos(light.InnerCutoff));
      LightsBuffer->SetData(prefix + "OuterCutoff", glm::cos(light.OuterCutoff));
      LightsBuffer->SetData(prefix + "Direction", light.Direction);
      LightsBuffer->SetData(prefix + "Position", light.Position);

      if (settings.CastShadows)
      {
        SpotLightShadowCaster caster{};
        caster.LightIndex = index;
        caster.Enabled = true;
        caster.NearFarPlane = settings.NearFarPlane;
        index = SpotLightShadowCasterIndex++;

        float aspectRatio = static_cast<float>(caster.ShadowMapResolution) / static_cast<float>(caster.ShadowMapResolution);
        Mat4 projection = glm::perspective(light.OuterCutoff * 2.0f, aspectRatio, caster.NearFarPlane.x, caster.NearFarPlane.y);
        Mat4 view = glm::lookAt(light.Position, light.Position + light.Direction, Vec3(1.0, 0.0, 0.0));
        caster.LightSpaceMatrix = projection * view;

        prefix = "u_SpotLightShadowCasters[" + std::to_string(index) + "].";
        auto reservedSlot = TextureUnits->ReserveSlot(ReservedSlotType::SpotLightShadowMap);
        caster.ShadowMapSlotIndex = reservedSlot.second;

        SetSharedShadowCasterData(caster, prefix);
        LightsBuffer->SetData(prefix + "LightSpaceMatrix", caster.LightSpaceMatrix);

        caster.ShadowMapFramebuffer = CreateDepthFramebuffer(caster, reservedSlot.first);

        SpotLightShadowCasters[index] = caster;
        LightsBuffer->SetData("u_SpotLightShadowCasterCount", static_cast<int>(SpotLightShadowCasterIndex));
      }
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

    NO_DISCARD std::span<const DirectionalLight> GetDirectionalLights() const noexcept
    {
      return std::span<const DirectionalLight>(DirectionalLights.data(), DirectionalLightIndex);
    }

    NO_DISCARD std::span<const DirectionalShadowCaster> GetDirectionalShadowCasters() const noexcept
    {
      return std::span<const DirectionalShadowCaster>(DirectionalShadowCasters.data(), DirectionalShadowCasterIndex);
    }

    NO_DISCARD std::span<const SpotLight> GetSpotLights() const noexcept
    {
      return std::span<const SpotLight>(SpotLights.data(), SpotLightIndex);
    }

    NO_DISCARD std::span<const SpotLightShadowCaster> GetSpotLightShadowCasters() const noexcept
    {
      return std::span<const SpotLightShadowCaster>(SpotLightShadowCasters.data(), SpotLightShadowCasterIndex);
    }

    NO_DISCARD std::span<const PointLight> GetPointLights() const noexcept
    {
      return std::span<const PointLight>(PointLights.data(), PointLightIndex);
    }

    NO_DISCARD std::span<const PointLightShadowCaster> GetPointLightShadowCasters() const noexcept
    {
      return std::span<const PointLightShadowCaster>(PointLightShadowCasters.data(), PointLightShadowCasterIndex);
    }

    NO_DISCARD const Ref<UniformBuffer> GetLightUniformBuffer() const noexcept { return LightsBuffer; }

  private:
    void SetSharedLightData(const Light &light, const string &prefix) noexcept
    {
      LightsBuffer->SetData(prefix + "Ambient", light.Ambient);
      LightsBuffer->SetData(prefix + "Diffuse", light.Diffuse);
      LightsBuffer->SetData(prefix + "Specular", light.Specular);
      LightsBuffer->SetData(prefix + "Enabled", light.Enabled);
      LightsBuffer->SetData(prefix + "Intensity", light.Intensity);
    }

    void SetSharedShadowCasterData(const ShadowCaster &caster, const string &prefix) noexcept
    {
      LightsBuffer->SetData(prefix + "Bias", caster.Bias);
      LightsBuffer->SetData(prefix + "LightIndex", caster.LightIndex);
      LightsBuffer->SetData(prefix + "ShadowMapResolution", caster.ShadowMapResolution);
      LightsBuffer->SetData(prefix + "ShadowMapSlotIndex", caster.ShadowMapSlotIndex);
      LightsBuffer->SetData(prefix + "Enabled", caster.Enabled);
      LightsBuffer->SetData(prefix + "NearFarPlane", caster.NearFarPlane);
    }

    NO_DISCARD Ref<Framebuffer> CreateDepthFramebuffer(ShadowCaster &caster, int slotIndex, bool isCubemap = false)
    {
      auto shadowMapFramebuffer = Context->CreateFramebuffer(caster.ShadowMapResolution, caster.ShadowMapResolution);

      if (isCubemap)
        shadowMapFramebuffer->AddDepthCubemapAttachment();
      else
        shadowMapFramebuffer->AddDepthAttachment();

      shadowMapFramebuffer->DisableReadBuffer();
      shadowMapFramebuffer->DisableWriteBuffers();
      KRYS_ASSERT(shadowMapFramebuffer->IsComplete(), "Shadow map framebuffer incomplete", 0);

      caster.ShadowMapFramebuffer = shadowMapFramebuffer;
      caster.DepthTexture = shadowMapFramebuffer->GetDepthAttachment();

      if (isCubemap)
        TextureUnits->TextureCubemap.Slots[slotIndex] = caster.DepthTexture;
      else
        TextureUnits->Texture2D.Slots[slotIndex] = caster.DepthTexture;

      return shadowMapFramebuffer;
    }
  };
}