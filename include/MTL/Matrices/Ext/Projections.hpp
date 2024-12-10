#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Matrices/Base.hpp"

// TODO: unit tests
namespace Krys::MTL
{
  /// Map the specified object coordinates (obj.x, obj.y, obj.z) into window coordinates.
  /// The near and far clip planes correspond to z normalized device coordinates of 0 and +1 respectively.
  /// @param obj Object coordinates.
  /// @param model Current modelview matrix
  /// @param proj Current projection matrix
  /// @param viewport Current viewport
  /// @returns The computed window coordinates.
  /// @tparam TComponent A floating point type.
  /// @tparam U An arithmetic type.
  template <IsFloatingPointT TComponent, IsArithmeticT U>
  NO_DISCARD constexpr auto Project_ZO(vector_t<TComponent, 3> const &obj,
                                       matrix_t<TComponent, 4, 4> const &model,
                                       matrix_t<TComponent, 4, 4> const &proj,
                                       vector_t<U, 4> const &viewport) noexcept -> vector_t<TComponent, 3>
  {
    vector_t<TComponent, 4> tmp(obj.x, obj.y, obj.z, TComponent(1));
    tmp = model * tmp;
    tmp = proj * tmp;

    tmp /= tmp.w;
    tmp.x = tmp.x * TComponent(0.5) + TComponent(0.5);
    tmp.y = tmp.y * TComponent(0.5) + TComponent(0.5);

    tmp[0] = tmp[0] * TComponent(viewport[2]) + TComponent(viewport[0]);
    tmp[1] = tmp[1] * TComponent(viewport[3]) + TComponent(viewport[1]);

    return vector_t<TComponent, 3>(tmp);
  }

  /// Map the specified object coordinates (obj.x, obj.y, obj.z) into window coordinates.
  /// The near and far clip planes correspond to z normalized device coordinates of -1 and +1 respectively.
  /// @param obj Object coordinates.
  /// @param model Current modelview matrix
  /// @param proj Current projection matrix
  /// @param viewport Current viewport
  /// @returns The computed window coordinates.
  /// @tparam TComponentT A floating point type.
  /// @tparam U An arithmetic type.
  template <IsFloatingPointT TComponent, IsArithmeticT U>
  NO_DISCARD constexpr auto Project_NO(vector_t<TComponent, 3> const &obj,
                                       matrix_t<TComponent, 4, 4> const &model,
                                       matrix_t<TComponent, 4, 4> const &proj, vector_t<U, 4> const &viewport)
  {
    vector_t<TComponent, 4> tmp(obj.x, obj.y, obj.z, TComponent(1));
    tmp = model * tmp;
    tmp = proj * tmp;

    tmp /= tmp.w;
    tmp = tmp * TComponent(0.5) + TComponent(0.5);
    tmp[0] = tmp[0] * TComponent(viewport[2]) + TComponent(viewport[0]);
    tmp[1] = tmp[1] * TComponent(viewport[3]) + TComponent(viewport[1]);

    return vector_t<TComponent, 3>(tmp);
  }

  /// Map the specified object coordinates (obj.x, obj.y, obj.z) into window coordinates.
  /// @param obj Object coordinates.
  /// @param model Current modelview matrix
  /// @param proj Current projection matrix
  /// @param viewport Current viewport
  /// @returns The computed window coordinates.
  /// @tparam T A floating point type.
  /// @tparam U An arithmetic type.
  template <IsFloatingPointT T, IsArithmeticT U>
  NO_DISCARD constexpr vector_t<T, 3> Project(vector_t<T, 3> const &obj, matrix_t<T, 4, 4> const &model,
                                              matrix_t<T, 4, 4> const &proj, vector_t<U, 4> const &viewport)
  {
#if KRYS_MATRIX_DEPTH_RANGE == KRYS_MATRIX_DEPTH_RANGE_ZERO_TO_ONE
    return Project_ZO(obj, model, proj, viewport);
#else
    return Project_NO(obj, model, proj, viewport);
#endif
  }
}