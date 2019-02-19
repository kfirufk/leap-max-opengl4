//
// Created by Zohar Azar on 2019-01-28.
//

#ifndef LEAP_TUXLEAPARM_H
#define LEAP_TUXLEAPARM_H

#include "LeapConfig.h"
#include "Leap.h"

using namespace Leap;

class TuxLeapArm : Arm {
private:
    Arm arm;
public:
    TuxLeapArm(Arm a);
    /**
 * Is it a valid Arm object?
 *
 * @return Is it a valid Arm object?
 */
    bool isValid();

    /**
     * Get the raw instance of com.leapmotion.leap.Arm.
     *
     * @return Raw instance of Arm
     */
    Arm getRaw();

    /**
     * The position of the elbow.
     *
     * @return Position
     */
Vector getElbowPosition();


    /**
     * The position of the wrist.
     *
     * @return Position
     */
Vector getWristPosition();

    /**
     * The average width of the arm.
     *
     * @return Width
     */
float getWidth();

    /**
     * The center position.
     *
     * @return Position
     */
Vector getPosition();


    /**
     * Draw arm.
     *
     * @param radius Radius
     */
    void draw(float radius=0.05);
    /**
     * Draw arm.
     */
};


#endif //LEAP_TUXLEAPARM_H
