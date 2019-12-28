#include "Shader.h"



Shader::Shader()
	:m_RendererID(0), path("")
{
}

Shader::Shader(const Shader& shader)
	:m_RendererID(shader.getRendererID()), path(shader.getPath())
{
}

Shader::Shader(const std::string& path)
	:path(path)
{
	shaderprogramSource shaderSource = parseSource(path);
	m_RendererID = createShader(shaderSource.vertexSource, shaderSource.fragmentSource);

}

Shader::~Shader()
{
	glDeleteShader(m_RendererID);
}



void Shader::bind() const
{
	GLCall(glUseProgram(m_RendererID));

}

void Shader::unbind() const
{
	GLCall(glUseProgram(0));
}

int Shader::getUniform(std::string name)
{
	int location = glGetUniformLocation(m_RendererID, name.c_str());
	if (location == -1)
	{
		std::cout << "Can't find uniform variable: " << name << "!" << std::endl;
	}
	return location;

}


shaderprogramSource Shader::parseSource(const std::string& shaderPath)
{
	std::ifstream stream = std::ifstream(shaderPath);
	enum class shaderType {
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};
	shaderType type = shaderType::NONE;

	std::string line;
	std::stringstream ss[2];

	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				type = shaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = shaderType::FRAGMENT;
		}

		else
		{
			ss[(int)type] << line << "\n";
		}

	}
	return { ss[0].str(), ss[1].str() };


}

unsigned int Shader::compileShader(unsigned int type, const std::string& sourceCode)
{
	unsigned int shader = glCreateShader(type);
	const char* src = sourceCode.c_str();
	glShaderSource(shader, 1, &src, nullptr);
	glCompileShader(shader);
	int compileState;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileState);
	if (compileState == GL_FALSE)
	{
		int length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(shader, length, &length, message);
		std::cout << "Failed to compile: " <<
			(type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader source code!" << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(shader);
		return 0;
	}
	return shader;

}


unsigned int Shader::createShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

	GLCall(glAttachShader(program, vs));
	GLCall(glAttachShader(program, fs));
	GLCall(glLinkProgram(program));
	GLCall(glValidateProgram(program));

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}