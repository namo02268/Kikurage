#pragma once

#include <glad/glad.h>

namespace Kikurage {
	class VertexBuffer {
	private:
		unsigned int m_id = 0;
		size_t m_size = 0;
		unsigned int m_usage = GL_STATIC_DRAW;

		void FreeBuffer();

	public:
		VertexBuffer();
		VertexBuffer(const VertexBuffer&) = delete;
		VertexBuffer(VertexBuffer&& vertexBuffer) noexcept;
		VertexBuffer& operator=(const VertexBuffer&) = delete;
		VertexBuffer& operator=(VertexBuffer&& vertexBuffer) noexcept;
		~VertexBuffer();

		void Bind() const;
		void Unbind() const;
		unsigned int GetHandle() const { return this->m_id; }
		void SetData(size_t size, const void* data, unsigned int usage);
	};
}
