#pragma once
#include "Buffer.h"
#include <glm/glm.hpp>
#include <memory> 

class VertexArray {
private: 
	uint32_t m_ArrayID; 
	uint32_t IndexCount = 0; 
	std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers; 
	std::shared_ptr<IndexBuffer> m_IndexBuffer;

public: 
	VertexArray(); 
	VertexArray(const std::shared_ptr<VertexBuffer> & vbo); 
	~VertexArray(); 
	void AddVertexBuffer(const std::shared_ptr<VertexBuffer> & vbo)  ; 
	void SetIndexBuffer(const std::shared_ptr<IndexBuffer> & ibo)  ; 
	std::shared_ptr<IndexBuffer>& GetIndexBuffer() { return m_IndexBuffer;  }
	void Bind() const; 
	void UnBind() const; 
};
