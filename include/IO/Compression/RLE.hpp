#pragma once

#include "Base/Types.hpp"

namespace Krys::IO::Stage
{
  struct RLEEncoder
  {
    using input_t = const List<byte> &;
    using output_t = List<byte>;

    constexpr void Setup() noexcept
    {
    }

    constexpr output_t ProcessChunk(input_t data) noexcept
    {
      output_t output {};
      output.reserve(data.size());

      int count = 1;
      byte last = data[0];
      for (size_t i = 1; i < data.size(); i++)
      {
        const byte current = data[i];
        if (current == last)
          count++;
        else
        {
          while (count > 255)
          {
            output.push_back(static_cast<byte>(255));
            output.push_back(last);
            count -= 255;
          }

          output.push_back(static_cast<byte>(count));
          output.push_back(last);
          last = current;
          count = 1;
        }
      }

      output.push_back(static_cast<byte>(count));
      output.push_back(last);

      return output;
    }

    constexpr void Teardown() noexcept
    {
    }
  };

  struct RLEDecoder
  {
    using input_t = const List<byte> &;
    using output_t = List<byte>;

    constexpr void Setup() noexcept
    {
    }

    constexpr output_t ProcessChunk(input_t data) noexcept
    {
      output_t output {};
      output.reserve(data.size());

      for (size_t i = 0; i < data.size(); i += 2)
      {
        const int count = static_cast<int>(data[i]);
        const byte value = data[i + 1];
        for (int j = 0; j < count; j++)
          output.push_back(value);
      }

      return output;
    }

    constexpr void Teardown() noexcept
    {
    }
  };
}