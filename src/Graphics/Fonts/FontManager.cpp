#include "Graphics/Fonts/FontManager.hpp"
#include "Graphics/Fonts/Font.hpp"
#include "Graphics/Textures/TextureManager.hpp"
#include <ft2build.h>
#include FT_FREETYPE_H

namespace Krys::Gfx
{
  static FT_Library library;

  FontManager::FontManager(Ptr<TextureManager> textureManager) noexcept : _textureManager(textureManager)
  {
    auto error = FT_Init_FreeType(&library);
    (void)error;
    KRYS_ASSERT(error == 0, "Failed to initialize FreeType library");
    Logger::Info("FreeType library initialized successfully");
  }

  FontManager::~FontManager() noexcept
  {
    FT_Done_FreeType(library);
  }

  FontHandle FontManager::LoadFont(const string &path, FontSettings settings) noexcept
  {
    KRYS_SCOPED_PROFILER(std::format("FontManager::LoadFont {0}", path));
    KRYS_ASSERT(!path.empty(), "Font path cannot be empty");

    SamplerDescriptor samplerDescriptor;
    samplerDescriptor.MinFilter = SamplerFilter::Linear;
    samplerDescriptor.MagFilter = SamplerFilter::Linear;
    samplerDescriptor.AddressModeS = SamplerAddressMode::ClampToEdge;
    samplerDescriptor.AddressModeT = SamplerAddressMode::ClampToEdge;
    _sampler = _textureManager->CreateSampler(samplerDescriptor);

    FT_Face face;
    FT_Error error;

    error = FT_New_Face(library, path.c_str(), 0, &face);
    (void)error;
    KRYS_ASSERT(error == 0, "Failed to create FreeType face");
    Logger::Info("FreeType face created successfully: {}", path);

    FT_Set_Pixel_Sizes(face, 0, settings.Size);

    auto handle = _fontHandles.Next();
    auto font = CreateUnique<Font>(path, handle);

    for (uchar character = 0; character < 128; character++)
    {
      char c = static_cast<char>(character);
      error = FT_Load_Char(face, c, FT_LOAD_RENDER);
      (void)error;
      KRYS_ASSERT(error == 0, "Failed to load character '{}' from font: {}", c, path);

      TextureDescriptor textureDescriptor;
      textureDescriptor.Type = TextureType::Font;
      textureDescriptor.Name = std::format("{}_{}", path, c);
      textureDescriptor.Width = face->glyph->bitmap.width;
      textureDescriptor.Height = face->glyph->bitmap.rows;
      textureDescriptor.Channels = 1;
      textureDescriptor.Sampler = _sampler;

      uint32 size = textureDescriptor.Width * textureDescriptor.Height;
      auto glyph = Glyph {
        .Texture = {},
        .Size = Vec2i(face->glyph->bitmap.width, face->glyph->bitmap.rows),
        .Bearing = Vec2i(face->glyph->bitmap_left, face->glyph->bitmap_top),
        .Advance = (int32)((float)face->glyph->advance.x / 64.0f),
        .OffsetX = static_cast<float>(face->glyph->bitmap_left) / settings.Size,
        .OffsetY = static_cast<float>(face->glyph->bitmap_top) / settings.Size,
      };

      if (size > 0)
      {
        List<byte> data(size);
        memcpy(data.data(), reinterpret_cast<byte *>(face->glyph->bitmap.buffer), size);

        glyph.Texture = _textureManager->CreateTexture(textureDescriptor, data);
      }

      font->_glyphs[std::string(1, c)] = glyph;
    }

    FT_Done_Face(face);

    _fonts.emplace(handle, std::move(font));
    _fontNames.emplace(path, handle);

    return handle;
  }
}