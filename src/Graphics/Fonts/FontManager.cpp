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
    KRYS_SCOPED_PROFILER("FontManager::LoadFont");
    KRYS_ASSERT(!path.empty(), "Font path cannot be empty");

    FT_Face face;

    auto error = FT_New_Face(library, path.c_str(), 0, &face);
    (void)error;
    KRYS_ASSERT(error == 0, "Failed to create FreeType face");
    Logger::Info("FreeType face created successfully: {}", path);

    FT_Set_Pixel_Sizes(face, 0, settings.Size);

    auto handle = _fontHandles.Next();
    auto font = CreateUnique<Font>(path, handle);

    error = FT_Load_Char(face, 'A', FT_LOAD_RENDER);
    (void)error;
    KRYS_ASSERT(error == 0, "Failed to load character 'A' from font: {}", path);

    TextureDescriptor textureDescriptor;
    textureDescriptor.Name = path + "_A";
    textureDescriptor.Width = face->glyph->bitmap.width;
    textureDescriptor.Height = face->glyph->bitmap.rows;
    textureDescriptor.Channels = 4;

    SamplerDescriptor samplerDescriptor;
    samplerDescriptor.MinFilter = SamplerFilter::Linear;
    samplerDescriptor.MagFilter = SamplerFilter::Linear;
    samplerDescriptor.AddressModeS = SamplerAddressMode::ClampToEdge;
    samplerDescriptor.AddressModeT = SamplerAddressMode::ClampToEdge;

    List<byte> rgbaData(textureDescriptor.Width * textureDescriptor.Height * 4);
    const byte *src = reinterpret_cast<byte*>(face->glyph->bitmap.buffer);

    for (uint y = 0; y < textureDescriptor.Height; y++)
    {
      for (uint x = 0; x < textureDescriptor.Width; x++)
      {
        int dstIdx = (y * textureDescriptor.Width + x) * 4;
        int srcIdx = y * face->glyph->bitmap.pitch + x; // account for pitch (row stride)

        byte alpha = src[srcIdx];
        rgbaData[dstIdx + 0] = byte{255};   // R
        rgbaData[dstIdx + 1] = byte {255};  // G
        rgbaData[dstIdx + 2] = byte {255};  // B
        rgbaData[dstIdx + 3] = alpha; // A (from FreeType)
      }
    }

    textureDescriptor.Sampler = _textureManager->CreateSampler(samplerDescriptor);
    font->_glyphs["A"] = Glyph {
      .Texture = _textureManager->CreateTexture(textureDescriptor, rgbaData),
      .Size = Vec2i(face->glyph->bitmap.width, face->glyph->bitmap.rows),
      .Bearing = Vec2i(face->glyph->bitmap_left, face->glyph->bitmap_top),
      .Advance = face->glyph->advance.x,
      .OffsetX = static_cast<float>(face->glyph->bitmap_left) / settings.Size,
      .OffsetY = static_cast<float>(face->glyph->bitmap_top) / settings.Size,
    };

    _fonts.emplace(handle, std::move(font));
    _fontNames.emplace(path, handle);

    return handle;
  }
}