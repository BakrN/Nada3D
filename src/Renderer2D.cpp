#include "Renderer2D.h"
#include <unordered_map>
#include <glm/gtx/string_cast.hpp>
#define MAX_TRIANGLE_COUNT 6000
#define TEXTURE_SLOTS 32
struct RenderCall {
	Scene* m_Scene;
	uint16_t m_MaxTriangleCount = MAX_TRIANGLE_COUNT;
	uint8_t m_MaxTextureSlots = TEXTURE_SLOTS;
	uint8_t m_TextureSlotIndex = 1;
	std::shared_ptr<IndexBuffer>  m_IndexBuffer;
	std::shared_ptr<VertexBuffer> m_VertexBuffer;
	std::unique_ptr<VertexArray>  m_VertexArray;

	VertexAttributes* m_Vertices;
	VertexAttributes* m_VerticesPtr; // Lighting system will probably need normals; 
	uint32_t* m_IndexData;
	uint32_t* m_IndexDataPtr;

	int index_count = 0;

	uint32_t m_WhiteTextureID;
	Shader* m_Shader;

	uint32_t m_VertexOffset = 0; 

};

static RenderStats s_RenderStats; 
static RenderCall s_RenderCall;
Shader* Renderer2D::GetShader()
{
	return s_RenderCall.m_Shader; 
}
void Renderer2D::Init()
{
	s_RenderCall.m_Shader = new Shader("ObjectShader.shader");
	s_RenderCall.m_Shader->Bind();
	s_RenderCall.m_Vertices = new VertexAttributes[3*s_RenderCall.m_MaxTriangleCount]; 
	s_RenderCall.m_VerticesPtr = s_RenderCall.m_Vertices; 
	int s = sizeof(VertexAttributes); 
	s_RenderCall.m_VertexBuffer = std::make_shared<VertexBuffer>(3*sizeof(VertexAttributes) * s_RenderCall.m_MaxTriangleCount); 
	BufferLayout layout({ {"v_Position", AttributeType::FLOAT3},{"v_Normal", AttributeType::FLOAT3},  {"v_Color", AttributeType::FLOAT4} ,{"v_TexUV", AttributeType::FLOAT2}, {"v_TexSlot", AttributeType::FLOAT1} });
	s_RenderCall.m_VertexBuffer->SetLayout(layout); 
	s_RenderCall.m_IndexData = new uint32_t[(3 * MAX_TRIANGLE_COUNT)];
	s_RenderCall.m_IndexDataPtr= s_RenderCall.m_IndexData; 
	s_RenderCall.m_IndexBuffer = std::make_shared<IndexBuffer>(3*sizeof(uint32_t)*s_RenderCall.m_MaxTriangleCount);

	s_RenderCall.m_VertexArray = std::make_unique<VertexArray>(s_RenderCall.m_VertexBuffer); 
	s_RenderCall.m_VertexArray->SetIndexBuffer(s_RenderCall.m_IndexBuffer); 
	s_RenderCall.m_VertexArray->Bind(); 
	uint32_t color = 0xffffffff; 
	glGenTextures(1, &s_RenderCall.m_WhiteTextureID); 
	glBindTexture(GL_TEXTURE_2D, s_RenderCall.m_WhiteTextureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE,&color );
	glBindTextureUnit(0,s_RenderCall.m_WhiteTextureID);
	unsigned int* Slots = new unsigned int[32]{};
	for (int i = 0; i < 32; ++i)
		Slots[i] = i; 
	s_RenderCall.m_Shader->UniformArrayINT("TextureSlot", 32,(int32_t*) Slots);
	delete[] Slots; 
}; 

void Renderer2D::AttatchScene(Scene* scene)
{
	s_RenderCall.m_Scene = scene; 
}

void Renderer2D::DrawScene()
{
}


void Renderer2D::Flush()
{
	s_RenderCall.m_VerticesPtr = s_RenderCall.m_Vertices; 
	s_RenderCall.m_IndexDataPtr = s_RenderCall.m_IndexData; 

	s_RenderCall.m_VertexArray->Bind(); 
	s_RenderCall.m_Shader->Bind();
	glDrawElements(GL_TRIANGLES, s_RenderCall.index_count, GL_UNSIGNED_INT, nullptr); 
	s_RenderCall.index_count = 0; 
	s_RenderCall.m_VertexOffset = 0;
	s_RenderCall.m_TextureSlotIndex = 1; 
	s_RenderStats.m_DrawCalls++;
}

void Renderer2D::DrawQuad(PrimitiveObject::Quad* quad)
{
	
	if (s_RenderCall.index_count + 6 >= 3 * s_RenderCall.m_MaxTriangleCount) {
		EndBatch(); 
		Flush(); 
		int temp = s_RenderStats.m_DrawCalls; 
		int count = s_RenderStats.m_DrawCalls;
		NewBatch();
		s_RenderStats.m_DrawCalls = temp; 
		s_RenderStats.m_DrawCount = count; 
	}
	quad->SetTextureSlot(0.0f); 
	auto& vertices = quad->get_vertices(); 
	for (int i = 0; i < 4;  i++) {
		*s_RenderCall.m_VerticesPtr = vertices[i];

		s_RenderCall.m_VerticesPtr++; 
	
	}
		*s_RenderCall.m_IndexDataPtr = 1 + s_RenderCall.m_VertexOffset;
		s_RenderCall.m_IndexDataPtr++;
		*s_RenderCall.m_IndexDataPtr = 2 + s_RenderCall.m_VertexOffset;
		s_RenderCall.m_IndexDataPtr++;
		*s_RenderCall.m_IndexDataPtr = 3 + s_RenderCall.m_VertexOffset;
		s_RenderCall.m_IndexDataPtr++;
		*s_RenderCall.m_IndexDataPtr = 1 + s_RenderCall.m_VertexOffset;
		s_RenderCall.m_IndexDataPtr++;
		*s_RenderCall.m_IndexDataPtr = 0 + s_RenderCall.m_VertexOffset;
		s_RenderCall.m_IndexDataPtr++;
		*s_RenderCall.m_IndexDataPtr = 2 + s_RenderCall.m_VertexOffset;
		s_RenderCall.m_IndexDataPtr++;
		s_RenderCall.m_VertexOffset += 4; 
		s_RenderCall.index_count += 6; 


		s_RenderStats.m_DrawCount++; 

}


void Renderer2D::DrawTexturedQuad(PrimitiveObject::Quad* quad, Texture& texture)
{
	if (s_RenderCall.index_count + 6 >= 3 * s_RenderCall.m_MaxTriangleCount || s_RenderCall.m_TextureSlotIndex > 31) {
		EndBatch();
		Flush();
		int temp = s_RenderStats.m_DrawCalls;
		int count = s_RenderStats.m_DrawCount;
		NewBatch();
		s_RenderStats.m_DrawCalls = temp;
		s_RenderStats.m_DrawCount = count;
	}
	texture.Bind(s_RenderCall.m_TextureSlotIndex); 
	quad->SetTextureSlot(s_RenderCall.m_TextureSlotIndex); 
	quad->SetColor(glm::vec4{ 1.0f,1.0f,1.0f,1.0f }); 
	auto& vertices = quad->get_vertices();
	for (int i = 0; i < 4; i++) {
		*s_RenderCall.m_VerticesPtr = vertices[i];

		s_RenderCall.m_VerticesPtr++;

	}
	*s_RenderCall.m_IndexDataPtr = 1 + s_RenderCall.m_VertexOffset;
	s_RenderCall.m_IndexDataPtr++;
	*s_RenderCall.m_IndexDataPtr = 2 + s_RenderCall.m_VertexOffset;
	s_RenderCall.m_IndexDataPtr++;
	*s_RenderCall.m_IndexDataPtr = 3 + s_RenderCall.m_VertexOffset;
	s_RenderCall.m_IndexDataPtr++;
	*s_RenderCall.m_IndexDataPtr = 1 + s_RenderCall.m_VertexOffset;
	s_RenderCall.m_IndexDataPtr++;
	*s_RenderCall.m_IndexDataPtr = 0 + s_RenderCall.m_VertexOffset;
	s_RenderCall.m_IndexDataPtr++;
	*s_RenderCall.m_IndexDataPtr = 2 + s_RenderCall.m_VertexOffset;
	s_RenderCall.m_IndexDataPtr++;
	s_RenderCall.m_VertexOffset += 4;
	s_RenderCall.index_count += 6;
	s_RenderCall.m_TextureSlotIndex++; 	


	s_RenderStats.m_DrawCount++;
}

void Renderer2D::DrawTriangle(PrimitiveObject::Triangle& triangle)
{

	
}

void Renderer2D::DrawTexturedTriangle(PrimitiveObject::Triangle& triangle, Texture& texture)
{

}

void Renderer2D::NewBatch()
{	
	s_RenderCall.m_VerticesPtr = s_RenderCall.m_Vertices; 
	s_RenderCall.m_IndexDataPtr = s_RenderCall.m_IndexData; 
	s_RenderStats.m_DrawCalls = 0;
	s_RenderStats.m_DrawCount = 0;
}

void Renderer2D::EndBatch()
{
		// glBindVao
	GLsizeiptr size_v = (uint8_t*)s_RenderCall.m_VerticesPtr - (uint8_t*)s_RenderCall.m_Vertices; // number of elements between both but in uint8_8 chunks
	GLsizeiptr size_i = (uint8_t*)s_RenderCall.m_IndexDataPtr - (uint8_t*)s_RenderCall.m_IndexData; 

	s_RenderCall.m_VertexBuffer->UpdateData(s_RenderCall.m_Vertices, size_v); 
	s_RenderCall.m_IndexBuffer->UpdateData(s_RenderCall.m_IndexData, size_i); 
}

RenderStats Renderer2D::GetStats()
{
	return s_RenderStats;
}





void Renderer2D::Finish()
{
	s_RenderCall.m_IndexBuffer.reset(); 
	s_RenderCall.m_VertexBuffer.reset(); 
	//delete s_RenderCall.m_Scene; 
	delete s_RenderCall.m_Shader; 
	delete[] s_RenderCall.m_Vertices;
	delete[] s_RenderCall.m_IndexData; 
}
