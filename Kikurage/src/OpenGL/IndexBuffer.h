#pragma once

#include <glad/glad.h>

namespace Kikurage {
	class IndexBuffer {
	private:
		unsigned int m_id = 0;
		size_t m_size = 0;
		unsigned int m_usage = GL_STATIC_DRAW;

		void FreeBuffer();

	public:
		IndexBuffer();
		IndexBuffer(const IndexBuffer&) = delete;
		IndexBuffer(IndexBuffer&& other) noexcept;
		IndexBuffer& operator=(const IndexBuffer&) = delete;
		IndexBuffer& operator=(IndexBuffer&& other) noexcept;
		~IndexBuffer();

		void Bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_id); }
		void Unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }
		const unsigned int GetHandle() const { return this->m_id; }
		void SetData(size_t size, const void* data, unsigned int usage);
	};
}
