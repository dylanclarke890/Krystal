#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Macros.hpp"
#include "Base/Pointers.hpp"
#include "Base/Types.hpp"
#include "Core/Debug/Macros.hpp"
#include "IO/DataFlowStage.hpp"

#include <tuple>

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

  template <IsDataSourceT TSource, IsDataSinkT TSink, IsDataFlowStageT... TStages>
  class DataFlow
  {
    using stages_t = std::tuple<TStages...>;

  public:
    constexpr DataFlow(TSource *source, TSink *sink, uint chunkSize = 1'024 * 32, TStages... stages) noexcept
        : _source(source), _sink(sink), _chunkSize(chunkSize), _stages(std::move(stages)...)
    {
    }

    template <typename... UStages>
    constexpr DataFlow(TSource *source, TSink *sink, uint chunkSize, std::tuple<UStages...> st) noexcept
        : _source(source), _sink(sink), _chunkSize(chunkSize), _stages(std::move(st))
    {
    }

    ~DataFlow() noexcept = default;
    constexpr DataFlow(const DataFlow &) = delete;
    constexpr DataFlow &operator=(const DataFlow &) = delete;

    /// @brief Append a stage to the pipeline.
    template <IsDataFlowStageT TStage>
    constexpr auto operator|(TStage stage) const noexcept
    {
      return DataFlow<TSource, TSink, TStages..., TStage>(_source, _sink, _chunkSize,
                                                          std::tuple_cat(_stages, std::make_tuple(stage)));
    }

    constexpr void Execute() noexcept
    {
      KRYS_SCOPED_PROFILER("DataFlow::Execute");
      KRYS_ASSERT(_source, "No source has been set.", 0);
      KRYS_ASSERT(_sink, "No sink has been set.", 0);

      _source->Open();
      _sink->Open();

      ApplyToStages([](auto &stage) { stage.Setup(); });

      _bytesProcessed = 0;
      _totalBytesToProcess = static_cast<uint>(_source->GetSize());
      KRYS_ASSERT(_totalBytesToProcess != 0, "Source is empty.", 0);

      while (true)
      {
        auto bytes = _source->ReadBytes(_chunkSize);
        if (bytes.empty() && _source->IsEOS())
          break;

        _isLastChunk = _bytesProcessed + static_cast<uint>(bytes.size()) == _totalBytesToProcess;

        auto data = ProcessStages(bytes);
        _bytesProcessed += static_cast<uint>(bytes.size());
        _sink->Write(data);

        _isFirstChunk = false;
      }

      ApplyToStages([](auto &stage) { stage.Teardown(); });

      _source->Close();
      _sink->Close();
    }

  private:
    template <typename TInput>
    constexpr auto ProcessStages(const TInput &data) noexcept
    {
      return ApplyStages<0>(data);
    }

    template <size_t Index, typename TInput>
    constexpr auto ApplyStages(const TInput &data) noexcept
    {
      if constexpr (Index < sizeof...(TStages))
      {
        using current_stage_t = std::tuple_element_t<Index, stages_t>;
        auto &stage = std::get<Index>(_stages);

        DataFlowStageContext<TInput, typename current_stage_t::output_t> context {};
        context.Input = data;
        context.IsFirstChunk = _isFirstChunk;
        context.IsLastChunk = _isLastChunk;
        context.TotalBytesToProcess = _totalBytesToProcess;
        context.BytesProcessed = _bytesProcessed;

        auto transformedData = stage.ProcessChunk(context);
        return ApplyStages<Index + 1>(transformedData);
      }
      else
      {
        return data; // Final transformed data
      }
    }

    template <typename Func>
    constexpr void ApplyToStages(Func func) noexcept
    {
      std::apply([&](auto &...stages) { (func(stages), ...); }, _stages);
    }

  private:
    TSource *_source;
    TSink *_sink;
    stages_t _stages;
    uint _chunkSize, _totalBytesToProcess, _bytesProcessed;
    bool _isFirstChunk = true, _isLastChunk = false;
  };
}

namespace Krys::IO::Stage
{
  template <typename T>
  struct Identity
  {
  public:
    using input_t = T;
    using output_t = T;

    constexpr void Setup() noexcept
    {
    }

    constexpr output_t ProcessChunk(DataFlowStageContext<input_t, output_t> &context) noexcept
    {
      return context.Input;
    }

    constexpr void Teardown() noexcept
    {
    }
  };
}