//
// Created by Zohar Azar on 2019-01-25.
//

#ifndef TUX_LEAPFINGER_H
#define TUX_LEAPFINGER_H


#include "LeapConfig.h"
#include "Leap.h"
#include <string>
#include "TuxLeapBone.h"
#include <map>

using namespace Leap;

class TuxLeapFinger : Finger {
private:
    Finger finger;
    std::map<Bone::Type , TuxLeapBone*> bones;
public:

    TuxLeapFinger(Finger f);

    Finger::Type getType();

    /**
 * Get the name of fingertype (0-4, 0=thumb, 1=index, 2=middle, 3=ring, 4=pinky).
 *
 * @return Name of finger
 */
    std::string getTypeName();

    /**
 * The finger tip position in millimeters.
 *
 * @return Position
 */
    Vector getPositionOfJointTip();

    /**
     * The mcp joint position in millimeters.
     *
     * @return Position
     */
    Vector getPositionOfJointMcp();

    /**
     * The pip joint position in millimeters.
     *
     * @return Position
     */
    Vector getPositionOfJointPip();

    /**
     * The dip joint position in millimeters.
     *
     * @return Position
     */
    Vector getPositionOfJointDip();

    /**
     * Raw data of the finger tip position.
     *
     * @return Raw position
     */
    Vector getRawPositionOfJointTip();

    /**
     * Raw data of the mcp joint position.
     *
     * @return Raw position
     */
    Vector getRawPositionOfJointMcp();

    /**
     * Raw data of the pip joint position.
     *
     * @return Raw position
     */
    Vector getRawPositionOfJointPip();

    /**
     * Raw data of the dip joint position.
     *
     * @return Raw position
     */
    Vector getRawPositionOfJointDip();

    void drawJoints(float radius);

    /**
   * Draw the type of the finger.
   *
   * @param xShift Shift in x axis
   * @param yShift Shift in y axis
   * @param zShift Shift in z axis
   */
    void drawName(float xShift, float yShift, float zShift);

    /**
   * Draw the type of the finger.
   */
    void drawName();

    /**
   * Draw all joints and bones of a finger.
   *
   * @param radius Radius
   */
    void draw(float radius = 0.05);

    /**
     * Draw all joints and bones of a finger.
     */

    void drawBones();


Leap::Vector getPosition();

    TuxLeapBone getBone(Bone::Type type);

};


#endif //TUX_LEAPFINGER_H
