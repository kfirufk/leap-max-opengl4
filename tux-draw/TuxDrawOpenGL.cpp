
//
// Created by Zohar Azar on 2019-01-26.
//

#include "TuxDraw.h"
#include <GL/glut.h>  // GLUT, includes glu.h and gl.h
#include <GLKit/GLKMatrix4.h>
#include "../tux-leap/TuxLeap.h"
#include "../tux-leap/TuxLeapBone.h"
#include "../tux-leap/TuxLeapFinger.h"
#include "../tux-leap/TuxLeapArm.h"
#include "../tux-leap/TuxLeapHand.h"

namespace TuxDrawOpenGL {


    /*void timer(int) {
        glutPostRedisplay();
        glutTimerFunc(1000 / 30, timer, 0);
    }*/

    void staticDisplay() {
        TuxDrawContainer::tuxDraw->display();
    }

    void reshape(int w, int h) {
        glViewport(0, 0, (GLsizei)w, (GLsizei)h);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        GLKMatrix4MakeOrtho(-1, 1, -1, -1, -1, 1);
        glMatrixMode(GL_MODELVIEW);
    }

}

void TuxDraw::draw() {
    TuxDrawContainer::isDrawing=true;
    glutPostRedisplay();

}


void TuxDraw::display() {

    if (TuxDrawContainer::isDisplayReady) {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// Clear the color buffer

        for (TuxLeapHand *hand : TuxLeap::hands) {
            hand->draw();
        }
        glutSwapBuffers();
        setIsDrawDataRendered(true);
    }
    TuxDrawContainer::isDisplayReady = true;
    TuxDrawContainer::isDrawing = false;
}



void TuxDraw::init() {
    //TuxDrawContainer::tuxDraw=this;
    char fakeParam[] = "fake";
    char *fakeargv[] = { fakeParam, NULL };
    int fakeargc = 1;
    glutInit(&fakeargc, fakeargv);                 // Initialize GLUT
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutCreateWindow("OpenGL Setup Test"); // Create a window with the given title
    glutInitWindowSize(1920, 1080);   // Set the window's initial width & height
   // glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
    glutDisplayFunc(TuxDrawOpenGL::staticDisplay);
    glutIdleFunc(TuxDrawOpenGL::staticDisplay);// Register display callback handler for window re-paint
    glutReshapeFunc(TuxDrawOpenGL::reshape);
    //glutTimerFunc(0, TuxDrawOpenGL::timer,0);
    glutMainLoop();           // Enter the infinitel
}


void TuxLeapBone::draw() {
//        this.parent.stroke(0, 35);
    Leap::Vector next = nextJoint().normalized();
    Leap::Vector prev = prevJoint().normalized();
    glColor3f(0.090, 0.360, 0.709); // blue
    glBegin(GL_LINES);
    glVertex3f(next.x, next.y, next.z);
    glVertex3f(prev.x, prev.y, prev.z);
    glEnd();
}

void TuxLeapFinger::drawJoints(float radius) {
    Leap::Vector tip = getPositionOfJointTip().normalized();
    Leap::Vector mcp = getPositionOfJointMcp().normalized();
    Leap::Vector pip = getPositionOfJointPip().normalized();
    Leap::Vector dip = getPositionOfJointDip().normalized();
    glColor3f(0.109, 0.831, 0.431); // green
    glPushMatrix();
    glTranslatef(tip.x, tip.y, tip.z);
    glutSolidSphere(radius, 20, 20);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(pip.x, pip.y, pip.z);
    glutSolidSphere(radius, 20, 20);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(dip.x, dip.y, dip.z);
    glutSolidSphere(radius, 20, 20);
    glPopMatrix();
    if (getType() != 0) { // ≠thumb
        glPushMatrix();
        glTranslatef(mcp.x, mcp.y, mcp.z);
        glutSolidSphere(radius, 20, 20);
        glPopMatrix();
    }
}

void TuxLeapArm::draw(float radius) {
    /**
 * Draw arm.
 *
 * @param radius Radius
 */
    Vector wristPos = getWristPosition().normalized();
    Vector elbowPos = getElbowPosition().normalized();

    glBegin(GL_LINES);
    glVertex3f(wristPos.x, wristPos.y, wristPos.z);
    glVertex3f(elbowPos.x, elbowPos.y, elbowPos.z);
    glEnd();
    glPushMatrix();
    glTranslatef(wristPos.x, wristPos.y, wristPos.z);
    glutSolidSphere(radius, 20, 20);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(elbowPos.x, elbowPos.y, elbowPos.z);
    glutSolidSphere(radius, 20, 20);
    glPopMatrix();
}

/**
* Draw the hand with all details.
*
* @param radius The radius of the ellipse (2D) or sphere (3D).
*/
void TuxLeapHand::draw(float radius) {

    Leap::Vector position = getPosition();
    glPushMatrix();
    glColor3f(0.921, 0.278, 0.360); // light red
    glTranslatef(position.x, position.y, position.z);
    glutSolidSphere(radius, 20, 20);
    glPopMatrix();
    // Is there any arm?
    if (hasArm()) {
        getArm().draw();
    }

    // Are there any fingers?
    if (hasFingers()) {
        if (countFingers() == 5) {
            Leap::Vector lastJointOfThumb = getThumb().getBone(Leap::Bone::TYPE_PROXIMAL).prevJoint().normalized();
            Leap::Vector lastJointOfIndex = getIndexFinger().getBone(Leap::Bone::TYPE_METACARPAL).prevJoint().normalized();
            Leap::Vector lastJointOfMiddle = getMiddleFinger().getBone(Leap::Bone::TYPE_METACARPAL).prevJoint().normalized();
            Leap::Vector lastJointOfRing = getRingFinger().getBone(Leap::Bone::TYPE_METACARPAL).prevJoint().normalized();
            Leap::Vector lastJointOfPinky = getPinkyFinger().getBone(Leap::Bone::TYPE_METACARPAL).prevJoint().normalized();

            glBegin(GL_POLYGON);
            glColor3f(0.819, 0.525, 0.933); // purple
            glVertex3f(lastJointOfThumb.x, lastJointOfThumb.y, lastJointOfThumb.z);
            glVertex3f(lastJointOfIndex.x, lastJointOfIndex.y, lastJointOfIndex.z);
            glVertex3f(lastJointOfMiddle.x, lastJointOfMiddle.y, lastJointOfMiddle.z);
            glVertex3f(lastJointOfRing.x, lastJointOfRing.y, lastJointOfRing.z);
            glVertex3f(lastJointOfPinky.x, lastJointOfPinky.y, lastJointOfPinky.z);

            glEnd();
        }
        for (TuxLeapFinger *finger : getFingers()) {
            finger->draw();
        }
    }

    // Basic information
    std::ostringstream stringStream;
    stringStream.precision(2);
    stringStream << "hand side: " << (isLeft() ? "left" : "right")  <<
            "\noutstretched fingers: " << getOutstretchedFingers().size() <<
             "\ntime visible: " << getTimeVisible() <<
             "\npinch strength: " << getPinchStrength() <<
             "\ngrab strength: " << getGrabStrength();

             TuxDrawContainer::tuxDraw->drawText(stringStream.str(), -0.9, -0.7f, 0);
}

void TuxDraw::drawText(std::string txt, float x, float y, float z) {
        float newX=x;
        float newY=y;
        float newZ=z;
        glRasterPos3f(x, y, z);
        for(char& c :txt) {
            if (c == 10) {
                newY+=0.1;
                glRasterPos3f(newX, newY, newZ);
            } else {
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, c);
            }
        }
}

