//
// Created by Zohar Azar on 2019-01-28.
//

#include "TuxLeapArm.h"


/**
* Is it a valid Arm object?
*
* @return Is it a valid Arm object?
*/
bool TuxLeapArm::isValid() {
    return arm.isValid();
}

/**
 * Get the raw instance of com.leapmotion.leap.Arm.
 *
 * @return Raw instance of Arm
 */
Arm TuxLeapArm::getRaw() {
    return arm;
}

/**
 * The position of the elbow.
 *
 * @return Position
 */
Vector TuxLeapArm::getElbowPosition() {
    return arm.elbowPosition();
}


/**
 * The position of the wrist.
 *
 * @return Position
 */
Vector TuxLeapArm::getWristPosition() {
    return arm.wristPosition();
}

/**
 * The average width of the arm.
 *
 * @return Width
 */
float TuxLeapArm::getWidth() {
    return arm.width();
}

/**
 * The center position.
 *
 * @return Position
 */
Vector TuxLeapArm::getPosition() {
    return arm.center();
}


TuxLeapArm::TuxLeapArm(Arm a) {
arm=a;
}