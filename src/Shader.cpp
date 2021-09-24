#include "Shader.h"




int Shader::GetUniformLocation(const std::string& name) const
{
	const auto& f = hash.find(name);
	if (f != hash.end())
		return f->second;
	hash[name] = glGetUniformLocation(m_programid, name.c_str());
	return hash[name]; 
}

Shader::Shader(const std::string& path)
{
	m_shadersources = parseShaders(path); 
	m_programid = CreateShader(m_shadersources.VertexShaderSource, m_shadersources.FragmentShaderSource); 
	Bind(); 
}


Shader::~Shader()
{
	UnBind();
	glDeleteProgram(m_programid);

}

void Shader::Bind()
{
	glUseProgram(m_programid); 
}

void Shader::UnBind()
{
	glUseProgram(0); 
}

void Shader::UniformMatrix4(const std::string& name, float* data) 
{
	int MatrixID = GetUniformLocation(name); 
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, data); 

}

void Shader::UniformArrayINT(const std::string& name, uint32_t count, int32_t* data)
{
	int Uniform_ID = GetUniformLocation(name); 
	glUniform1iv(Uniform_ID, count, data); 
}
