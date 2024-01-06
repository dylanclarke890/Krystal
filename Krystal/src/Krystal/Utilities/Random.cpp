#include "krys-pch.h"
#include "Krystal/Utilities/Random.h"

namespace Krys
{
  std::mt19937 Random::s_RandomEngine;
  std::uniform_int_distribution<std::mt19937::result_type> Random::s_Distribution;
}
