#pragma once

#include "Base/Types.hpp"
#include "Debug/Macros.hpp"
#include "IO/DataFlowStage.hpp"

namespace Krys::IO::Stage
{
  struct RLEEncoder
  {
    using input_t = List<byte>;
    using output_t = List<byte>;

    constexpr output_t ProcessChunk(DataFlowStageContext<input_t, output_t> &context) noexcept
    {
      const auto &data = context.Input;

      output_t output {};
      output.reserve(data.size());

      int begin = 0;
      if (context.IsFirstChunk)
      {
        _count = 1;
        _last = data[0];
        begin = 1;
      }

      for (size_t i = begin; i < data.size(); i++)
      {
        const byte current = data[i];
        if (current == _last)
          _count++;
        else
        {
          while (_count > 255)
          {
            output.push_back(static_cast<byte>(255));
            output.push_back(_last);
            _count -= 255;
          }

          output.push_back(static_cast<byte>(_count));
          output.push_back(_last);
          _last = current;
          _count = 1;
        }
      }

      if (context.IsLastChunk && _count > 0)
      {
        output.push_back(static_cast<byte>(_count));
        output.push_back(_last);
      }

      return output;
    }

  private:
    byte _last {};
    int _count {};
  };

  struct RLEDecoder
  {
    using input_t = List<byte>;
    using output_t = List<byte>;

    constexpr output_t ProcessChunk(DataFlowStageContext<input_t, output_t> &context) noexcept
    {
      const auto &data = context.Input;

      // Append new data to whatever was left over from previous chunk(s)
      _carry.insert(_carry.end(), data.begin(), data.end());

      output_t output;
      // Attempt to decode as many full pairs as possible
      std::size_t i = 0;
      while ((i + 1) < _carry.size())
      {
        // We have at least 2 bytes: decode the pair
        byte runCount = _carry[i++];
        byte runValue = _carry[i++];
        for (int j = 0; j < static_cast<int>(runCount); j++)
          output.push_back(runValue);
      }

      // Now i points to any leftover in _carry that did not form a complete pair
      // Move leftover bytes (if any) to the front of _carry
      if (i < _carry.size())
      {
        // We have 1 leftover byte that wasn't decoded yet
        // Shift it down to index 0
        _carry[0] = _carry[i];
        _carry.resize(_carry.size() - (i));
      }
      else
      {
        // No leftover: just clear the carry buffer
        _carry.clear();
      }

      // If this is the last chunk, we expect there to be no leftover
      // or exactly two leftover bytes. If there's exactly two leftover
      // bytes, we can decode one final run:
      if (context.IsLastChunk)
      {
        KRYS_ASSERT(_carry.size() == 0 || _carry.size() == 2, "Invalid ending for RLE data");
        if (_carry.size() == 2)
        {
          const byte runCount = _carry[0];
          const byte runValue = _carry[1];
          for (int j = 0; j < static_cast<int>(runCount); j++)
            output.push_back(runValue);
        }
      }

      return output;
    }

  private:
    // Carry buffer to hold partial [count, value] pairs across chunks
    List<byte> _carry;
  };
}