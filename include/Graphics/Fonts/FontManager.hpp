#pragma once

#include "Base/Attributes.hpp"
#include "Base/Types.hpp"
#include "Base/Pointers.hpp"
#include "Graphics/Handles.hpp"
#include "Graphics/Fonts/Font.hpp"

namespace Krys::Gfx
{
  class TextureManager;

  struct FontSettings
  {
    int32 Size = 48;
    int32 Padding = 0;
    bool Kerning = false;
  };

  class FontManager
  {
  public:
    /// @brief Constructor for FontManager.
    /// @param textureManager A pointer to the texture manager.
    FontManager(Ptr<TextureManager> textureManager) noexcept;

    /// @brief Destructor for FontManager.
    /// @note Cleans up all loaded fonts.
    ~FontManager() noexcept;

    /// @brief Load a font from a file.
    /// @param path The path to the font file.
    /// @return A handle to the loaded font.
    NO_DISCARD FontHandle LoadFont(const string &path, FontSettings settings = {}) noexcept;

    /// @brief Get a font by handle.
    /// @param handle The handle of the font.
    /// @return A pointer to the font if it exists, nullptr otherwise.
    NO_DISCARD Font *GetFont(FontHandle handle) noexcept;

    private:
      Ptr<TextureManager> _textureManager;
      FontHandleMap<Unique<Font>> _fonts;
      Map<string, FontHandle> _fontNames;
      FontHandleManager _fontHandles;
  };
}