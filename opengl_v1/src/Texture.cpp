#include "../headers/Texture.h"
#include "../headers/Renderer.h"

Texture::Texture(const string& filepath)
	:file_location(filepath),m_localBuffer(nullptr), m_height(0), m_width(0), m_BPP(0)
{
	GLCall(glGenTextures(1, &texture_id));
	GLCall(glBindTexture(GL_TEXTURE_2D, texture_id));
}