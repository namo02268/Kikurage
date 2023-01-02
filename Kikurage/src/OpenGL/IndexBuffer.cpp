#include "OpenGL/IndexBuffer.h"

namespace Kikurage {
    IndexBuffer::IndexBuffer() {
        glGenBuffers(1, &this->m_id);
    }

    IndexBuffer::IndexBuffer(IndexBuffer&& indexBuffer) noexcept {
        this->m_id = indexBuffer.m_id;
        this->m_size = indexBuffer.m_size;
        this->m_usage = indexBuffer.m_usage;

        indexBuffer.m_id = 0;
        indexBuffer.m_size = 0;
        indexBuffer.m_usage = GL_STATIC_DRAW;
    }

    IndexBuffer& IndexBuffer::operator=(IndexBuffer&& indexBuffer) noexcept {
        this->m_id = indexBuffer.m_id;
        this->m_size = indexBuffer.m_size;
        this->m_usage = indexBuffer.m_usage;

        indexBuffer.m_id = 0;
        indexBuffer.m_size = 0;
        indexBuffer.m_usage = GL_STATIC_DRAW;

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

    void IndexBuffer::Bind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_id);
    }

    void IndexBuffer::Unbind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void IndexBuffer::SetData(size_t size, const void* data, unsigned int usage) {
        this->m_size = size;
        this->m_usage = usage;
        this->Bind();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, m_usage);
    }
}
