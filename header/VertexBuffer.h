#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

class VertexBuffers
{
private:

	GLuint vao = 0;

	std::vector<GLuint> buffers;
	std::vector<GLint> tupleSize;

	unsigned int numVertices = 0;

public:

	VertexBuffers()
	{}

	~VertexBuffers()
	{}
	
	void clear();
	void generate();

	void bindBuffer(const std::vector<float>& data);
	void bindBuffer(const std::vector<glm::vec2>& data);
	void bindBuffer(const std::vector<glm::vec3>& data);
	void bindBuffer(const std::vector<glm::vec4>& data);

	void draw();
};

inline void VertexBuffers::clear()
{
	for (int n = 0; n < buffers.size(); ++n)
	{
		glDeleteBuffers(1, &buffers[n]);
	}

	buffers.clear();

	if (vao != 0)
	{
		glDeleteVertexArrays(1, &vao);
		vao = 0;
	}
}

inline void VertexBuffers::generate()
{
	if (vao == 0) glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	for (int n = 0; n < buffers.size(); ++n)
	{
		glBindBuffer(GL_ARRAY_BUFFER, buffers[n]);
		glVertexAttribPointer(n, tupleSize[n], GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(n);
	}
}

inline void VertexBuffers::draw()
{
	if (vao == 0) return;

	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, numVertices);
}

inline void VertexBuffers::bindBuffer(const std::vector<float>& data)
{
	numVertices = (unsigned int)data.size();

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, numVertices*sizeof(float), &data[0], GL_STATIC_DRAW);

	buffers.push_back(vbo);
	tupleSize.push_back(1);
}

inline void VertexBuffers::bindBuffer(const std::vector<glm::vec2>& data)
{
	numVertices = (unsigned int)data.size();

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, numVertices*sizeof(glm::vec2), &data[0][0], GL_STATIC_DRAW);

	buffers.push_back(vbo);
	tupleSize.push_back(2);
}

inline void VertexBuffers::bindBuffer(const std::vector<glm::vec3>& data)
{
	numVertices = (unsigned int)data.size();

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, numVertices*sizeof(glm::vec3), &data[0][0], GL_STATIC_DRAW);

	buffers.push_back(vbo);
	tupleSize.push_back(3);
}

inline void VertexBuffers::bindBuffer(const std::vector<glm::vec4>& data)
{
	numVertices = (unsigned int)data.size();

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, numVertices*sizeof(glm::vec4), &data[0][0], GL_STATIC_DRAW);

	buffers.push_back(vbo);
	tupleSize.push_back(4);
}
