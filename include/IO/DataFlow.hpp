#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Macros.hpp"
#include "Base/Pointers.hpp"
#include "Base/Types.hpp"
#include "Core/Debug/Macros.hpp"

#include <tuple>

namespace Krys::IO
{
#pragma region Concepts

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
    { stage.Setup() } -> Same<void>;
    { stage.ProcessChunk(std::declval<typename T::input_t>()) } -> Same<typename T::output_t>;
    { stage.Teardown() } -> Same<void>;
  };

#pragma endregion Concepts

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

    void Execute() noexcept
    {
      KRYS_SCOPED_PROFILER("DataFlow::Execute");
      KRYS_ASSERT(_source, "No source has been set.", 0);
      KRYS_ASSERT(_sink, "No sink has been set.", 0);

      _source->Open();
      _sink->Open();

      ApplyToStages([](auto &stage) { stage.Setup(); });

      KRYS_ASSERT(_source->GetSize() != 0, "Source is empty.", 0);
      while (!_source->IsEOS())
      {
        auto bytes = _source->ReadBytes(_chunkSize);
        KRYS_ASSERT(!bytes.empty(), "No data was read from the source.", 0);

        auto data = ProcessStages(bytes);
        _sink->Write(data);
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
        using currentStage = std::tuple_element_t<Index, stages_t>;
        auto &stage = std::get<Index>(_stages);
        auto transformedData = stage.ProcessChunk(data);
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
    uint _chunkSize;
    stages_t _stages;
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

    constexpr output_t ProcessChunk(input_t data) noexcept
    {
      return data;
    }

    constexpr void Teardown() noexcept
    {
    }
  };
}