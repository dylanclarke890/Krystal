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

    Ref<UniformBuffer> LightBuffer;
    Ref<GraphicsContext> Context;

    LightingModel ActiveLightingModel;

  public:
    LightManager()
        : SpotLights({}), PointLights({}), DirectionalLights({}),
          LightBuffer(0), Context(0), ActiveLightingModel(LightingModel::Phong)
    {
    }

    void Init(Ref<GraphicsContext> context)
    {
      Context = context;
      LightBuffer = Context->CreateUniformBuffer(LightBufferBinding, LightBufferLayout);
    }

    void AddDirectionalLight(const DirectionalLight &light)
    {
      auto index = DirectionalLights.size();
      DirectionalLights.push_back(light);

      string elementName = "u_DirectionalLights[" + std::to_string(index) + "].";
      LightBuffer->SetData(elementName + "Ambient", light.Ambient);
      LightBuffer->SetData(elementName + "Diffuse", light.Diffuse);
      LightBuffer->SetData(elementName + "Specular", light.Specular);

      LightBuffer->SetData(elementName + "Enabled", light.Enabled);
      LightBuffer->SetData(elementName + "Intensity", light.Intensity);

      LightBuffer->SetData(elementName + "Direction", light.Direction);

      LightBuffer->SetData("u_DirectionalLightCount", DirectionalLights.size());
    }

    void AddPointLight(const PointLight &light)
    {
      auto index = PointLights.size();
      PointLights.push_back(light);

      string elementName = "u_PointLights[" + std::to_string(index) + "].";
      LightBuffer->SetData(elementName + "Ambient", light.Ambient);
      LightBuffer->SetData(elementName + "Diffuse", light.Diffuse);
      LightBuffer->SetData(elementName + "Specular", light.Specular);

      LightBuffer->SetData(elementName + "Enabled", light.Enabled);
      LightBuffer->SetData(elementName + "Intensity", light.Intensity);

      LightBuffer->SetData(elementName + "Constant", light.Constant);
      LightBuffer->SetData(elementName + "Linear", light.Linear);
      LightBuffer->SetData(elementName + "Quadratic", light.Quadratic);

      LightBuffer->SetData(elementName + "Position", light.Position);

      LightBuffer->SetData("u_PointLightCount", PointLights.size());
    }

    void AddSpotLight(const SpotLight &light)
    {
      auto index = SpotLights.size();
      SpotLights.push_back(light);

      string elementName = "u_SpotLights[" + std::to_string(index) + "].";
      LightBuffer->SetData(elementName + "Ambient", light.Ambient);
      LightBuffer->SetData(elementName + "Diffuse", light.Diffuse);
      LightBuffer->SetData(elementName + "Specular", light.Specular);

      LightBuffer->SetData(elementName + "Enabled", light.Enabled);
      LightBuffer->SetData(elementName + "Intensity", light.Intensity);

      LightBuffer->SetData(elementName + "Constant", light.Constant);
      LightBuffer->SetData(elementName + "Linear", light.Linear);
      LightBuffer->SetData(elementName + "Quadratic", light.Quadratic);

      LightBuffer->SetData(elementName + "Direction", light.Direction);
      LightBuffer->SetData(elementName + "Position", light.Position);

      LightBuffer->SetData("u_SpotLightCount", SpotLights.size());
    }

    void SetLightingModel(LightingModel model)
    {
      ActiveLightingModel = model;
      LightBuffer->SetData("u_UseBlinnLightingModel", model == LightingModel::BlinnPhong);
    }

    void Enable(bool enabled = true)
    {
      LightBuffer->SetData("u_LightingEnabled", enabled);
    }

    void Bind()
    {
      LightBuffer->Bind();
    }

    const std::vector<DirectionalLight> &GetDirectionalLights() { return DirectionalLights; }
    const std::vector<SpotLight> &GetSpotLights() { return SpotLights; }
    const std::vector<PointLight> &GetPointLights() { return PointLights; }
  };
}