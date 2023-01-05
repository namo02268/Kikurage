#include "OpenGL/IndexBuffer.h"

namespace Kikurage {
    IndexBuffer::IndexBuffer() {
        glGenBuffers(1, &this->m_id);
    }

    IndexBuffer::IndexBuffer(IndexBuffer&& other) noexcept {
        this->m_id = other.m_id;
        this->m_size = other.m_size;
        this->m_usage = other.m_usage;

        other.m_id = 0;
        other.m_size = 0;
        other.m_usage = GL_STATIC_DRAW;
    }

    IndexBuffer& IndexBuffer::operator=(IndexBuffer&& other) noexcept {
        this->m_id = other.m_id;
        this->m_size = other.m_size;
        this->m_usage = other.m_usage;

        other.m_id = 0;
        other.m_size = 0;
        other.m_usage = GL_STATIC_DRAW;

        return *this;
    }

    IndexBuffer::~IndexBuffer() {
        this->FreeBuffer();
    }

    void IndexBuffer::FreeBuffer() {
        if (this->m_id != 0)
        {
            glDeleteBuffers(1, &this->m_id);
            this->m_id = 0;
        }
    }

    void IndexBuffer::SetData(size_t size, const void* data, unsigned int usage) {
        this->m_size = size;
        this->m_usage = usage;
        this->Bind();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, m_usage);
    }
}
