#include "OpenGL/VertexBuffer.h"

namespace Kikurage {
    VertexBuffer::VertexBuffer() {
        glGenBuffers(1, &this->m_id);
    }

    VertexBuffer::VertexBuffer(VertexBuffer&& other) noexcept {
        this->m_id = other.m_id;
        this->m_size = other.m_size;
        this->m_usage = other.m_usage;

        other.m_id = 0;
        other.m_size = 0;
        other.m_usage = GL_STATIC_DRAW;
    }

    VertexBuffer& VertexBuffer::operator=(VertexBuffer&& other) noexcept {
        this->m_id = other.m_id;
        this->m_size = other.m_size;
        this->m_usage = other.m_usage;

        other.m_id = 0;
        other.m_size = 0;
        other.m_usage = GL_STATIC_DRAW;

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

    void VertexBuffer::SetData(size_t size, const void* data, unsigned int usage) {
        this->m_size = size;
        this->m_usage = usage;
        this->Bind();
        glBufferData(GL_ARRAY_BUFFER, size, data, m_usage);
    }
}
