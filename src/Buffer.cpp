#include "Buffer.h"
#include <GL/glew.h>

IndexBuffer::IndexBuffer(const void* data, unsigned int size) {
	glGenBuffers(1, &m_BufferId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
}

IndexBuffer::IndexBuffer(unsigned int size)
{
	glGenBuffers(1, &m_BufferId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
	UnBind(); 
	glDeleteBuffers(1, &m_BufferId);
}

void IndexBuffer::UpdateData(const void* data, unsigned int size)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferId);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, size, data);
}

void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferId);
}

void IndexBuffer::UnBind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	// size is data size 
	glGenBuffers(1, &m_BufferId);
	glBindBuffer(GL_ARRAY_BUFFER, m_BufferId);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
}

VertexBuffer::VertexBuffer(unsigned int size)
{
	glGenBuffers(1, &m_BufferId);
	glBindBuffer(GL_ARRAY_BUFFER, m_BufferId);
	glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
}

void VertexBuffer::UpdateData(const void* data, unsigned int size)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_BufferId);
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, data); 
}

VertexBuffer::~VertexBuffer()
{
	UnBind(); 
	glDeleteBuffers(1, &m_BufferId);
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_BufferId);
}

void VertexBuffer::UnBind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
