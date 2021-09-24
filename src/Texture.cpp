#include "Texture.h"
#include <iostream>
Texture::~Texture()
{
	glDeleteTextures(1, &m_TextureID); 
	delete[] m_Img; 
}

Texture::Texture(const std::string& File) 
{

	stbi_set_flip_vertically_on_load(1);
	m_Img = stbi_load(File.c_str(), &texture.width, &texture.height, &texture.channels, 4);
	
	if (!m_Img) {
		std::cout << " Failed to load \n"; 
	}
	glGenTextures(1, &m_TextureID);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, texture.width, texture.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_Img);
	glBindTexture(GL_TEXTURE_2D, 0);

}

void Texture::Bind(uint32_t slot)
{
	glBindTextureUnit(slot, m_TextureID); 
}

void Texture::UnBind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
