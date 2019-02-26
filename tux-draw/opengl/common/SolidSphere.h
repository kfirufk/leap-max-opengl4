//
// Created by Kfir Ozer on 2019-02-26.
//

#ifndef LEAP_SOLIDSPHERE_H
#define LEAP_SOLIDSPHERE_H

#include <GL/gl.h>
#include <vector>
#include <glm/glm.hpp>

class SolidSphere
{
public:
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> texcoords;
    std::vector<glm::vec4> indices;

    SolidSphere(float radius, unsigned int rings, unsigned int sectors);

    void draw(GLfloat x, GLfloat y, GLfloat z);
};

#endif //LEAP_SOLIDSPHERE_H
