//
// Created by Zohar Azar on 2019-01-25.
//

#include "../tux-draw/TuxDraw.h"
#include "TuxLeapFinger.h"

using namespace Leap;

TuxLeapFinger::TuxLeapFinger(Finger f) {
    finger=f;
    bones.insert(std::make_pair(Bone::Type::TYPE_METACARPAL,new TuxLeapBone(finger.bone(Bone::TYPE_METACARPAL))));
    bones.insert(std::make_pair(Bone::Type::TYPE_PROXIMAL,new TuxLeapBone(finger.bone(Bone::TYPE_PROXIMAL))));
    bones.insert(std::make_pair(Bone::Type::TYPE_DISTAL,new TuxLeapBone(finger.bone(Bone::TYPE_DISTAL))));
    bones.insert(std::make_pair(Bone::Type::TYPE_INTERMEDIATE,new TuxLeapBone(finger.bone(Bone::TYPE_INTERMEDIATE))));
}

/**
* The finger tip position in millimeters.
*
* @return Position
*/
Vector TuxLeapFinger::getPositionOfJointTip() {
    return finger.jointPosition(Finger::JOINT_TIP);
}

/**
 * The mcp joint position in millimeters.
 *
 * @return Position
 */
Vector TuxLeapFinger::getPositionOfJointMcp() {
    return finger.jointPosition(Finger::JOINT_MCP);
}

/**
 * The pip joint position in millimeters.
 *
 * @return Position
 */
Vector TuxLeapFinger::getPositionOfJointPip() {
    return finger.jointPosition(Finger::JOINT_PIP);
}

/**
 * The dip joint position in millimeters.
 *
 * @return Position
 */
Vector TuxLeapFinger::getPositionOfJointDip() {
    return finger.jointPosition(Finger::JOINT_DIP);
}


/**
* Draw the type of the finger.
*
* @param xShift Shift in x axis
* @param yShift Shift in y axis
* @param zShift Shift in z axis
*/
void TuxLeapFinger::drawName(float xShift, float yShift, float zShift) {
    Leap::Vector pos = getPosition();
    TuxDrawContainer::tuxDraw->drawText(getTypeName(), pos.x + xShift, pos.y + yShift, pos.z + zShift);
}

/**
* Draw the type of the finger.
*/
void TuxLeapFinger::drawName() {
    drawName(-0.15f, -0.15f, 0);
}
/**
* Draw all joints and bones of a finger.
*
* @param radius Radius
*/
void TuxLeapFinger::draw(float radius) {

    drawBones();
    drawJoints(radius);
   // drawName();
}


/**
     * Draw all bones of a finger.
     */
void TuxLeapFinger::drawBones() {
    getBone(Bone::Type::TYPE_METACARPAL).draw();
    getBone(Bone::Type::TYPE_PROXIMAL).draw();
    getBone(Bone::Type::TYPE_INTERMEDIATE).draw();
    if (getType() != 0) { // ≠thumb
        getBone(Bone::Type::TYPE_DISTAL).draw();
    }
}

Leap::Finger::Type TuxLeapFinger::getType() {
    return finger.type();
}

/**
 * Get a specific bone by numeric index.
 *
 * @param type (0-3, 0=distal, 1=intermediate, 2=proximal, 3=metacarpal).
 * @return Single bone or null
 */
TuxLeapBone TuxLeapFinger::getBone(Leap::Bone::Type type) {
    return *bones[type];
}


Leap::Vector TuxLeapFinger::getPosition() {//BUG?: TOOD: not sure tipPosition is the proper one
return finger.tipPosition();
}




/**
 * Get the name of fingertype (0-4, 0=thumb, 1=index, 2=middle, 3=ring, 4=pinky).
 *
 * @return Name of finger
 */
std::string TuxLeapFinger::getTypeName() {
    switch (finger.type()) {
        case TYPE_THUMB:
            return "thumb";
        case TYPE_INDEX:
            return "index";
        case TYPE_MIDDLE:
            return "middle";
        case TYPE_RING:
            return "ring";
        case TYPE_PINKY:
            return "pinky";
    }
    return "";
}
