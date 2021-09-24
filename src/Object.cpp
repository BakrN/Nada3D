#include "Object.h"
#include<glm/gtx/quaternion.hpp>
#include <algorithm>

Object::~Object()
{
}

void Object::Translate(const glm::vec3& displacement)
{
	ModelMatrix[3] = glm::vec4(displacement,0); 
}

void Object::Rotate(const glm::quat& quaternion)
{
	ModelMatrix = glm::toMat4(quaternion)  * ModelMatrix; 
}

void Object::ResizeX(float scale)
{
	for (int i = 0; i < Vertices.size(); i++)
		Vertices[i].VertexPosition.x *= scale; 
}

void Object::ResizeY(float scale)
{

	for (int i = 0; i < Vertices.size(); i++)
		Vertices[i].VertexPosition.y *= scale; 
}

void Object::ResizeZ(float scale){
	for (int i = 0; i < Vertices.size(); i++)
		Vertices[i].VertexPosition.z *= scale; 
}

void Object::Rotate(const glm::mat3& rot3x3)
{
	ModelMatrix = ModelMatrix * glm::mat4(rot3x3); 
	//Do rotations for normal asweel 
	 
}

void Object::SetTextureSlot(float texslot)
{
	for (int i = 0; i < Vertices.size(); i++) {
		Vertices[i].TextureSlot = texslot; 
	}
}

void Object::SetColor(glm::vec4 color)
{
	for (int i = 0; i < Vertices.size(); i++) {
		Vertices[i].Color = color;
	}
}
glm::vec3 Object::CalculateNormal(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3)
{
	auto n1 = p3 - p1;
	auto n2 = p2 - p1;
	return glm::normalize(glm::cross(n1, n2));
}


	// Construct Vertices and Faces; 

	// vertices; 
/*
	for (int i = 0; i < 8; i++) {
		this->Vertices.push_back({ glm::vec3(CubeVertices[3 * i], CubeVertices[3 * i + 1], CubeVertices[3 * i + 2]) * m_CubeSpecs.size,glm::vec4{r,1-r,r*r, 1.0f}, glm::vec2{0.0f}});
	}*/

		/*this->Vertices.push_back({ glm::vec3(CubeVertices[3 * 0], CubeVertices[3 * 0 + 1], CubeVertices[3 * 0 + 2]) * m_CubeSpecs.size,glm::vec4{1.0f,0.0f,0.0f, 1.0f}, glm::vec2{0.0f}});
		this->Vertices.push_back({ glm::vec3(CubeVertices[3 * 1], CubeVertices[3 * 1 + 1], CubeVertices[3 * 1 + 2]) * m_CubeSpecs.size,glm::vec4{1.0f,0.0f,0.0f, 1.0f}, glm::vec2{0.0f}});
		this->Vertices.push_back({ glm::vec3(CubeVertices[3 * 2], CubeVertices[3 * 2 + 1], CubeVertices[3 * 2 + 2]) * m_CubeSpecs.size,glm::vec4{1.0f,0.0f,0.0f, 1.0f}, glm::vec2{0.0f}});
		this->Vertices.push_back({ glm::vec3(CubeVertices[3 * 3], CubeVertices[3 * 3 + 1], CubeVertices[3 * 3 + 2]) * m_CubeSpecs.size,glm::vec4{1.0f,0.0f,0.0f, 1.0f}, glm::vec2{0.0f}});
		this->Vertices.push_back({ glm::vec3(CubeVertices[3 * 4], CubeVertices[3 * 4 + 1], CubeVertices[3 * 4 + 2]) * m_CubeSpecs.size,glm::vec4{0.0f,0.0f,1.0f, 1.0f}, glm::vec2{0.0f}});
		this->Vertices.push_back({ glm::vec3(CubeVertices[3 * 5], CubeVertices[3 * 5 + 1], CubeVertices[3 * 5 + 2]) * m_CubeSpecs.size,glm::vec4{0.0f,0.0f,1.0f, 1.0f}, glm::vec2{0.0f}});
		this->Vertices.push_back({ glm::vec3(CubeVertices[3 * 6], CubeVertices[3 * 6 + 1], CubeVertices[3 * 6 + 2]) * m_CubeSpecs.size,glm::vec4{0.0f,0.0f,1.0f, 1.0f}, glm::vec2{0.0f}});
		this->Vertices.push_back({ glm::vec3(CubeVertices[3 * 7], CubeVertices[3 * 7 + 1], CubeVertices[3 * 7 + 2]) * m_CubeSpecs.size,glm::vec4{0.0f,0.0f,1.0f, 1.0f}, glm::vec2{0.0f}});*/

		//faces triangle
		//front
	/*this->Indices.push_back(0); this->Indices.push_back(1); this->Indices.push_back(2); 
	this->Indices.push_back(2); this->Indices.push_back(3); this->Indices.push_back(0); 
	// right
	this->Indices.push_back(1); this->Indices.push_back(5); this->Indices.push_back(6); 
	this->Indices.push_back(6); this->Indices.push_back(2); this->Indices.push_back(1); 
	// back
	this->Indices.push_back(7); this->Indices.push_back(6); this->Indices.push_back(5);
	this->Indices.push_back(5); this->Indices.push_back(4); this->Indices.push_back(7); 
	// left
	this->Indices.push_back(4); this->Indices.push_back(0);  this->Indices.push_back(3); 
	this->Indices.push_back(3); this->Indices.push_back(7);  this->Indices.push_back(4); 
	// bottom
	this->Indices.push_back(4); this->Indices.push_back(5); this->Indices.push_back(1); 
	this->Indices.push_back(1);  this->Indices.push_back(0); this->Indices.push_back(4); 
	// top
	this->Indices.push_back(3); this->Indices.push_back(2); this->Indices.push_back(6); 
	this->Indices.push_back(6); this->Indices.push_back(7); this->Indices.push_back(3); */

PrimitiveObject::Cube::Cube(CubeSpecifications spec )
{
	m_CubeSpecs = spec;
/*	float CubeVertices[] = {
-0.5f + m_CubeSpecs.position.x, -0.5f + m_CubeSpecs.position.y,  0.5f + m_CubeSpecs.position.z,
 0.5f + m_CubeSpecs.position.x, -0.5f + m_CubeSpecs.position.y,  0.5f + m_CubeSpecs.position.z,
 0.5f + m_CubeSpecs.position.x, 0.5f + m_CubeSpecs.position.y,  0.5f + m_CubeSpecs.position.z,
-0.5f + m_CubeSpecs.position.x,  0.5f + m_CubeSpecs.position.y,  0.5f + m_CubeSpecs.position.z,
// back
-0.5f + m_CubeSpecs.position.x, -0.5f + m_CubeSpecs.position.y, -0.5f + m_CubeSpecs.position.z,
 0.5f + m_CubeSpecs.position.x, -0.5f + m_CubeSpecs.position.y, -0.5f + m_CubeSpecs.position.z,
 0.5f + m_CubeSpecs.position.x,  0.5f + m_CubeSpecs.position.y, -0.5f + m_CubeSpecs.position.z,
-0.5f + m_CubeSpecs.position.x,  0.5f + m_CubeSpecs.position.y, -0.5f + m_CubeSpecs.position.z
	};*/
	m_QuadSides = new PrimitiveObject::Quad[6];
	PrimitiveObject::Quad* quadPtr = m_QuadSides;
	for (int z = -1; z < 2; z += 2) { // z
		for (int y = -1; y < 2; y += 2) { // z
			for (int x = -1; x < 2; x += 2) { // z
				quadPtr->SetSpec({ 1.0f,1.0f,m_CubeSpecs.position + glm::vec3{0.5 * x,0.5 * y,0.5 * z} });
				//quadPtr->SetColor(glm::vec4{0.5 + x,0.5 + y,0.5 + z,1.0f}); 
				quadPtr++;
			}
		}
	}
	quadPtr = nullptr; 
	for (int i = 0; i < 6; i++) {
		this->Vertices.insert(this->Vertices.end(), m_QuadSides[i].get_vertices().begin(), m_QuadSides[i].get_vertices().end() );
	}
	for (int offset = 0; offset < 6; offset++) {
		std::vector<uint32_t> QuadIndices = m_QuadSides[offset].get_indices(); 
		for (int i = 0; i < 6; i++) {
			QuadIndices[i] += offset * 4; 
		}
		this->Indices.insert(this->Indices.end(), QuadIndices.begin(), QuadIndices.end()); // ERROR GER
	}
	
}

PrimitiveObject::Cube::~Cube()
{
	delete[] m_QuadSides;
}


PrimitiveObject::Quad::~Quad()
{
}

PrimitiveObject::Quad::Quad()
{
	float quad_vertices[] = {
	-0.5 * m_QuadSpecs.width + m_QuadSpecs.position.x ,-0.5 * m_QuadSpecs.height + m_QuadSpecs.position.y ,m_QuadSpecs.position.z, // bottom left 
	-0.5 * m_QuadSpecs.width + m_QuadSpecs.position.x ,0.5 * m_QuadSpecs.height + m_QuadSpecs.position.y ,m_QuadSpecs.position.z, // top left
	0.5 * m_QuadSpecs.width + m_QuadSpecs.position.x ,-0.5 * m_QuadSpecs.height + m_QuadSpecs.position.y ,m_QuadSpecs.position.z, // bottom right
	0.5 * m_QuadSpecs.width + m_QuadSpecs.position.x  ,0.5 * m_QuadSpecs.height + m_QuadSpecs.position.y ,m_QuadSpecs.position.z // top right
	};
	glm::vec3 QuadNormal = CalculateNormal(glm::vec3{ quad_vertices[3],quad_vertices[4],quad_vertices[5] },
		glm::vec3{ quad_vertices[6],quad_vertices[7],quad_vertices[8] }, glm::vec3{ quad_vertices[9],quad_vertices[10],quad_vertices[11] });

	for (int i = 0; i < 4; i++)
		this->Vertices.push_back({ glm::vec3{quad_vertices[3 * i], quad_vertices[3 * i + 1], quad_vertices[3 * i + 2] },QuadNormal,
			glm::vec4{1.0f,0.0f,0.0f,1.0f}, glm::vec2{(float)(i > 1),(float)((i+1) % 2)}, 0.0f });

	this->Indices.push_back(1);
	this->Indices.push_back(2);
	this->Indices.push_back(3);
	this->Indices.push_back(1);
	this->Indices.push_back(0);
	this->Indices.push_back(2);
}

PrimitiveObject::Quad::Quad(QuadSpecifications spec)
{
	m_QuadSpecs = spec; 
	float quad_vertices[] = {
-0.5 * m_QuadSpecs.width + m_QuadSpecs.position.x ,-0.5 * m_QuadSpecs.height + m_QuadSpecs.position.y ,m_QuadSpecs.position.z, // bottom left 
-0.5 * m_QuadSpecs.width + m_QuadSpecs.position.x ,0.5 * m_QuadSpecs.height + m_QuadSpecs.position.y ,m_QuadSpecs.position.z, // top left
0.5 * m_QuadSpecs.width + m_QuadSpecs.position.x ,-0.5 * m_QuadSpecs.height + m_QuadSpecs.position.y ,m_QuadSpecs.position.z, // bottom right
0.5 * m_QuadSpecs.width + m_QuadSpecs.position.x  ,0.5 * m_QuadSpecs.height + m_QuadSpecs.position.y ,m_QuadSpecs.position.z, // top right
	};
	glm::vec3 QuadNormal = CalculateNormal(glm::vec3{ quad_vertices[3],quad_vertices[4],quad_vertices[5] },
		glm::vec3{ quad_vertices[6],quad_vertices[7],quad_vertices[8] }, glm::vec3{ quad_vertices[9],quad_vertices[10],quad_vertices[11] });
	for (int i = 0; i < 4; i++)
		this->Vertices.push_back({ glm::vec3(quad_vertices[3 * i], quad_vertices[3 * i + 1], quad_vertices[3 * i + 2]) ,QuadNormal,
			glm::vec4{1.0f,0.0f,0.0f,1.0f},glm::vec2{(float)(i > 1),(float)((i + 1) % 2)},0.0f });
}


PrimitiveObject::Quad::Quad(const Quad& quad) : Object(quad)
{
	this->m_QuadSpecs = quad.m_QuadSpecs;
}

void PrimitiveObject::Quad::MoveToPoint(const glm::vec3& pos)
{
	this->Vertices[0].VertexPosition = glm::vec3{ -0.5f * m_QuadSpecs.width + pos.x, -0.5f * m_QuadSpecs.height + pos.y, pos.z }; 
	this->Vertices[1].VertexPosition = glm::vec3{ -0.5f * m_QuadSpecs.width + pos.x, 0.5f * m_QuadSpecs.height + pos.y, pos.z };
	this->Vertices[2].VertexPosition = glm::vec3{ 0.5f * m_QuadSpecs.width + pos.x, -0.5f * m_QuadSpecs.height + pos.y, pos.z }; 
	this->Vertices[3].VertexPosition = glm::vec3{ 0.5f * m_QuadSpecs.width + pos.x, 0.5f * m_QuadSpecs.height + pos.y, pos.z }; 
}

void PrimitiveObject::Quad::SetSpec(QuadSpecifications spec)
{
	m_QuadSpecs = spec; 
	Quad(m_QuadSpecs); 
}



/*
		static const float epsilon;
	static const bool isVertex(glm::vec3& first, glm::vec3& second) {
		glm::vec3 v = glm::epsilonEqual(first, second,epsilon);
		for (int i = 0; i < 3; i++) if (!v[i]) return false; 
		return true; 
	}
static const float epsilon;
	static const bool isVertex(glm::vec3& first, glm::vec3& second) {
		glm::vec3 v = glm::epsilonEqual(first, second,epsilon);
		for (int i = 0; i < 3; i++) if (!v[i]) return false; 
		return true; 
	}



Object::Object(std::string& filepath)
{
	std::ifstream stdFile(filepath);
	std::string line;
	std::string pos[3];
	unsigned int  index = 0;
	bool vertexIn = false; 
	while (std::getline(stdFile, line)) {
		if (line.find("vertex") != std::string::npos) {
			line = line.substr(line.find("vertex") + 7);
			std::stringstream coords(line);
			for (int i = 0; i < 3; i++) {
				coords >> pos[i];
			}
			glm::vec3 newVertx(glm::vec3(std::stof(pos[0]), std::stof(pos[1]), std::stof(pos[2])));
			if (Vertices.size() == 0) { Vertices.push_back(newVertx);  Indices.push_back(index); }
	
			else {
				for (unsigned int i = 0; i < Vertices.size(); i++) {
					if (isVertex(Vertices[i], newVertx)) {
						Indices.push_back(i); 
						vertexIn = true; 
					}
				}
			}
			if (!vertexIn) {
				Vertices.push_back(newVertx); ++index; Indices.push_back(index);
			}

			vertexIn = false;
		}
	}
}
*/

