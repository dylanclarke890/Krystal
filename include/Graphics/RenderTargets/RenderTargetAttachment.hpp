#pragma once

#include "Graphics/Handles.hpp"

namespace Krys::Gfx
{
  /// @brief Describes how the attachment should be loaded at the beginning of the render pass.
  enum class AttachmentLoadOp
  {
    /// @brief Retains the contents of the attachment.
    Load,

    /// @brief Clears the contents of the attachment.
    Clear,

    /// @brief Undefined behavior, for optimisation purposes.
    DontCare
  };

  /// @brief Describes how the attachment should be stored at the end of the render pass.
  enum class AttachmentStoreOp
  {
    /// @brief Stores the contents of the attachment.
    Store,

    /// @brief Undefined behavior, for optimisation purposes.
    DontCare
  };

  /// @brief Describes a render target attachment.
  struct RenderTargetAttachment
  {
    /// @brief The target to which the attachment is bound.
    RenderTargetHandle Target;

    /// @brief The load operation to perform on the attachment at the beginning of the render pass.
    AttachmentLoadOp LoadOperation = AttachmentLoadOp::Clear;

    /// @brief The store operation to perform on the attachment at the end of the render pass.
    AttachmentStoreOp StoreOperation = AttachmentStoreOp::Store;
  };
}