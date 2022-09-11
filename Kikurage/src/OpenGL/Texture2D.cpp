#include "OpenGL/Texture2D.h"

Texture2D::Texture2D() {
	glGenTextures(1, &this->m_id);
}

Texture2D::Texture2D(Texture2D&& texture) noexcept {
	this->m_id = texture.m_id;
	this->m_width = texture.m_width;
	this->m_height = texture.m_height;
	this->m_format = texture.m_format;

	this->Wrap_S = texture.Wrap_S;
	this->Wrap_T = texture.Wrap_T;
	this->Filter_Min = texture.Filter_Min;
	this->Filter_Max = texture.Filter_Max;
}

Texture2D& Texture2D::operator=(Texture2D&& texture) noexcept {
	this->m_id = texture.m_id;
	this->m_width = texture.m_width;
	this->m_height = texture.m_height;
	this->m_format = texture.m_format;

	this->Wrap_S = texture.Wrap_S;
	this->Wrap_T = texture.Wrap_T;
	this->Filter_Min = texture.Filter_Min;
	this->Filter_Max = texture.Filter_Max;

	return *this;
}

Texture2D::~Texture2D() {
	this->FreeTexture();
}

void Texture2D::Generate(unsigned int width, unsigned int height, unsigned int channels, unsigned int format, unsigned char* data) {
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

	// create Texture
	glBindTexture(GL_TEXTURE_2D, this->m_id);
	glTexImage2D(GL_TEXTURE_2D, 0, this->m_format, this->m_width, this->m_height, 0, dataChannels, GL_UNSIGNED_BYTE, data);

	// set Texture wrap and filter modes
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->Wrap_S);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->Wrap_T);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->Filter_Min);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->Filter_Max);

	// unbind texture
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::Bind() const {
	glBindTexture(GL_TEXTURE_2D, this->m_id);
}

void Texture2D::Unbind() const {
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::FreeTexture() {
	if (this->m_id != 0) {
		glDeleteTextures(1, &m_id);
		this->m_id = 0;
	}
}