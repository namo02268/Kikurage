#include "OpenGL/Texture2D.h"

namespace Kikurage {
	Texture2D::Texture2D() {
		glGenTextures(1, &this->m_id);
	}

	Texture2D::Texture2D(Texture2D&& texture) noexcept {
		this->m_id = texture.m_id;
		this->m_width = texture.m_width;
		this->m_height = texture.m_height;
		this->m_format = texture.m_format;
		this->m_wrapType = texture.m_wrapType;
		this->m_filter = texture.m_filter;

		texture.m_id = 0;
		texture.m_width = 0;
		texture.m_height = 0;
	}

	Texture2D& Texture2D::operator=(Texture2D&& texture) noexcept {
		this->m_id = texture.m_id;
		this->m_width = texture.m_width;
		this->m_height = texture.m_height;

		this->m_format = texture.m_format;
		this->m_wrapType = texture.m_wrapType;
		this->m_filter = texture.m_filter;

		texture.m_id = 0;
		texture.m_width = 0;
		texture.m_height = 0;

		return *this;
	}

	Texture2D::~Texture2D() {
		this->FreeTexture();
	}

	void Texture2D::Bind() const {
		glBindTexture(GL_TEXTURE_2D, this->m_id);
	}

	void Texture2D::Unbind() const {
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture2D::Generate(unsigned char* data, unsigned int width, unsigned int height, unsigned int channels, unsigned int format) {
		this->m_width = width;
		this->m_height = height;
		this->m_format = format;

		GLenum dataChannels = GL_RGB;
		switch (channels)
		{
		case 1:
			dataChannels = GL_RED;
			break;
		case 2:
			dataChannels = GL_RG;
			break;
		case 3:
			dataChannels = GL_RGB;
			break;
		case 4:
			dataChannels = GL_RGBA;
			break;
		default:
			break;
		}

		this->Bind();
		glTexImage2D(GL_TEXTURE_2D, 0, this->m_format, this->m_width, this->m_height, 0, dataChannels, GL_UNSIGNED_BYTE, data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->m_wrapType);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->m_wrapType);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->m_filter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->m_filter);
		this->Unbind();
	}

	void Texture2D::FreeTexture() {
		if (this->m_id != 0) {
			glDeleteTextures(1, &m_id);
			this->m_id = 0;
		}
	}

	void Texture2D::SetWrapType(unsigned int wrapType) {
		this->m_wrapType = wrapType;

		this->Bind();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->m_wrapType);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->m_wrapType);
		this->Unbind();
	}

	void Texture2D::SetFilterType(unsigned int filterType) {
		this->m_filter = filterType;

		this->Bind();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->m_filter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->m_filter);
		glGenerateMipmap(GL_TEXTURE_2D);
		this->Unbind();
	}
}
