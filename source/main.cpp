
#include <TrackBall.h>
#include <GL/glew.h>
#include <pybind11/pybind11.h>
#include <ShaderSources.h>
#include <ShaderPrograms.h>
#include <iostream>

void initGL()
{

}

void paintGL()
{

}

void resizeGL( int width, int height )
{

}

void trackMouseMove()
{

}

PYBIND11_MODULE(example, m) {
    
    m.doc() = "pybind11 example plugin"; // optional module docstring

    m.def("initGL", &initGL );
    m.def("paintGL", &paintGL );
    m.def("resizeGL", &resizeGL );

    m.def("trackMouse", &trackMouseMove);
}
