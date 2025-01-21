#pragma once

#include "Base/Concepts.hpp"
#include "Base/Types.hpp"
#include "IO/Concepts.hpp"

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
}