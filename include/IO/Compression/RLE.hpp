#pragma once

#include "Base/Types.hpp"

namespace Krys::IO::Stage
{
  struct RLEEncoder
  {
    using input_t = List<byte>;
    using output_t = List<byte>;

    constexpr void Setup() noexcept
    {
    }

    constexpr List<byte> Execute(const List<byte> &data) noexcept
    {
      List<byte> output {};
      output.reserve(data.size());

      int count = 1;
      byte lastByte = data[0];
      for (size_t i = 1; i < data.size(); i++)
      {
        if (data[i] == lastByte)
        {
          count++;
        }
        else
        {
          output.push_back(static_cast<byte>(count));
          output.push_back(lastByte);
          lastByte = data[i];
          count = 1;
        }
      }

      output.push_back(static_cast<byte>(count));
      output.push_back(lastByte);

      return output;
    }

    constexpr void Teardown() noexcept
    {
    }
  };

  struct RLEDecoder
  {
    using input_t = List<byte>;
    using output_t = List<byte>;

    static constexpr void Setup() noexcept
    {
    }

    static constexpr List<byte> Execute(const List<byte> &data) noexcept
    {
      List<byte> output {};
      output.reserve(data.size());

      for (size_t i = 0; i < data.size(); i += 2)
      {
        int count = static_cast<int>(data[i]);
        byte value = data[i + 1];
        for (int j = 0; j < count; j++)
        {
          output.push_back(value);
        }
      }

      return output;
    }

    static constexpr void Teardown() noexcept
    {
    }
  };
}