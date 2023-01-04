#pragma once

#include <glad/glad.h>
#include "OpenGL/VertexBuffer.h"

namespace Kikurage {
	class VertexArray {
	private:
		unsigned int m_id = 0;

		void FreeBuffer();

	public:
		VertexArray();
		VertexArray(const VertexArray&) = delete;
		VertexArray(VertexArray&& other) noexcept;
		VertexArray& operator=(const VertexArray&) = delete;
		VertexArray& operator=(VertexArray&& other) noexcept;
		~VertexArray();

		void Bind() const { glBindVertexArray(this->m_id); }
		void Unbind() const { glBindVertexArray(0); }
		const unsigned int GetHandle() const { return this->m_id; }

		void BindAttribute(
			unsigned int attribute,
			unsigned int size,
			unsigned int type,
			unsigned int stride,
			size_t offset
		) {
			glEnableVertexAttribArray(attribute);
			glVertexAttribPointer(attribute, size, GL_FLOAT, GL_FALSE, stride, (void*)offset);
			glEnableVertexAttribArray(0);
		}
	};
}
