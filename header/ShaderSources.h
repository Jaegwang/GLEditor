#pragma once

#include <GL/glew.h>
#include <vector>
#include <map>

class ShaderSources
{
private:

	std::map<std::string, GLuint> sources;

	std::vector<char> infoLog;

	ShaderSources() {}

	friend class ShaderPrograms;

public:

	static ShaderSources* pointer();

	bool compileShader(const char* name, const char* source, GLuint shaderType);
	void deleteShader(const char* name);

	const char* getLog();
};
