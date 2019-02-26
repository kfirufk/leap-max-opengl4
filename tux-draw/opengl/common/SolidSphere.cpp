//
// Created by Kfir Ozer on 2019-02-26.
//
// modified from https://stackoverflow.com/questions/5988686/creating-a-3d-sphere-in-opengl-using-visual-c
#include "SolidSphere.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <glm/glm.hpp>
#include <vector>
#include <cmath>

    SolidSphere::SolidSphere(float radius, unsigned int rings, unsigned int sectors)
    {
        float const R = 1./(float)(rings-1);
        float const S = 1./(float)(sectors-1);
        int r, s;

        vertices.resize(rings * sectors);
        normals.resize(rings * sectors);
        texcoords.resize(rings * sectors);
        std::vector<glm::vec3>::iterator v = vertices.begin();
        std::vector<glm::vec3>::iterator n = normals.begin();
        std::vector<glm::vec2>::iterator t = texcoords.begin();
        for(r = 0; r < rings; r++) for(s = 0; s < sectors; s++) {
                float const y = sin( -M_PI_2 + M_PI * r * R );
                float const x = cos(2*M_PI * s * S) * sin( M_PI * r * R );
                float const z = sin(2*M_PI * s * S) * sin( M_PI * r * R );

                *t++ = glm::vec2(s*S,r*R);

                *v++ = glm::vec3(x * radius, y * radius,z * radius);

                *n++ = glm::vec3(x,y,z);
            }

        indices.resize(rings * sectors);
        std::vector<glm::vec4>::iterator i = indices.begin();
        for(r = 0; r < rings; r++) for(s = 0; s < sectors; s++) {
                *i++ = glm::vec4(
                        (r * sectors + s)/20.0,
                        (r * sectors + (s+1))/20.0,
                        ((r+1) * sectors + (s+1))/20.0,
                        ((r+1) * sectors + s)/20.0);
            }
    }

    void SolidSphere::draw(GLfloat x, GLfloat y, GLfloat z)
    {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslatef(x,y,z);

        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);

        glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
        glNormalPointer(GL_FLOAT, 0, &normals[0]);
        glTexCoordPointer(2, GL_FLOAT, 0, &texcoords[0]);
        glDrawElements(GL_QUADS, indices.size(), GL_UNSIGNED_SHORT, &indices[0]);
        glPopMatrix();
    }
