#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Macros.hpp"
#include "Base/Pointers.hpp"
#include "Base/Types.hpp"
#include "Core/Debug/Macros.hpp"

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
  concept IsDataFlowStageT = requires {
    typename T::input_t;
    typename T::output_t;

    { T::Setup() } -> Same<void>;
    { T::Teardown() } -> Same<void>;

    // Stage must have an Execute method with the correct signature
    requires std::invocable<decltype(&T::Execute), typename T::input_t>;
  };
#pragma endregion Concepts

  template <IsDataSourceT TSource, IsDataSinkT TSink, IsDataFlowStageT... TStages>
  class DataFlow
  {
    using data_flow_t = DataFlow<TSource, TSink, TStages...>;

  public:
    explicit constexpr DataFlow(TSource *source, TSink *sink, uint chunkSize = 1'024) noexcept
        : _source(source), _sink(sink), _chunkSize(chunkSize)
    {
    }

    ~DataFlow() noexcept = default;

    constexpr DataFlow(const DataFlow &) = delete;
    constexpr DataFlow &operator=(const DataFlow &) = delete;

    /// @brief Append a stage to the pipeline.
    template <IsDataFlowStageT TStage>
    constexpr auto operator|(TStage) const noexcept
    {
      return DataFlow<TSource, TSink, TStages..., TStage>(_source, _sink, _chunkSize);
    }

    void Execute() noexcept
    {
      KRYS_ASSERT(_source, "No source has been set.", 0);
      KRYS_ASSERT(_sink, "No sink has been set.", 0);

      _source->Open();
      _sink->Open();

      KRYS_ASSERT(_source->GetSize() != 0, "Source is empty.", 0);
      while (!_source->IsEOS())
      {
        auto bytes = _source->ReadBytes(_chunkSize);
        KRYS_ASSERT(!bytes.empty(), "No data was read from the source.", 0);

        auto data = ProcessStages(bytes);
        _sink->Write(data);
      }

      _source->Close();
      _sink->Close();
    }

  private:
    template <typename TInput>
    auto ProcessStages(const TInput &data) const noexcept
    {
      return ApplyStages<0>(data);
    }

    template <size_t Index, typename TInput>
    auto ApplyStages(const TInput &data) const noexcept
    {
      if constexpr (Index < sizeof...(TStages))
      {
        using currentStage = std::tuple_element_t<Index, std::tuple<TStages...>>;
        auto transformedData = currentStage::Execute(data);
        return ApplyStages<Index + 1>(transformedData);
      }
      else
      {
        return data; // Final transformed data
      }
    }

  private:
    TSource *_source;
    TSink *_sink;
    uint _chunkSize;
  };
}

namespace Krys::IO::Stage
{
  template <typename TInput, typename TOutput>
  struct Identity
  {
  public:
    using input_t = TInput;
    using output_t = TOutput;

    constexpr static void Setup() noexcept
    {
    }

    constexpr static TOutput Execute(TInput data) noexcept
    {
      return data;
    }

    constexpr static void Teardown() noexcept
    {
    }
  };
}