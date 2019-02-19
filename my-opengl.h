//
// Created by Zohar Azar on 2019-01-13.
//

#ifndef LEAP_MY_OPENGL_H
#define LEAP_MY_OPENGL_H

#include <glm/glm.hpp>
#include <GL/glut.h>  // GLUT, includes glu.h and gl.h

GLuint vbo, vao;

/*void initBuffer() {
    GLuint vao;
    glGenVertexArrays(1, &vao);
    GLuint vbo;
    glGenBuffers(1, &vbo); // Generate 1 buffer
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

}*/


struct VertexFormat
{
    glm::vec3 position;//our first vertex attribute

    VertexFormat(const glm::vec3 &pos)
    {
        position = pos;
    }
};

#endif //LEAP_MY_OPENGL_H
