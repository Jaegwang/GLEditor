
//https://galid1.tistory.com/483

#define STRINGIFY(x) #x

#include <GL/glew.h>
#include <iostream>
#include <pybind11/pybind11.h>
#include <atomic>
#include <thread>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp> 

#include <ShaderSources.h>
#include <ShaderPrograms.h>
#include <Loader.h>
#include <VertexBuffer.h>

namespace py = pybind11;

const char* vertex_source = STRINGIFY(

\n #version 430 \n

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_normal;
layout(location = 2) in vec2 uvTexs;

uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;

varying vec3 pos;
varying vec3 nor;


void main()
{
	pos = vec3(modelViewMatrix * vec4(vertex_position, 1.0));
	nor = vec3(modelViewMatrix * vec4(vertex_normal, 0.0));

	gl_Position = projectionMatrix * modelViewMatrix * vec4(vertex_position, 1.0);
}

);

const char* fragment_source = STRINGIFY(

\n #version 430 \n

out vec4 fragColour;

varying vec3 pos;
varying vec3 nor;

void main()
{
	vec3 lightPos = vec3(100.0, 0.0, 100.0);
	vec3 eyePos = vec3(0.0, 0.0, 0.0);


	vec3 l = normalize(lightPos - pos);
	vec3 e = normalize(eyePos - pos);
	vec3 n = normalize(nor);


	float dif = dot(l, n);


	fragColour = vec4(dif, 0.0, 0.5, 1.0);
}

);


int gWidth(1), gHeight(1);

std::vector<glm::vec3> positions, normals;
std::vector<glm::vec2> uv;
VertexBuffers bff;

GLuint program;


void initGL()
{
	if (glewInit() != GLEW_OK) {}

	glEnable(GL_DEPTH_TEST);

	ShaderSources* sources = ShaderSources::pointer();
	ShaderPrograms* programs = ShaderPrograms::pointer();


	glClearColor(0.5, 0.5, 0.5, 1.0);


	if (sources->compileShader("simple_vertex", vertex_source, GL_VERTEX_SHADER) == false)
		std::cout << sources->getLog() << std::endl;

	if (sources->compileShader("simple_fragment", fragment_source, GL_FRAGMENT_SHADER) == false)
		std::cout << sources->getLog() << std::endl;


	programs->attachShader("simple_vertex");
	programs->attachShader("simple_fragment");

	if (programs->linkProgram("simple") == false)
		std::cout << programs->getLog() << std::endl;


	program = programs->getProgram("simple");


	loadOBJ("data/suzanne.obj", positions, normals, uv);

	std::cout << positions.size() << std::endl;


	bff.bindBuffer(positions);
	bff.bindBuffer(normals);
	bff.bindBuffer(uv);

	bff.generate();

}

void paintGL()
{	
	float aspect = (float)gWidth / (float)gHeight;

	glm::mat4 modelMatrix = glm::translate(glm::mat4(1.f), glm::vec3(0.0f, 0.0f, -5.0f));
	//glm::mat4 viewMatrix = glm::lookAt(glm::vec3(0.f, 0.f, 10.f), glm::vec3(0.f, 0.f, -1.f), glm::vec3(0.f, 1.f, 0.f));
	glm::mat4 viewMatrix = glm::mat4(1.f);

	glm::mat4 modelViewMatrix = viewMatrix * modelMatrix;
	glm::mat4 projectionMatrix = glm::perspective(glm::radians(60.f), aspect, 0.1f, 10000.0f);


	/* Render here */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	if (program > 0)
	{
		glUseProgram(program);

		glUniformMatrix4fv(glGetUniformLocation(program, "modelViewMatrix"), 1, GL_FALSE, &modelViewMatrix[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(program, "projectionMatrix"), 1, GL_FALSE, &projectionMatrix[0][0]);

		bff.draw();
	}

}

void resizeGL(int width, int height)
{
	gWidth = width;
	gHeight = height;

	glViewport(0, 0, width, height);
}

void build(const char* vtx_src, const char* frag_src)
{
	ShaderSources* sources = ShaderSources::pointer();
	ShaderPrograms* programs = ShaderPrograms::pointer();
	
	sources->deleteShader("simple_vertex");
	sources->deleteShader("simple_fragment");
	programs->deleteProgram("simple");	
	program = 0;

	if (sources->compileShader("simple_vertex", vtx_src, GL_VERTEX_SHADER) == false)
		std::cout << sources->getLog() << std::endl;

	if (sources->compileShader("simple_fragment", frag_src, GL_FRAGMENT_SHADER) == false)
		std::cout << sources->getLog() << std::endl;


	programs->attachShader("simple_vertex");
	programs->attachShader("simple_fragment");

	if (programs->linkProgram("simple") == false)
		std::cout << programs->getLog() << std::endl;


	program = programs->getProgram("simple");
}

PYBIND11_MODULE(example, m) 
{

	m.doc() = "pybind11 example plugin"; // optional module docstring
	
	m.def("initGL", &initGL);
	m.def("paintGL", &paintGL);
	m.def("resizeGL", &resizeGL);

	m.def("build", &build);

}
