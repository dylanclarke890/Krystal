#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Endian.hpp"
#include "Base/Types.hpp"

namespace Krys::IO
{
  template <IsIntegralT TCode>
  class HuffmanDecoder
  {
  public:
    HuffmanDecoder(const string &fileIn, const string &fileOut, const HuffmanTree<TCode> &tree) noexcept
        : _fileIn(fileIn), _fileOut(fileOut), _tree(tree)
    {
    }

    NO_DISCARD void Decode() const noexcept
    {
      binary_reader_t reader(_fileIn);
      reader.OpenStream();
      auto sizeInBits = reader.Read<uint32>();
      auto data = reader.ReadAllBytes();
      reader.CloseStream();

      if (!sizeInBits && data.empty())
        return;

      KRYS_ASSERT(sizeInBits && !data.empty(), "Invalid format", 0);

      auto root = _tree.GetRoot();
      KRYS_ASSERT(root, "Tree was not initialised", 0);
      auto current = root;
      List<uchar> decoded;

      if (sizeInBits == 1)
      {
        decoded.emplace_back(static_cast<uchar>(root->Symbol));
        binary_writer_t writer(_fileOut);
        writer.OpenStream();
        writer.Write(decoded);
        writer.CloseStream();
        return;
      }

      size_t i = 0;
      while (i < sizeInBits)
      {
        uchar character = static_cast<uchar>(data[i / 8]);
        for (uint j = 0; j < 8; j++)
        {
          if (i >= sizeInBits)
            break;

          bool bit = (character >> j) & 1;
          current = bit ? current->Right : current->Left;

          if (!current->Left && !current->Right) // Leaf node reached
          {
            decoded.emplace_back(static_cast<uchar>(current->Symbol));
            current = root; // Reset to the root for the next symbol
          }
          i++;
        }
      }

      binary_writer_t writer(_fileOut);
      writer.OpenStream();
      writer.Write(decoded);
      writer.CloseStream();
    }

  private:
    string _fileIn, _fileOut;
    HuffmanTree<TCode> _tree;
  };
}