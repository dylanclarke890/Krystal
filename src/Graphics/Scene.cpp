#include "Graphics/Scene.hpp"
#include "Graphics/Colours.hpp"

namespace Krys::Gfx
{
  Scene::Scene(SceneHandle handle, const string &name) noexcept : _handle(handle), _name(name), _lightingRig()
  {
    // Default ambient light.
    SetAmbientLight(Colours::Black);
  }

  const string& Scene::GetName() const noexcept
  {
    return _name;
  }

  List<RenderEntity *> Scene::GetEntities() const noexcept
  {
    List<RenderEntity *> entities(_renderEntities.size());
    std::transform(_renderEntities.begin(), _renderEntities.end(), entities.begin(),
                   [](const auto &pair) { return pair.second.get(); });
    return entities;
  }

  const LightingRig &Scene::GetLightingRig() const noexcept
  {
    return _lightingRig;
  }

  const Colour &Scene::GetAmbientLight() const noexcept
  {
    return _lightingRig.AmbientLight->GetColour();
  }

  bool Scene::RemoveLight(LightHandle handle) noexcept
  {
    auto Remove = [&handle](auto &lights) -> bool
    {
      auto it = std::find_if(lights.begin(), lights.end(),
                             [&handle](const auto &light) { return light->GetHandle() == handle; });

      if (it != lights.end())
        lights.erase(it);

      return it != lights.end();
    };

    // Probably more likely to be a point light.
    auto wasFound = Remove(_lightingRig.PointLights);
    if (!wasFound)
      wasFound = Remove(_lightingRig.DirectionalLights);

    return wasFound;
  }

  bool Scene::RemoveEntity(RenderEntityHandle handle) noexcept
  {
    auto it = _renderEntities.find(handle);
    bool wasFound = it != _renderEntities.end();

    if (wasFound)
      _renderEntities.erase(it);

    return wasFound;
  }

  LightHandle Scene::NextLightHandle() noexcept
  {
    auto handle = LightHandle(_nextLightHandle.Id());
    _nextLightHandle = LightHandle(_nextLightHandle.Id() + 1);

    return handle;
  }

  RenderEntityHandle Scene::NextRenderEntityHandle() noexcept
  {
    auto handle = RenderEntityHandle(_nextRenderEntityHandle.Id());
    _nextRenderEntityHandle = RenderEntityHandle(_nextRenderEntityHandle.Id() + 1);

    return handle;
  }
}