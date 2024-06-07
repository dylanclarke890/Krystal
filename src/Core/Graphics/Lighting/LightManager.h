#pragma once

#include <vector>

#include "Core.h"
#include "Lights.h"
#include "Graphics/GraphicsContext.h"

namespace Krys
{

  class LightManager
  {
  private:
    std::vector<SpotLight> SpotLights;
    std::vector<PointLight> PointLights;
    std::vector<DirectionalLight> DirectionalLights;

    Ref<UniformBuffer> PointLightBuffer, SpotLightBuffer, DirectionalLightBuffer, LightCountsBuffer;
    Ref<GraphicsContext> Context;

  public:
    LightManager()
        : SpotLights({}), PointLights({}), DirectionalLights({}),
          PointLightBuffer(0), SpotLightBuffer(0), DirectionalLightBuffer(0), LightCountsBuffer(0),
          Context(0)
    {
    }

    void Init(Ref<GraphicsContext> context)
    {
      Context = context;
      DirectionalLightBuffer = Context->CreateUniformBuffer(DirectionalLightBufferBinding, DirectionalLightBufferLayout);
      PointLightBuffer = Context->CreateUniformBuffer(PointLightBufferBinding, PointLightBufferLayout);
      SpotLightBuffer = Context->CreateUniformBuffer(SpotLightBufferBinding, SpotLightBufferLayout);
      LightCountsBuffer = Context->CreateUniformBuffer(LightCountsBufferBinding, LightCountsBufferLayout);

      UpdateLightCountsBuffer();
    }

    void AddSpotLight(const SpotLight &light)
    {
      SpotLights.push_back(light);
      UpdateSpotLightBuffer();
    }

    void AddPointLight(const PointLight &light)
    {
      PointLights.push_back(light);
      UpdatePointLightBuffer();
    }

    void AddDirectionalLight(const DirectionalLight &light)
    {
      DirectionalLights.push_back(light);
      UpdateDirectionalLightBuffer();
    }

    void BindUBOs()
    {
      DirectionalLightBuffer->Bind();
      PointLightBuffer->Bind();
      SpotLightBuffer->Bind();
      LightCountsBuffer->Bind();
    }

  private:
    void UpdateSpotLightBuffer()
    {
      SpotLightBuffer->SetData(SpotLights.data(), static_cast<uint32>(SpotLights.size() * sizeof(SpotLight)));
      UpdateLightCountsBuffer();
    }

    void UpdatePointLightBuffer()
    {
      PointLightBuffer->SetData(PointLights.data(), static_cast<uint32>(PointLights.size() * sizeof(PointLight)));
      UpdateLightCountsBuffer();
    }

    void UpdateDirectionalLightBuffer()
    {
      DirectionalLightBuffer->SetData(DirectionalLights.data(), static_cast<uint32>(DirectionalLights.size() * sizeof(DirectionalLight)));
      UpdateLightCountsBuffer();
    }

    void UpdateLightCountsBuffer()
    {
      struct LightCounts
      {
        int DirectionalLightCount;
        int PointLightCount;
        int SpotLightCount;
      } lightCounts;

      lightCounts.DirectionalLightCount = static_cast<int>(DirectionalLights.size());
      lightCounts.PointLightCount = static_cast<int>(PointLights.size());
      lightCounts.SpotLightCount = static_cast<int>(SpotLights.size());

      LightCountsBuffer->SetData(&lightCounts, sizeof(LightCounts));
    }
  };
}