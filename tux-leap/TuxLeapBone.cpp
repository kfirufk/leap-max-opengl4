//
// Created by Zohar Azar on 2019-01-26.
//

#include "TuxLeapBone.h"


TuxLeapBone::TuxLeapBone(Leap::Bone b) {
    bone=b;
}


Leap::Vector TuxLeapBone::nextJoint() {
    return bone.nextJoint();
}

Leap::Vector TuxLeapBone::prevJoint() {
    return bone.prevJoint();
}


