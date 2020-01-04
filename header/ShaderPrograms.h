#pragma once

#include <GL/glew.h>
#include <vector>
#include <stack>
#include <map>

class ShaderPrograms
{
private:

	std::map<std::string, GLuint> programs;

	std::stack<GLuint> shaders;

	std::vector<char> infoLog;

	ShaderPrograms() {}

public:

	static ShaderPrograms* pointer();

	bool attachShader(const char* name);
	bool linkProgram(const char* programName);

	void deleteProgram(const char* programName);

	const char* getLog();

	const GLuint getProgram(const char* programName);
};