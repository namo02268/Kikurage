#include "OpenGL/VertexArray.h"

namespace Kikurage {
	VertexArray::VertexArray() {
		glGenVertexArrays(1, &this->m_id);
	}

	VertexArray::VertexArray(VertexArray&& other) noexcept {
		this->m_id = other.m_id;
		other.m_id = 0;

		this->m_index = other.m_index;
		other.m_index = 0;
	}

	VertexArray& VertexArray::operator=(VertexArray&& other) noexcept {
		this->m_id = other.m_id;
		other.m_id = 0;

		this->m_index = other.m_index;
		other.m_index = 0;

		return *this;
	}

	VertexArray::~VertexArray() {
		this->FreeBuffer();
	}

	void VertexArray::FreeBuffer() {
		if (this->m_id != 0) {
			glDeleteVertexArrays(1, &this->m_id);
			this->m_id = 0;
		}
	}

	void VertexArray::BindAttribute(VertexBuffer& VBO, VertexAttribute attribute) {
		this->Bind();
		VBO.Bind();

		glEnableVertexAttribArray(this->m_index);
		glVertexAttribPointer(this->m_index, attribute.size, GL_FLOAT, attribute.type, attribute.stride, (void*)attribute.offset);
		glEnableVertexAttribArray(0);

		this->m_index++;
		this->Unbind();
	}

	void VertexArray::BindIBO(IndexBuffer& IBO) {
		this->Bind();
		IBO.Bind();
		this->Unbind();
	}
}
