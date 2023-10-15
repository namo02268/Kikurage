#pragma once

#include <glad/glad.h>
#include "OpenGL/VertexBuffer.h"
#include "OpenGL/IndexBuffer.h"

namespace Kikurage {
	struct VertexAttribute {
		unsigned int size;
		unsigned int type;
		unsigned int stride;
		size_t offset;
	};

	class VertexArray {
	private:
		unsigned int m_id = 0;
		unsigned int m_index = 0;

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

		// TODO: ƒ^ƒCƒv‚²‚Æ‚Étemplate“ÁŽê‰»
		void BindAttribute(VertexBuffer& VBO, VertexAttribute attribute);
		void BindIBO(IndexBuffer& IBO);
	};
}
