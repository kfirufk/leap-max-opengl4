//
// Created by Zohar Azar on 2019-01-26.
//

#ifndef LEAP_TUXLEAPBONE_H
#define LEAP_TUXLEAPBONE_H

#include "LeapConfig.h"
#include "Leap.h"

class TuxLeapBone : Leap::Bone {
private:
    Leap::Bone bone;
public:
    TuxLeapBone(Leap::Bone b);
    void draw();
    Leap::Vector nextJoint();
    Leap::Vector prevJoint();
};


#endif //LEAP_TUXLEAPBONE_H
