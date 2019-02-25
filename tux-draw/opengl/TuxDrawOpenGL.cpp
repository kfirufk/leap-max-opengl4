
//
// Created by Zohar Azar on 2019-01-26.
//

#include "../TuxDraw.h"
#include "../../tux-leap/TuxLeap.h"
#include "../../tux-leap/TuxLeapBone.h"
#include "../../tux-leap/TuxLeapFinger.h"
#include "../../tux-leap/TuxLeapArm.h"
#include "../../tux-leap/TuxLeapHand.h"
#include "./common/OpenGLWindow.h"
#include "staticGeometry.h"

namespace TuxDrawOpenGL {


    /*void timer(int) {
        glutPostRedisplay();
        glutTimerFunc(1000 / 30, timer, 0);
    }*/

    void staticDisplay() {
        TuxDrawContainer::tuxDraw->display();
    }

    void reshape(int w, int h) {
     /*   glViewport(0, 0, (GLsizei)w, (GLsizei)h);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        GLKMatrix4MakeOrtho(-1, 1, -1, -1, -1, 1);
        glMatrixMode(GL_MODELVIEW);*/
    }

}

void TuxDraw::draw() {
    TuxDraw::display();
}


void TuxDraw::display() {
    for (TuxLeapHand *hand : TuxLeap::hands) {
        hand->draw();
    }
}

int TuxDraw::init() {
    const std::string& windowTitle = "001.) Creating OpenGL4 Window - Tutorial by Michal Bubnar (www.mbsoftworks.sk)";
    int majorVersion = 4;
    int minorVersion = 1;
    bool showFullscreen = false;

    OpenGLWindow window;
    if (!window.createOpenGLWindow(windowTitle, majorVersion, minorVersion, showFullscreen))
    {
        printf("Failed to create window with OpenGL context %d.%d! Shutting down...\n", majorVersion, minorVersion);
        return 1;
    }

    window.runApp();
    if (window.hasErrorOccured())
    {
        std::cout << std::endl << std::endl << "Program could not start because of the above errors! Press ENTER to quit..." << std::endl;
        std::cin.get();
        return 1;
    }
    return 0;
}


void TuxLeapBone::draw() {
//        this.parent.stroke(0, 35);
    Bone::Type boneType = bone.type();
    Finger::Type fingerType = finger.type();
    Leap::Vector next = nextJoint().normalized();
    Leap::Vector prev = prevJoint().normalized();

    static_geometry::addFingerBoneData(fingerType,boneType,glm::vec3(next.x,next.y,next.z),
            glm::vec3(prev.x,prev.y,prev.z));
}

void TuxLeapFinger::drawJoints(float radius) {
    Leap::Vector tip = getPositionOfJointTip().normalized();
    Leap::Vector mcp = getPositionOfJointMcp().normalized();
    Leap::Vector pip = getPositionOfJointPip().normalized();
    Leap::Vector dip = getPositionOfJointDip().normalized();
    static_geometry::addFingerJointData(getType(),glm::vec3(tip.x,tip.y,tip.z),glm::vec3(pip.x,pip.y,pip.z),
            glm::vec3(dip.x,dip.y,dip.z),glm::vec3(mcp.x,mcp.y,mcp.z));
    /* TODO: check if adding mcp on thumb doesn't cause an exception. I don't draw that
    if (getType() != 0) { // ≠thumb
    }
     */
}

void TuxLeapArm::draw(float radius) {
    /**
 * Draw arm.
 *
 * @param radius Radius
 */
    Vector wristPos = getWristPosition().normalized();
    Vector elbowPos = getElbowPosition().normalized();
    static_geometry::armLines[0]=glm::vec3(wristPos.x, wristPos.y, wristPos.z);
    static_geometry::armLines[1]=glm::vec3(elbowPos.x, elbowPos.y, elbowPos.z);
    static_geometry::armSpheres[0]=glm::vec3(wristPos.x, wristPos.y, wristPos.z);
    static_geometry::armSpheres[1]=glm::vec3(elbowPos.x, elbowPos.y, elbowPos.z);
}

/**
* Draw the hand with all details.
*
* @param radius The radius of the ellipse (2D) or sphere (3D).
*/
void TuxLeapHand::draw(float radius) {

   /* Leap::Vector position = getPosition();
    glPushMatrix();
    glColor3f(0.921, 0.278, 0.360); // light red
    glTranslatef(position.x, position.y, position.z);
    glutSolidSphere(radius, 20, 20);
    glPopMatrix();*/
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

            static_geometry::jointsPolygonVertices[0]=glm::vec3(lastJointOfThumb.x, lastJointOfThumb.y, lastJointOfThumb.z);
            static_geometry::jointsPolygonVertices[1]=glm::vec3(lastJointOfIndex.x, lastJointOfIndex.y, lastJointOfIndex.z);
            static_geometry::jointsPolygonVertices[2]=glm::vec3(lastJointOfMiddle.x, lastJointOfMiddle.y, lastJointOfMiddle.z);
            static_geometry::jointsPolygonVertices[3]=glm::vec3(lastJointOfRing.x, lastJointOfRing.y, lastJointOfRing.z);
            static_geometry::jointsPolygonVertices[4]=glm::vec3(lastJointOfPinky.x, lastJointOfPinky.y, lastJointOfPinky.z);

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
        /*float newX=x;
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
        }*/ //TODO:implement in opengl4 with glfw
}

