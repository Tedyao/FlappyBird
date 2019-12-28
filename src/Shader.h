#pragma once
#include "GameSettings.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

struct shaderprogramSource {
	std::string vertexSource;
	std::string fragmentSource;
};


class Shader
{
private:
	unsigned int m_RendererID;
	const std::string path;
public:
	Shader();
	Shader(const Shader& shader);
	Shader(const std::string& path);
	~Shader();
	void bind() const;
	void unbind() const;
	inline unsigned int getRendererID() const{ return m_RendererID; };
	inline const std::string& getPath() const { return path; };
	int getUniform(std::string name);
	void setUniform1i(std::string name, int value);
	void setUniform1f(std::string name, float value);
	void setUniformMat4f(std::string name, const float* matrix);
	void setUniform4f(std::string name, float v0, float v1, float v2, float v3);
	void setUniformMat4f(std::string name, const glm::mat4& matrix);
	void operator=(const Shader& otherShader);
private:
	unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);
	unsigned int compileShader(unsigned int type, const std::string& sourceCode);
	shaderprogramSource parseSource(const std::string& shaderPath);
};

inline void Shader::setUniform1f(std::string name, float value)
{
	int location = getUniform(name);
	GLCall(glUniform1f(location, value));
}

inline void Shader::setUniform1i(std::string name, int value)
{
	int location = getUniform(name);
	GLCall(glUniform1i(location, value));
	
}


inline void Shader::setUniformMat4f(std::string name, const float* matrix)
{
	int location = getUniform(name);
	GLCall(glUniformMatrix4fv(location, 1, GL_TRUE, matrix););
	

}

inline void Shader::setUniformMat4f(std::string name, const glm::mat4& matrix)
{
	int location = getUniform(name);
	GLCall(glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]););


}

inline void Shader::operator=(const Shader& otherShader)
{
	this->m_RendererID = otherShader.getRendererID();
}

inline void Shader::setUniform4f(std::string name, float v0, float v1, float v2, float v3)
{
	int location = getUniform(name);
	GLCall(glUniform4f(location, v0, v1, v2, v3));
}