#include "GLBuffer.h"

namespace Krys
{
  GLIndexBuffer::GLIndexBuffer(uint32 count)
  {
    glCreateBuffers(1, &Id);
    glNamedBufferData(Id, count * sizeof(uint32), 0, GL_STATIC_DRAW);
  }

  GLIndexBuffer::GLIndexBuffer(const uint32 *indices, uint32 count)
      : Id(0), Count(count)
  {
    glCreateBuffers(1, &Id);
    glNamedBufferData(Id, count * sizeof(uint32), indices, GL_STATIC_DRAW);
  }

  GLIndexBuffer::~GLIndexBuffer()
  {
    glDeleteBuffers(1, &Id);
  }

  void GLIndexBuffer::Bind()
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Id);
  }

  void GLIndexBuffer::Unbind()
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }

  void GLIndexBuffer::SetData(const uint32 *indices, uint32 count)
  {
    glNamedBufferSubData(Id, 0, count * sizeof(GLuint), indices);
  }

  uint GLIndexBuffer::Size()
  {
    return Count;
  }

  GLVertexBuffer::GLVertexBuffer(uint32 size)
      : Id(0)
  {
    glCreateBuffers(1, &Id);
    glNamedBufferData(Id, size, nullptr, GL_DYNAMIC_DRAW);
  }

  GLVertexBuffer::GLVertexBuffer(float *vertices, uint32 size)
      : Id(0)
  {
    glCreateBuffers(1, &Id);
    glNamedBufferData(Id, size, vertices, GL_STATIC_DRAW);
  }

  GLVertexBuffer::~GLVertexBuffer()
  {
    glDeleteBuffers(1, &Id);
  }

  void GLVertexBuffer::Bind()
  {
    glBindBuffer(GL_ARRAY_BUFFER, Id);
  }

  void GLVertexBuffer::Unbind()
  {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  void GLVertexBuffer::SetData(const void *data, uint32 size)
  {
    glNamedBufferSubData(Id, 0, size, data);
  }

  const VertexBufferLayout &GLVertexBuffer::GetLayout() const
  {
    return Layout;
  }

  void GLVertexBuffer::SetLayout(const VertexBufferLayout &layout)
  {
    Layout = layout;
  }

  GLUniformBuffer::GLUniformBuffer(uint32 size, uint32 binding)
  {
    glCreateBuffers(1, &Id);
    glNamedBufferData(Id, size, nullptr, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, binding, Id);
  }

  Krys::GLUniformBuffer::GLUniformBuffer(uint32 binding, UniformBufferLayout layout)
  {
    glCreateBuffers(1, &Id);

    SetLayout(layout);
    glNamedBufferData(Id, layout.GetSize(), nullptr, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, binding, Id);
  }

  GLUniformBuffer::~GLUniformBuffer()
  {
    glDeleteBuffers(1, &Id);
  }

  void GLUniformBuffer::Bind()
  {
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
  }

  void GLUniformBuffer::SetData(const string &name, bool value)
  {
    auto info = GetAttributeInfo(name);
    KRYS_ASSERT(info.Found, "Unable to find element in layout with name %s", name.c_str());
    int paddedValue = value;
    glNamedBufferSubData(Id, info.Offset, info.Size, &paddedValue);
  }

  void GLUniformBuffer::SetData(const string &name, int value)
  {
    auto info = GetAttributeInfo(name);
    KRYS_ASSERT(info.Found, "Unable to find element in layout with name %s", name.c_str());
    glNamedBufferSubData(Id, info.Offset, info.Size, &value);
  }

  void GLUniformBuffer::SetData(const string &name, size_t value)
  {
    auto info = GetAttributeInfo(name);
    KRYS_ASSERT(info.Found, "Unable to find element in layout with name %s", name.c_str());
    glNamedBufferSubData(Id, info.Offset, info.Size, &value);
  }

  void GLUniformBuffer::SetData(const string &name, float value)
  {
    auto info = GetAttributeInfo(name);
    KRYS_ASSERT(info.Found, "Unable to find element in layout with name %s", name.c_str());
    glNamedBufferSubData(Id, info.Offset, info.Size, &value);
  }

  void GLUniformBuffer::SetData(const string &name, const Vec2 &value)
  {
    auto info = GetAttributeInfo(name);
    KRYS_ASSERT(info.Found, "Unable to find element in layout with name %s", name.c_str());
    glNamedBufferSubData(Id, info.Offset, info.Size, &value);
  }

  void GLUniformBuffer::SetData(const string &name, const Vec3 &value)
  {
    auto info = GetAttributeInfo(name);
    KRYS_ASSERT(info.Found, "Unable to find element in layout with name %s", name.c_str());
    Vec4 paddedValue = {value, 0.0f};
    glNamedBufferSubData(Id, info.Offset, info.Size, &paddedValue);
  }

  void GLUniformBuffer::SetData(const string &name, const Vec4 &value)
  {
    auto info = GetAttributeInfo(name);
    KRYS_ASSERT(info.Found, "Unable to find element in layout with name %s", name.c_str());
    glNamedBufferSubData(Id, info.Offset, info.Size, &value);
  }

  void GLUniformBuffer::SetData(const string &name, const Mat3 &value)
  {
    KRYS_ASSERT(false, "TODO: Implement me!", 0);
  }

  void GLUniformBuffer::SetData(const string &name, const Mat4 &value)
  {
    auto info = GetAttributeInfo(name);
    KRYS_ASSERT(info.Found, "Unable to find element in layout with name %s", name.c_str());
    glNamedBufferSubData(Id, info.Offset, info.Size, &value);
  }

  GLUniformBuffer::AttributeInfo GLUniformBuffer::GetAttributeInfo(const string &name) const noexcept
  {
    size_t bracketOpenPos = name.find("[");
    size_t dotPos = name.find(".");
    if (bracketOpenPos != string::npos && (dotPos == string::npos || bracketOpenPos < dotPos))
    {
      // Handle arrays
      string arrayName = name.substr(0, bracketOpenPos);
      size_t bracketClosePos = name.find("]");
      uint32 arrayIndex = std::stoi(name.substr(bracketOpenPos + 1, bracketClosePos - bracketOpenPos - 1));
      string remaining = name.substr(bracketClosePos + 1);

      for (const auto &element : Layout)
        if (element.Name == arrayName)
        {
          auto elementSize = element.LayoutSize;
          auto offset = element.AlignedOffset + elementSize * arrayIndex;
          GLUniformBuffer::AttributeInfo info = {offset, elementSize};

          if (!remaining.empty() && remaining[0] == '.')
            return GetAttributeInfo(remaining.substr(1), element.Layout, info);
          return info;
        }
    }
    else if (dotPos != string::npos)
    {
      // Handle nested structures
      string structName = name.substr(0, dotPos);
      string remaining = name.substr(dotPos + 1);

      for (const auto &element : Layout)
        if (element.Name == structName)
        {
          GLUniformBuffer::AttributeInfo attributeInfo = {element.AlignedOffset, 0};
          return GetAttributeInfo(remaining, element.Layout, attributeInfo);
        }
    }
    else
    {
      for (const auto &element : Layout)
        if (element.Name == name)
          return {element.AlignedOffset, element.LayoutSize, true};
    }

    return {};
  }

  GLUniformBuffer::AttributeInfo GLUniformBuffer::GetAttributeInfo(const string &name, UniformStructLayout layout, AttributeInfo info) const noexcept
  {
    size_t bracketOpenPos = name.find("[");
    size_t dotPos = name.find(".");

    // Handle array case
    if (bracketOpenPos != string::npos && (dotPos == string::npos || bracketOpenPos < dotPos))
    {
      string arrayName = name.substr(0, bracketOpenPos);
      size_t bracketClosePos = name.find("]");
      uint32 arrayIndex = std::stoi(name.substr(bracketOpenPos + 1, bracketClosePos - bracketOpenPos - 1));
      string remaining = name.substr(bracketClosePos + 1);

      for (const auto &element : layout)
      {
        if (element.Name == arrayName)
        {
          auto elementSize = element.LayoutSize;
          auto offset = info.Offset + element.AlignedOffset + elementSize * arrayIndex;
          info.Offset = offset;
          info.Size = elementSize;
          info.Found = true;

          return info;
        }
      }

      KRYS_ASSERT(false, "Unexpected attribute: %s", name.c_str());
    }
    else
    {
      for (const auto &element : layout)
      {
        if (element.Name == name)
        {
          info.Offset += element.AlignedOffset;
          info.Size = element.LayoutSize;
          info.Found = true;
          return info;
        }
      }
    }

    return info;
  }

  const UniformBufferLayout &GLUniformBuffer::GetLayout() const
  {
    return Layout;
  }

  void GLUniformBuffer::SetLayout(const UniformBufferLayout &layout)
  {
    KRYS_ASSERT(layout.GetElements().size(), "Uniform buffer has no layout!", 0);
    Layout = layout;
  }

  GLInstanceArrayBuffer::GLInstanceArrayBuffer(uint32 size)
  {
    glCreateBuffers(1, &Id);
    glNamedBufferData(Id, size, nullptr, GL_DYNAMIC_DRAW);
  }

  GLInstanceArrayBuffer::GLInstanceArrayBuffer(void *data, uint32 size)
  {
    glCreateBuffers(1, &Id);
    glNamedBufferData(Id, size, data, GL_DYNAMIC_DRAW);
  }

  GLInstanceArrayBuffer::~GLInstanceArrayBuffer()
  {
    glDeleteBuffers(1, &Id);
  }

  void GLInstanceArrayBuffer::Bind()
  {
    glBindBuffer(GL_ARRAY_BUFFER, Id);
  }

  void GLInstanceArrayBuffer::Unbind()
  {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  void GLInstanceArrayBuffer::SetData(const void *data, uint32 size)
  {
    glNamedBufferSubData(Id, 0, size, data);
  }

  const InstanceArrayBufferLayout &GLInstanceArrayBuffer::GetLayout() const
  {
    return Layout;
  }

  void GLInstanceArrayBuffer::SetLayout(const InstanceArrayBufferLayout &layout)
  {
    Layout = layout;
  }
}
