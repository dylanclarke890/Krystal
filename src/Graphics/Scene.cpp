#include "Graphics/Scene.hpp"
#include "Graphics/Colours.hpp"

namespace Krys::Gfx
{
  Scene::Scene(SceneHandle handle, const string &name) noexcept : _handle(handle), _name(name), _lightingRig()
  {
    // Default ambient light.
    SetAmbientLight(Colours::Black);
  }

  const string &Scene::GetName() const noexcept
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
    KRYS_ASSERT(handle.IsValid(), "Invalid light handle.");
    if (!handle.IsValid())
      return false;

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

    if (wasFound)
      _lightHandles.Recycle(handle);

    return wasFound;
  }

  bool Scene::RemoveEntity(RenderEntityHandle handle) noexcept
  {
    if (const auto &it = _renderEntities.find(handle); it != _renderEntities.end())
    {
      _renderEntities.erase(it);
      _renderEntityHandles.Recycle(handle);
      return true;
    }

    return false;
  }

  void Scene::SetCamera(Camera *camera) noexcept
  {
    _camera = camera;
  }
}