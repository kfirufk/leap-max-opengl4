//
// Created by Zohar Azar on 2019-01-25.
//

#ifndef TUX_LEAPHAND_H
#define TUX_LEAPHAND_H

#include "LeapConfig.h"
#include "Leap.h"
#include <cstdio>
#include <map>
#include "TuxLeapFinger.h"
#include "TuxLeapArm.h"

class TuxLeapHand : Leap::Hand{
private:
    std::map<Finger::Type , TuxLeapFinger*> fingers;
    std::vector<TuxLeapFinger*> fingersVector;
    Leap::Hand hand;
    TuxLeapArm *arm;
    std::vector<TuxLeapFinger*> outstretchedFingers;
    bool hasFingers();
public:
/**
     * Get a specific finger by id.
     *
     * @param type 0:TYPE_THUMB, 1:TYPE_INDEX, 2:TYPE_MIDDLE, 3:TYPE_RING, 4:TYPE_PINKY
     * @return Single finger or null
     */
    explicit TuxLeapHand(Leap::Hand);

    /**
  * Get the thumb finger.
  *
  * @return Single finger or null
  */
    TuxLeapFinger getThumb();

    /**
     * Get the index finger.
     *
     * @return Single finger or null
     */
    TuxLeapFinger getIndexFinger();

    /**
     * Get the middle finger.
     *
     * @return Single finger or null
     */
    TuxLeapFinger getMiddleFinger();

    /**
     * Get the ring finger.
     *
     * @return Single finger or null
     */
    TuxLeapFinger getRingFinger();

    /**
     * Get the pinky/little finger.
     *
     * @return Single finger or null
     */
    TuxLeapFinger getPinkyFinger();


    TuxLeapFinger getFinger(Finger::Type type);

    std::vector<TuxLeapFinger*>  getFingers();

    bool isLeft();

    /**
        * Get the unique ID.
        *
        * @return ID
        */
    int32_t getId();


    bool hasArm();

    int countFingers();

/**
     * How confident we are with a given hand pose. The confidence level ranges between 0.0 and 1.0 inclusive.
     *
     * @return Confidence level ranges between 0.0 and 1.0
     */
    float getConfidence();

    /**
 * The duration of time this Hand has been visible to the Leap Motion Controller.
 *
 * @return Duration
 */
    float getTimeVisible();


    TuxLeapArm getArm();

    /**
    * The center position of the palm in millimeters.
    *
    * @return Position
    */
    Leap::Vector getPosition();

    /**
    * The strength of a grab hand pose. The strength is zero for an open hand, and blends to 1.0 when a grabbing hand pose is recognized.
    *
    * @return A float value in the [0..1] range representing the holding strength of the pose.
    */
float getGrabStrength();

    /**
     * The holding strength of a pinch hand pose. The strength is zero for an open hand, and blends to 1.0 when a pinching hand pose is recognized. Pinching can be done between the thumb and any other finger of the same hand.
     *
     * @return A float value in the [0..1] range representing the holding strength of the pinch pose.
     */
float getPinchStrength();

    /**
 * Draw the hand with all details.
 *
 * @param radius The radius of the ellipse (2D) or sphere (3D).
 */
    void draw(float radius=0.05);

    std::vector<TuxLeapFinger*> getOutstretchedFingers();

};


#endif //TUX_LEAPHAND_H
