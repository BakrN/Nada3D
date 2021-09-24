#pragma once
#include "Scene.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "Buffer.h"
struct RenderStats {
	uint32_t m_DrawCount = 0;
	uint32_t m_DrawCalls = 0;
	void ResetStats() {
		m_DrawCount = 0;
		m_DrawCalls = 0; 
	}
};
static class Renderer2D{
private: 
	Shader* m_ObjShader; 
	std::vector<std::unique_ptr<VertexArray>> m_VertexArrays; 
	std::vector<uint32_t> m_Count; 
	// max quad count 

	//vaoList; 
public: 
	static Shader* GetShader(); 
	static void Init(); // All gl commands; 
	static void Flush(); 
	static void Finish(); // delete memory , gl commands; 
	static void AttatchScene(Scene* scene); 
	static void DrawScene(); 
	static void DrawQuad(PrimitiveObject::Quad* quad);
	static void DrawTexturedQuad(PrimitiveObject::Quad* quad , Texture& texture);
	static void DrawTriangle(PrimitiveObject::Triangle& triangle); 
	static void DrawTexturedTriangle(PrimitiveObject::Triangle& triangle, Texture& texture); 
	static void NewBatch(); 
	static void EndBatch(); 

	static RenderStats GetStats(); 
};
