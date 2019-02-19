//
// Created by Zohar Azar on 2019-01-12.
//

#include "my-opengl.h"
#include <GLKit/GLKMatrix4.h>
#include "my-leap.h"
/* Handler for window-repaint event. Call back when the window first appears and
   whenever the window needs to be re-painted. */


// Using The STL Exception Library Increases The
// Chances That Someone Else Using Our Code Will Correctly
// Catch Any Exceptions That We Throw.
#include <stdexcept>

float verticesQuads[] = {
        0.2f, 0.2f, 0.0f,
        0.2f,  0.1f, 0.0f,
        0.1f, 0.1f, 0.0f,
        0.1f, 0.2f, 0.0f,
};


float verticesTriangles[] = {
        -0.5f, -0.6f, 0.0f,
        0.5f, -0.6f, 0.0f,
        -0.2f,  -0.2f, 0.0f,

        0.5f, 0.6f, 0.0f,
        -0.5f, 0.6f, 0.0f,
        0.2f,  0.2f, 0.0f,

        0.4f, 0.5f, 0.0f,
        -0.4f, 0.5f, 0.0f,
        0.1f,  0.1f, 0.0f,



};

float colorsQuads[] = {
        1.0f, 0.0f, 0.0f, // red
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
};

float colorsFingers[] = {
        1.0f, 0.0f, 0.0f, // red
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,

        1.0f, 0.0f, 0.0f, // red
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,

        1.0f, 0.0f, 0.0f, // red
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, // green
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,

        0.0f, 1.0f, 0.0f, // green
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,

        0.0f, 1.0f, 0.0f, // green
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,

        0.0f, 0.0f, 1.0f, // blue
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,

        0.0f, 0.0f, 1.0f, // blue
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,

        0.0f, 0.0f, 1.0f, // blue
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,

        1.0f, 0.0f, 0.0f, // red
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,

        1.0f, 0.0f, 0.0f, // red
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,

        1.0f, 0.0f, 0.0f, // red
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, // green
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,

        0.0f, 1.0f, 0.0f, // green
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,

        0.0f, 1.0f, 0.0f, // green
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,

};


float colorsTrangles[] = {
        1.0f, 0.0f, 0.0f, // red
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, // green
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f, // blue
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
};

void renderbitmap(float x, float y, void *font, char *string) {
    char *c;
    glRasterPos2f(x,y);
    for (c=string; *c != '\0'; c++) {
        glutBitmapCharacter(font,*c);
    }
}

void introscreen() {
    glColor3f(1.f,1.f,1.f);
    char buf[100] = {0};
    sprintf(buf,"%d %d",fingersBonesTriangles.size(), fingersBonesTrianglesColors.size());
    renderbitmap(-0.8,0.8,GLUT_BITMAP_TIMES_ROMAN_24, buf);
}


void drawTriangle() {
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, verticesTriangles);

    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, colorsTrangles);

    glDrawArrays(GL_TRIANGLES, 0, 9);

    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void drawHands() {

        glPointSize(10);

        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, &fingersBonesTriangles[0]);
        //   glDisableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);
        glColorPointer(4, GL_FLOAT, 0, &fingersBonesTrianglesColors[0]);
        //    glDisableClientState(GL_COLOR_ARRAY);
        glDrawArrays(GL_POINTS, 0, fingersBonesTriangles.size());
        //glDisableClientState(GL_COLOR_ARRAY);
        //glDisableClientState(GL_VERTEX_ARRAY);
        introscreen();

}

void drawPoints() {
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, verticesQuads);

    glEnableClientState(GL_COLOR_ARRAY);
    glPointSize(10);
    glColorPointer(3, GL_FLOAT, 0, colorsQuads);

    glDrawArrays(GL_POINTS, 0, 4);

    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void drawLines() {
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, verticesQuads);

    glEnableClientState(GL_COLOR_ARRAY);
    glLineWidth(10);
    glColorPointer(3, GL_FLOAT, 0, colorsQuads);

    glDrawArrays(GL_LINES, 0, 4);

    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}


void drawQuad() {
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, verticesQuads);

    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, colorsQuads);

    glDrawArrays(GL_QUADS, 0, 4);

    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLKMatrix4MakeOrtho(-1, 1, -1, -1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}

void display() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
    glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer
    // activate and specify pointer to vertex array
    if (isFingerBonesComputed && !isFingerBonesRendered) {

        drawHands();
    glutSwapBuffers();
        isFingerBonesComputed = false;
        isFingerBonesRendered = false;
    }

}

Controller controller;
SampleListener listener;


void timer(int) {
    glutPostRedisplay();
    //vertices[0]+=0.01f;
    glutTimerFunc(1000/30, timer, 0);
}


int main(int argc, char** argv) {
   /* glGenVertexArraysAPPLE(1, &vao);  //create VAO container and get ID for it
    glBindVertexArrayAPPLE(vao);      //bind to OpenGL context
    glGenBuffers(1, &vbo);
    //glBindBuffer(GL_ARRAY_BUFFER, vbo);//bind to context
    //glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * vertices.size(), &vertices[0], GL_STATIC_DRAW);*/
    controller.addListener(listener); // init leap
    controller.setPolicy(Leap::Controller::POLICY_BACKGROUND_FRAMES);
    glutInit(&argc, argv);                 // Initialize GLUT
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutCreateWindow("OpenGL Setup Test"); // Create a window with the given title
    glutInitWindowSize(1024, 768);   // Set the window's initial width & height
    glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
    glutDisplayFunc(display); // Register display callback handler for window re-paint
   // glutReshapeFunc(reshape);
    glutTimerFunc(0, timer,0);
    glutMainLoop();           // Enter the infinitely event-processing loop
    controller.removeListener(listener);
    return 0;
}