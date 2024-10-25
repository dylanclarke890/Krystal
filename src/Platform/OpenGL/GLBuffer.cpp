#include "OpenGL/GLBuffer.h"

namespace Krys::OpenGL
{
  GLIndexBuffer::GLIndexBuffer(uint32 count)
  {
    glCreateBuffers(1, &_id);
    glNamedBufferData(_id, count * sizeof(uint32), 0, GL_STATIC_DRAW);
  }

  GLIndexBuffer::GLIndexBuffer(const uint32 *indices, uint32 count) : _id(0), _count(count)
  {
    glCreateBuffers(1, &_id);
    glNamedBufferData(_id, count * sizeof(uint32), indices, GL_STATIC_DRAW);
  }

  GLIndexBuffer::~GLIndexBuffer()
  {
    glDeleteBuffers(1, &_id);
  }

  void GLIndexBuffer::Bind()
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id);
  }

  void GLIndexBuffer::Unbind()
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }

  void GLIndexBuffer::SetData(const uint32 *indices, uint32 count)
  {
    glNamedBufferSubData(_id, 0, count * sizeof(GLuint), indices);
  }

  uint GLIndexBuffer::Size()
  {
    return _count;
  }

  GLVertexBuffer::GLVertexBuffer(uint32 size) : _id(0)
  {
    glCreateBuffers(1, &_id);
    glNamedBufferData(_id, size, nullptr, GL_DYNAMIC_DRAW);
  }

  GLVertexBuffer::GLVertexBuffer(float *vertices, uint32 size) : _id(0)
  {
    glCreateBuffers(1, &_id);
    glNamedBufferData(_id, size, vertices, GL_STATIC_DRAW);
  }

  GLVertexBuffer::~GLVertexBuffer()
  {
    glDeleteBuffers(1, &_id);
  }

  void GLVertexBuffer::Bind()
  {
    glBindBuffer(GL_ARRAY_BUFFER, _id);
  }

  void GLVertexBuffer::Unbind()
  {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  void GLVertexBuffer::SetData(const void *data, uint32 size)
  {
    glNamedBufferSubData(_id, 0, size, data);
  }

  const VertexBufferLayout &GLVertexBuffer::GetLayout() const
  {
    return _layout;
  }

  void GLVertexBuffer::SetLayout(const VertexBufferLayout &layout)
  {
    KRYS_ASSERT(layout.GetAttributeCount() <= MaxVertexAttributes,
                "Layout has too many vertex attributes. It has %d, but only %d are supported",
                layout.GetAttributeCount(), MaxVertexAttributes);
    _layout = layout;
  }

  GLUniformBuffer::GLUniformBuffer(uint32 size, uint32 binding)
  {
    glCreateBuffers(1, &_id);
    glNamedBufferData(_id, size, nullptr, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, binding, _id);
  }

  GLUniformBuffer::GLUniformBuffer(uint32 binding, UniformBufferLayout layout)
  {
    glCreateBuffers(1, &_id);

    SetLayout(layout);
    glNamedBufferData(_id, layout.GetSize(), nullptr, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, binding, _id);
  }

  GLUniformBuffer::~GLUniformBuffer()
  {
    glDeleteBuffers(1, &_id);
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
    glNamedBufferSubData(_id, info.Offset, info.Size, &paddedValue);
  }

  void GLUniformBuffer::SetData(const string &name, int value)
  {
    auto info = GetAttributeInfo(name);
    KRYS_ASSERT(info.Found, "Unable to find element in layout with name %s", name.c_str());
    glNamedBufferSubData(_id, info.Offset, info.Size, &value);
  }

  void GLUniformBuffer::SetData(const string &name, size_t value)
  {
    auto info = GetAttributeInfo(name);
    KRYS_ASSERT(info.Found, "Unable to find element in layout with name %s", name.c_str());
    glNamedBufferSubData(_id, info.Offset, info.Size, &value);
  }

  void GLUniformBuffer::SetData(const string &name, float value)
  {
    auto info = GetAttributeInfo(name);
    KRYS_ASSERT(info.Found, "Unable to find element in layout with name %s", name.c_str());
    glNamedBufferSubData(_id, info.Offset, info.Size, &value);
  }

  void GLUniformBuffer::SetData(const string &name, const Vec2 &value)
  {
    auto info = GetAttributeInfo(name);
    KRYS_ASSERT(info.Found, "Unable to find element in layout with name %s", name.c_str());
    glNamedBufferSubData(_id, info.Offset, info.Size, &value);
  }

  void GLUniformBuffer::SetData(const string &name, const Vec3 &value)
  {
    auto info = GetAttributeInfo(name);
    KRYS_ASSERT(info.Found, "Unable to find element in layout with name %s", name.c_str());
    Vec4 paddedValue = {value, 0.0f};
    glNamedBufferSubData(_id, info.Offset, info.Size, &paddedValue);
  }

  void GLUniformBuffer::SetData(const string &name, const Vec4 &value)
  {
    auto info = GetAttributeInfo(name);
    KRYS_ASSERT(info.Found, "Unable to find element in layout with name %s", name.c_str());
    glNamedBufferSubData(_id, info.Offset, info.Size, &value);
  }

  void GLUniformBuffer::SetData(const string &name, const Mat3 &value)
  {
    KRYS_ASSERT(false, "TODO: Implement me!", 0);
  }

  void GLUniformBuffer::SetData(const string &name, const Mat4 &value)
  {
    auto info = GetAttributeInfo(name);
    KRYS_ASSERT(info.Found, "Unable to find element in layout with name %s", name.c_str());
    glNamedBufferSubData(_id, info.Offset, info.Size, &value);
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

      for (const auto &element : _layout)
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

      for (const auto &element : _layout)
        if (element.Name == structName)
        {
          GLUniformBuffer::AttributeInfo attributeInfo = {element.AlignedOffset, 0};
          return GetAttributeInfo(remaining, element.Layout, attributeInfo);
        }
    }
    else
    {
      for (const auto &element : _layout)
        if (element.Name == name)
          return {element.AlignedOffset, element.LayoutSize, true};
    }

    return {};
  }

  GLUniformBuffer::AttributeInfo GLUniformBuffer::GetAttributeInfo(const string &name, UniformStructLayout layout,
                                                                   AttributeInfo info) const noexcept
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
          // HACK: This is a little bit hacky; When we calculate the total std140 size of the buffer
          // we cheat and multiply the size of the mat4 and mat3 types by count so the total size is correct
          // means  we have to divide again here to get the size of a single one.
          auto elementSize = element.LayoutSize / element.Count;
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
    return _layout;
  }

  void GLUniformBuffer::SetLayout(const UniformBufferLayout &layout)
  {
    KRYS_ASSERT(layout.GetElements().size(), "Uniform buffer has no layout!", 0);
    _layout = layout;
  }

  GLInstanceArrayBuffer::GLInstanceArrayBuffer(uint32 size)
  {
    glCreateBuffers(1, &_id);
    glNamedBufferData(_id, size, nullptr, GL_DYNAMIC_DRAW);
  }

  GLInstanceArrayBuffer::GLInstanceArrayBuffer(void *data, uint32 size)
  {
    glCreateBuffers(1, &_id);
    glNamedBufferData(_id, size, data, GL_DYNAMIC_DRAW);
  }

  GLInstanceArrayBuffer::~GLInstanceArrayBuffer()
  {
    glDeleteBuffers(1, &_id);
  }

  void GLInstanceArrayBuffer::Bind()
  {
    glBindBuffer(GL_ARRAY_BUFFER, _id);
  }

  void GLInstanceArrayBuffer::Unbind()
  {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  void GLInstanceArrayBuffer::SetData(const void *data, uint32 size)
  {
    glNamedBufferSubData(_id, 0, size, data);
  }

  const InstanceArrayBufferLayout &GLInstanceArrayBuffer::GetLayout() const
  {
    return _layout;
  }

  void GLInstanceArrayBuffer::SetLayout(const InstanceArrayBufferLayout &layout)
  {
    _layout = layout;
  }
}
