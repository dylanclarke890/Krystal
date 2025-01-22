#pragma once

#include "Base/Types.hpp"

namespace Krys::Impl
{
  /// @brief Helper function to combine the hash values of supplied objects (using std::hash).
  /// @tparam Head The type of the first object.
  /// @tparam Tail The types of the remaining objects.
  /// @param seed The initial hash value, will be set to the combined hash value.
  /// @param head The first object.
  /// @param tail The remaining objects.
  template <class Head, class... Tail>
  void HashCombine(std::size_t &seed, const Head &head, Tail... tail)
  {
    // this algorithm is based on boost::combine_hash and is designed to mix/smear around values
    seed ^= std::hash<Head> {}(head) + 0x9e'37'79'b9'7f'4a'7c'55 + (seed << 6) + (seed >> 2);
    (HashCombine(seed, tail), ...);
  }
}

namespace Krys
{
  /// @brief Combines the hash values of supplied objects (using std::hash).
  /// @tparam Args The types of the objects to hash.
  /// @param args The objects to hash.
  /// @return The combined hash value of all objects.
  template <class... Args>
  size_t HashCombine(Args... args)
  {
    size_t seed = 0u;
    Impl::HashCombine(seed, args...);
    return seed;
  }
}