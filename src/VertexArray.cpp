#include "VertexArray.h"
#include <GL/glew.h>
#include <iostream> 
static GLenum GLTypeFromBufferElementType(AttributeType t) {
	switch (t) {
		case  AttributeType::FLOAT1: return GL_FLOAT; 
		case AttributeType::FLOAT2: return GL_FLOAT;
		case AttributeType::FLOAT3: return GL_FLOAT;
		case AttributeType::FLOAT4: return GL_FLOAT;
		case AttributeType::UINT1:  return GL_UNSIGNED_INT;
		case AttributeType::UINT2:  return GL_UNSIGNED_INT;
		case AttributeType::UINT3:  return GL_UNSIGNED_INT;
		case AttributeType::UINT4:  return GL_UNSIGNED_INT;
		case AttributeType::MAT3:   return GL_FLOAT;
		case AttributeType::MAT4:   return GL_FLOAT;
	}
}
VertexArray::VertexArray()
{
	IndexCount = 0; 
	glGenVertexArrays(1, &m_ArrayID); 
	glBindVertexArray(m_ArrayID); 
}
VertexArray::~VertexArray()
{
	for (int i = IndexCount; i >= 0; --i) glDisableVertexAttribArray(i); 
	UnBind(); 
}

VertexArray::VertexArray(const std::shared_ptr<VertexBuffer>& vbo)
{
	IndexCount = 0; 
	glGenVertexArrays(1, &m_ArrayID); 
	glBindVertexArray(m_ArrayID); 
	AddVertexBuffer(vbo); 
}

void VertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vbo)
{
	glBindVertexArray(m_ArrayID); 
	int vm = vbo->GetBufferLayout().GetStride();
	vbo->Bind(); 
	for (auto& v : vbo->GetBufferLayout()) {
		glEnableVertexAttribArray(IndexCount); 
	
		glVertexAttribPointer(IndexCount,v.GetCountByType(),GLTypeFromBufferElementType(v.Type), GL_FALSE, vm,(void*)v.Offset);
	//	std::cout << IndexCount << " : " << v.Offset << " COUNT : " << v.GetCountByType() <<  std::endl; 
		IndexCount++;

		}

		m_VertexBuffers.push_back(vbo); 
	}

void VertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& ibo) 
{
	glBindVertexArray(m_ArrayID); 
	ibo->Bind(); 
	m_IndexBuffer = ibo; 
}


void VertexArray::Bind() const
{
	glBindVertexArray(m_ArrayID); 
	m_IndexBuffer->Bind(); 
}

void VertexArray::UnBind() const
{
	glBindVertexArray(0); 
	for (auto& vbo : m_VertexBuffers) vbo->UnBind(); 
	m_IndexBuffer->UnBind(); 
}
