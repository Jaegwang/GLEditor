#include <ShaderSources.h>

ShaderSources* ShaderSources::pointer()
{
	static ShaderSources single;
	return &single;
}

bool ShaderSources::compileShader(const char* name, const char* source, GLuint shaderType)
{
	GLuint shd = glCreateShader(shaderType);
	glShaderSource(shd, 1, &source, NULL);
	glCompileShader(shd);

	GLint isCompiled = 0;
	glGetShaderiv(shd, GL_COMPILE_STATUS, &isCompiled);

	if(isCompiled == GL_TRUE)
	{
		sources[name] = shd;
		return true;
	}
	else
	{
		GLint maxLength = 0;
		glGetShaderiv(shd, GL_INFO_LOG_LENGTH, &maxLength);

		infoLog.resize(maxLength);
		glGetShaderInfoLog(shd, maxLength, &maxLength, &infoLog[0]);

		glDeleteShader(shd);
		return false;
	}
}

void ShaderSources::deleteShader(const char* name)
{
	auto it = sources.find(name);
	if (it == sources.end()) return;

	sources.erase(name);
	glDeleteShader(it->second);
}

const char* ShaderSources::getLog()
{
	if (infoLog.empty()) return "OK";
	return &infoLog[0];
}
