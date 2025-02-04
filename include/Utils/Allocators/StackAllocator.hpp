#pragma once

#include "Base/Types.hpp"

// TODO: implement this
namespace Krys::Allocators
{
  class StackAllocator
  {
  private:
  public:
    explicit StackAllocator(uint32 stackSizeInBytes);

    // TODO: templates?
    void *Alloc(uint32 sizeInBytes);
  };
}