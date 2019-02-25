//
// Created by Zohar Azar on 2019-01-26.
//

#include "TuxLeapBone.h"

TuxLeapBone::TuxLeapBone(Leap::Finger f, Leap::Bone b) {
    bone=b;
    finger=f;
}


Leap::Vector TuxLeapBone::nextJoint() {
    return bone.nextJoint();
}

Leap::Vector TuxLeapBone::prevJoint() {
    return bone.prevJoint();
}


