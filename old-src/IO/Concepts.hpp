#pragma once

#include "Base/Concepts.hpp"
#include "Base/Types.hpp"

namespace Krys::IO
{
  template <typename T>
  concept IsDataSourceT = requires(T source) {
    { source.Open() } -> Same<void>;
    { source.Close() } -> Same<void>;
    { source.IsEOS() } -> Same<bool>;
    { source.ReadBytes(0) } -> Same<List<byte>>;
    requires requires {
      { source.template Read<int>() } -> Same<int>;
    };
    requires requires {
      { source.template Read<int>(10) } -> Same<List<int>>;
    };
  };

  template <typename T>
  concept IsDataSinkT = requires(T sink) {
    { sink.Open() } -> Same<void>;
    { sink.Close() } -> Same<void>;
    { sink.WriteBytes(List<byte>()) } -> Same<void>;
    requires requires {
      { sink.template Write<int>(0) } -> Same<void>;
    };
    requires requires {
      { sink.template Write<int>(List<int>()) } -> Same<void>;
    };
  };

  template <typename T>
  concept IsDataFlowStageT = requires(T stage) {
    typename T::input_t;
    typename T::output_t;
    // {
    //   stage.ProcessChunk(std::declval<DataFlowStageContext<typename T::input_t, typename T::output_t>>())
    // } -> Same<typename T::output_t>;
  };
}