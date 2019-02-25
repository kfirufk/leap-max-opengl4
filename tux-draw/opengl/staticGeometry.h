#pragma once

#include <glm/glm.hpp>
#include "Leap.h"

#define COLOR_BLUE glm::vec3(0.090, 0.360, 0.709)
#define COLOR_GREEN glm::vec3(0.109, 0.831, 0.431)
#define COLOR_PURPLE glm::vec3(0.819, 0.525, 0.933)
#define COLOR_LIGHT_RED glm::vec3(0.921, 0.278, 0.360)
#define COLOR_WHITE glm::vec3(1,1,1)
namespace static_geometry
{
    extern glm::vec3 jointsPolygonVertices[5];
    extern glm::vec3 jointsPolygonColor[5];

    extern glm::vec3 armLines[2];
    extern glm::vec3 armLinesColor[2];
    extern glm::vec3 armSpheres[2];
    extern glm::vec3 armSpheresColor[2];

    extern glm::vec3 fingerThumbBonesLines[6]; // leapC 0 index - thumb
    extern glm::vec3 fingerThumbBonesLinesColor[6];
    extern glm::vec3 fingerThumbJointSphere[3]; // leapC 0 index - thumb
    extern glm::vec3 fingerThumbJointSphereColor[3];
    extern glm::vec3 fingerIndexBonesLines[8]; // leapC 1 index - index
    extern glm::vec3 fingerIndexBonesLinesColor[8];
    extern glm::vec3 fingerIndexJointSphere[4]; // leapC 1 index - index
    extern glm::vec3 fingerIndexJointSphereColor[4];
    extern glm::vec3 fingerMiddleBonesLines[8]; // leapC 2 index - middle
    extern glm::vec3 fingerMiddleBonesLinesColor[8];
    extern glm::vec3 fingerMiddleJointSphere[4]; // leapC 2 index - middle
    extern glm::vec3 fingerMiddleJointSphereColor[4];
    extern glm::vec3 fingerRingBonesLines[8]; // leapC 3 index - ring
    extern glm::vec3 fingerRingBonesLinesColor[8];
    extern glm::vec3 fingerRingJointSphere[4]; // leapC 3 index - ring
    extern glm::vec3 fingerRingJointSphereColor[4];
    extern glm::vec3 fingerPinkyBonesLines[8]; // leapC 4 index - pinky
    extern glm::vec3 fingerPinkyBonesLinesColor[8];
    extern glm::vec3 fingerPinkyJointSphere[4]; // leapC 4 index - pinky
    extern glm::vec3 fingerPinkyJointSphereColor[4];

    extern void addFingerBoneData(Leap::Finger::Type fType, Leap::Bone::Type bType, glm::vec3 vec1,
                                  glm::vec3 vec2);
    extern void addFingerJointData(Leap::Finger::Type fType,  glm::vec3 vec1,
                                  glm::vec3 vec2, glm::vec3 vec3,
                                  glm::vec3 vec4);

}
