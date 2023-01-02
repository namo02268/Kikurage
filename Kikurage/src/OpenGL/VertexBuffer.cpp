#include "OpenGL/VertexBuffer.h"

namespace Kikurage {
    VertexBuffer::VertexBuffer() {
        glGenBuffers(1, &this->m_id);
    }

    VertexBuffer::VertexBuffer(VertexBuffer&& vertexBuffer) noexcept {
        this->m_id = vertexBuffer.m_id;
        this->m_size = vertexBuffer.m_size;
        this->m_usage = vertexBuffer.m_usage;

        vertexBuffer.m_id = 0;
        vertexBuffer.m_size = 0;
        vertexBuffer.m_usage = GL_STATIC_DRAW;
    }

    VertexBuffer& VertexBuffer::operator=(VertexBuffer&& vertexBuffer) noexcept {
        this->m_id = vertexBuffer.m_id;
        this->m_size = vertexBuffer.m_size;
        this->m_usage = vertexBuffer.m_usage;

        vertexBuffer.m_id = 0;
        vertexBuffer.m_size = 0;
        vertexBuffer.m_usage = GL_STATIC_DRAW;

        return *this;
    }

    VertexBuffer::~VertexBuffer() {
        this->FreeBuffer();
    }

    void VertexBuffer::FreeBuffer() {
        if (this->m_id != 0)
        {
            glDeleteBuffers(1, &this->m_id);
            this->m_id = 0;
        }
    }

    void VertexBuffer::Bind() const {
        glBindBuffer(GL_ARRAY_BUFFER, this->m_id);
    }

    void VertexBuffer::Unbind() const {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void VertexBuffer::SetData(size_t size, const void* data, unsigned int usage) {
        this->m_size = size;
        this->m_usage = usage;
        this->Bind();
        glBufferData(GL_ARRAY_BUFFER, size, data, m_usage);
    }
}
