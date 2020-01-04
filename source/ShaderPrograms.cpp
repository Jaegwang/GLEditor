#include <ShaderPrograms.h>
#include <ShaderSources.h>

#include <iostream>

ShaderPrograms* ShaderPrograms::pointer()
{
	static ShaderPrograms single;
	return &single;
}

bool ShaderPrograms::attachShader(const char* shaderName)
{
	ShaderSources* sshs = ShaderSources::pointer();

	auto it = sshs->sources.find(shaderName);

	if (it != sshs->sources.end())
	{
		shaders.push(it->second);
		return true;
	}
	else
	{
		return false;
	}
}

bool ShaderPrograms::linkProgram(const char* programName)
{
	GLuint program = glCreateProgram();

	while (shaders.empty() == false)
	{
		glAttachShader(program, shaders.top());
		shaders.pop();
	}

	glLinkProgram(program);

	GLint isLinked = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
	
	if (isLinked == GL_TRUE)
	{
		programs[programName] = program;
		return true;
	}
	else
	{
		GLint maxLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		infoLog.resize(maxLength);
		glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

		glDeleteProgram(program);
		return false;
	}
}

void ShaderPrograms::deleteProgram(const char* programName)
{
	auto it = programs.find(programName);
	if (it == programs.end()) return;

	programs.erase(programName);
	glDeleteProgram(it->second);
}

const char* ShaderPrograms::getLog()
{
	if (infoLog.empty()) return "OK";
	return &infoLog[0];
}

const GLuint ShaderPrograms::getProgram(const char* programName)
{
	auto it = programs.find(programName);
	
	if(it != programs.end())
	{
		return it->second;
	}
	else
	{
		return 0;
	}
}
