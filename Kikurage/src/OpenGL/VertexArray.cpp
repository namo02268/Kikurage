#include "OpenGL/VertexArray.h"

namespace Kikurage {
	VertexArray::VertexArray() {
		glGenVertexArrays(1, &this->m_id);
	}

	VertexArray::VertexArray(VertexArray&& other) noexcept {
		this->m_id = other.m_id;
		other.m_id = 0;
	}

	VertexArray& VertexArray::operator=(VertexArray&& other) noexcept {
		this->m_id = other.m_id;
		other.m_id = 0;
		return *this;
	}

	VertexArray::~VertexArray() {
		this->FreeBuffer();
	}

	void VertexArray::FreeBuffer() {
		glDeleteVertexArrays(1, &this->m_id);
	}
}
