#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>

struct ShaderSources {
	std::string VertexShaderSource;
	std::string FragmentShaderSource;
};

class Shader {
private:
	ShaderSources m_shadersources; 
	static ShaderSources parseShaders(const std::string& path) {
		enum class SHADER_TYPE {
			NONE = -1, VERTEX = 0, FRAGMENT = 1
		};
		std::ifstream stream(path);
		std::string line;
		std::stringstream ss[2];
		SHADER_TYPE type = SHADER_TYPE::NONE;
		while (std::getline(stream, line)) {
			if (line.find("#shader") != std::string::npos) {
				if (line.find("vertex") != std::string::npos) {
					type = SHADER_TYPE::VERTEX;
				}
				else if (line.find("fragment") != std::string::npos) {
					type = SHADER_TYPE::FRAGMENT;
				}

			}
			else {
				ss[(int)type] << line << '\n';
			}
		}
		return { ss[0].str(), ss[1].str() };
	}

	static unsigned int CompileShader(unsigned int type, const std::string& source) {
		unsigned int id = glCreateShader(type);
		const char* src = source.c_str();
		glShaderSource(id, 1, &src, nullptr);
		glCompileShader(id);

		//ERROR HANDLING
		int result;
		glGetShaderiv(id, GL_COMPILE_STATUS, &result);
		if (!result) {
			int length;

			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
			char* message = (char*)_malloca(length * sizeof(char));
			glGetShaderInfoLog(id, length, &length, message);
			std::cout << "Failed to compute" << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "shader!" << std::endl << message << std::endl;
		}

		return id;
	}
	static int CreateShader(static std::string& vertexShader, static std::string& fragmentShader) {
		unsigned int program = glCreateProgram();
		unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
		unsigned int frag = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
		glAttachShader(program, vs);
		glAttachShader(program, frag);
		glLinkProgram(program);
		glValidateProgram(program);
		glDeleteShader(vs);
		glDeleteShader(frag);
		return program;
	}
	int GetUniformLocation(const std::string& name) const;
	int m_programid; 
	mutable std::unordered_map<std::string,int> hash; 
public: 
	Shader(const std::string& path); 

	~Shader(); 
	void Bind(); 
	void UnBind(); 
	void UniformMatrix4(const std::string& name, float* data) ;
	void UniformArrayINT(const std::string& name, uint32_t count, int32_t* data);
};