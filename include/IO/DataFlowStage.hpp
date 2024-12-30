#pragma once

#include "Base/Concepts.hpp"
#include "Base/Types.hpp"

namespace Krys::IO
{
  template <typename TInput, typename TOutput>
  struct DataFlowStageContext
  {
    bool IsFirstChunk {true}, IsLastChunk {false};
    int32 TotalBytesToProcess {0}, BytesProcessed {0};
    TInput Input {};
    TOutput Output {};
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