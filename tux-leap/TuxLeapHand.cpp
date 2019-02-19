//
// Created by Zohar Azar on 2019-01-25.
//

#include "TuxLeapHand.h"
#include "TuxLeapFinger.h"
#include <vector>

TuxLeapHand::TuxLeapHand(Leap::Hand h) {
    hand = h;
    for (Leap::Finger finger : hand.fingers()) {
        TuxLeapFinger *f = new TuxLeapFinger(finger);
        fingers.insert(std::make_pair(finger.type(),f));
        fingersVector.push_back(f);
    }
    arm = new TuxLeapArm(hand.arm());
}

/**
* Get the thumb finger.
*
* @return Single finger or null
*/
TuxLeapFinger TuxLeapHand::getThumb() {
    return getFinger(Finger::Type::TYPE_THUMB);
}

/**
 * Get the index finger.
 *
 * @return Single finger or null
 */
TuxLeapFinger TuxLeapHand::getIndexFinger() {
    return getFinger(Finger::Type::TYPE_INDEX);
}

/**
 * Get the middle finger.
 *
 * @return Single finger or null
 */
TuxLeapFinger TuxLeapHand::getMiddleFinger() {
    return getFinger(Finger::Type::TYPE_MIDDLE);
}

/**
 * Get the ring finger.
 *
 * @return Single finger or null
 */
TuxLeapFinger TuxLeapHand::getRingFinger() {
    return getFinger(Finger::Type::TYPE_RING);
}

/**
 * Get the pinky/little finger.
 *
 * @return Single finger or null
 */
TuxLeapFinger TuxLeapHand::getPinkyFinger() {
    return getFinger(Finger::Type::TYPE_PINKY);
}


TuxLeapFinger TuxLeapHand::getFinger(Finger::Type type) {
    return *fingers[type];
}

std::vector<TuxLeapFinger*> TuxLeapHand::getFingers() {
    return fingersVector;
}

bool TuxLeapHand::isLeft() {
    return this->hand.isLeft();
}

/**
    * Get the unique ID.
    *
    * @return ID
    */
int32_t TuxLeapHand::getId() {
    return hand.id();
}


bool TuxLeapHand::hasArm() {
    return hand.arm().isValid();
}

int TuxLeapHand::countFingers() {
    return hand.fingers().count();
}

/**
     * How confident we are with a given hand pose. The confidence level ranges between 0.0 and 1.0 inclusive.
     *
     * @return Confidence level ranges between 0.0 and 1.0
     */
float TuxLeapHand::getConfidence() {
    return hand.confidence();
}

/**
* The duration of time this Hand has been visible to the Leap Motion Controller.
*
* @return Duration
*/
float TuxLeapHand::getTimeVisible() {
    return hand.timeVisible();
}


bool TuxLeapHand::hasFingers() {
    return !hand.fingers().isEmpty();
}

TuxLeapArm TuxLeapHand::getArm() {
    return *arm;
}

/**
* The center position of the palm in millimeters.
*
* @return Position
*/
Leap::Vector TuxLeapHand::getPosition() {
    return hand.stabilizedPalmPosition().normalized();
}

/**
* The strength of a grab hand pose. The strength is zero for an open hand, and blends to 1.0 when a grabbing hand pose is recognized.
*
* @return A float value in the [0..1] range representing the holding strength of the pose.
*/
float TuxLeapHand::getGrabStrength() {
    return hand.grabStrength();
}

/**
 * The holding strength of a pinch hand pose. The strength is zero for an open hand, and blends to 1.0 when a pinching hand pose is recognized. Pinching can be done between the thumb and any other finger of the same hand.
 *
 * @return A float value in the [0..1] range representing the holding strength of the pinch pose.
 */
float TuxLeapHand::getPinchStrength() {
    return hand.pinchStrength();
}

std::vector<TuxLeapFinger*> TuxLeapHand::getOutstretchedFingers() {
    outstretchedFingers.clear();
    if (!hand.fingers().extended().isEmpty()) {
        for (Finger finger : hand.fingers().extended()) {
            outstretchedFingers.push_back(new TuxLeapFinger(finger));
        }
    }
    return outstretchedFingers;
}