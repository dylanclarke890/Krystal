#pragma once

#include "Base/Attributes.hpp"
#include "Base/Macros.hpp"
#include "Base/Pointers.hpp"
#include "Base/Types.hpp"
#include "Core/ApplicationSettings.hpp"

namespace Krys
{
  class EventManager;
  class InputManager;

  /// @brief The window for the application. Provides various cross-platform functionality for managing a
  /// window.
  class Window
  {
  public:
    NO_COPY_AND_ASSIGN(Window)

    virtual ~Window() noexcept = default;

    /// @brief Get the width of the window.
    NO_DISCARD uint32 GetWidth() const noexcept;

    /// @brief Get the height of the window.
    NO_DISCARD uint32 GetHeight() const noexcept;

    /// @brief Get the title of the window.
    NO_DISCARD const string &GetTitle() const noexcept;

    /// @brief Get the vertical synchronization of the window.
    NO_DISCARD bool IsVSyncEnabled() const noexcept;

    /// @brief Sets the vertical synchronization of the window.
    /// @param enabled Whether to enable or disable vertical synchronization.
    virtual void SetVSync(bool enabled) noexcept = 0;

    /// @brief Get the render frame rate of the window.
    /// This will be zero if the window is set to use vertical synchronization.
    NO_DISCARD float GetRenderFrameRate() const noexcept;

    /// @brief Set the render frame rate of the window. Has no effect if vertical synchronization is enabled.
    /// @param newFrameRate The desired frames per second.
    void SetRenderFrameRate(float newFrameRate) noexcept;

    /// @brief Polls the native window. Usually involves processing various OS events, some of which will
    /// result in an application event being raised.
    virtual void Poll() noexcept = 0;

    /// @brief Swaps the front and back buffers of the window.
    virtual void SwapBuffers() noexcept = 0;

  protected:
    /// @brief Constructs a `Window`.
    /// @param width The desired window width.
    /// @param height The desired window height.
    /// @param fps The desired frames per second.
    /// @param eventManager A pointer to the current `EventManager`.
    /// @param inputManager A pointer to the current `InputManager`.
    Window(const ApplicationSettings &settings, Ptr<EventManager> eventManager,
           Ptr<InputManager> inputManager) noexcept;

  protected:
    uint32 _width{0}, _height{0};
    bool _vsyncEnabled{false};
    float _renderFrameRate {0.0f};
    string _title;
    Ptr<EventManager> _eventManager{nullptr};
    Ptr<InputManager> _inputManager{nullptr};
  };
}