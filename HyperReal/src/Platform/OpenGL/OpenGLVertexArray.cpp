#include "hrpch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace HyperR {

    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
    {
        switch (type)
        {
            case HyperR::ShaderDataType::Float:    return GL_FLOAT;
            case HyperR::ShaderDataType::Float2:   return GL_FLOAT;
            case HyperR::ShaderDataType::Float3:   return GL_FLOAT;
            case HyperR::ShaderDataType::Float4:   return GL_FLOAT;
            case HyperR::ShaderDataType::Mat3:     return GL_FLOAT;
            case HyperR::ShaderDataType::Mat4:     return GL_FLOAT;
            case HyperR::ShaderDataType::Int:      return GL_INT;
            case HyperR::ShaderDataType::Int2:     return GL_INT;
            case HyperR::ShaderDataType::Int3:     return GL_INT;
            case HyperR::ShaderDataType::Int4:     return GL_INT;
            case HyperR::ShaderDataType::Bool:     return GL_BOOL;
        }

        HR_CORE_ASSERT(false, "Unknown ShaderDataType!");
        return 0;
    }

    OpenGLVertexArray::OpenGLVertexArray()
    {
        HR_PROFILE_FUNCTION();
        glCreateVertexArrays(1, &m_RendererID);
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        HR_PROFILE_FUNCTION();

        glDeleteVertexArrays(1, &m_RendererID);
    }

    void OpenGLVertexArray::Bind() const
    {
        HR_PROFILE_FUNCTION();

        glBindVertexArray(m_RendererID);
    }

    void OpenGLVertexArray::Unbind() const
    {
        HR_PROFILE_FUNCTION();

        glBindVertexArray(0);
    }

    void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
    {
        HR_PROFILE_FUNCTION();

        HR_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");
        glBindVertexArray(m_RendererID);
        vertexBuffer->Bind();
        uint32_t index = 0;
        const auto& layout = vertexBuffer->GetLayout();
        for (const auto& element : layout)
        {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index,
                element.GetComponentCount(),
                ShaderDataTypeToOpenGLBaseType(element.Type),
                element.Normalized ? GL_TRUE : GL_FALSE,
                layout.GetStride(),
                (const void*)element.Offset);
            index++;
        }
        m_VertexBuffers.push_back(vertexBuffer);
    }

    void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
    {
        HR_PROFILE_FUNCTION();

        glBindVertexArray(m_RendererID);
        indexBuffer->Bind();
        m_IndexBuffer = indexBuffer;
    }
}