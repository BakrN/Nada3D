#pragma once
#include <string>
#include "stb_image.h"
#include <GL/glew.h>
class Texture
{
	struct ImageSpec {
		int width, height, channels;
	};
private: 
	ImageSpec texture; 
	unsigned char* m_Img; 
	uint32_t m_TextureID; 
public: 
	~Texture(); 
	Texture(const std::string& File); 
	void Bind(uint32_t slot);
	void UnBind(); 
	
};

