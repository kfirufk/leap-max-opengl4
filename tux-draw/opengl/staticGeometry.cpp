#include "staticGeometry.h"

namespace static_geometry
{
	glm::vec3 jointsPolygonVertices[5];
	glm::vec3 jointsPolygonColor[5] = {COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE,
									COLOR_PURPLE, COLOR_PURPLE};

	glm::vec3 armLines[2];
	glm::vec3 armLinesColor[2]={COLOR_WHITE,COLOR_WHITE};
	glm::vec3 armSpheres[2];
	glm::vec3 armSpheresColor[2]={COLOR_LIGHT_RED,COLOR_LIGHT_RED};

	glm::vec3 fingerThumbBonesLines[6]; // leapC 0 index - thumb
	glm::vec3 fingerThumbBonesLinesColor[6] = {COLOR_BLUE, COLOR_BLUE, COLOR_BLUE,
											   COLOR_BLUE, COLOR_BLUE, COLOR_BLUE };
	glm::vec3 fingerThumbJointSphere[3]; // leapC 0 index - thumb
	glm::vec3 fingerThumbJointSphereColor[3]= {COLOR_GREEN, COLOR_GREEN, COLOR_GREEN}; // leapC 0 index - thumb
	glm::vec3 fingerIndexBonesLines[8]; // leapC 1 index - index
	glm::vec3 fingerIndexBonesLinesColor[8] = {COLOR_BLUE, COLOR_BLUE, COLOR_BLUE,
											   COLOR_BLUE, COLOR_BLUE, COLOR_BLUE, COLOR_BLUE, COLOR_BLUE};
	glm::vec3 fingerIndexJointSphere[4]; // leapC 1 index - index
	glm::vec3 fingerIndexJointSphereColor[4] = {COLOR_GREEN, COLOR_GREEN, COLOR_GREEN, COLOR_GREEN};
	glm::vec3 fingerMiddleBonesLines[8]; // leapC 2 index - middle
	glm::vec3 fingerMiddleBonesLinesColor[8] = {COLOR_BLUE, COLOR_BLUE, COLOR_BLUE,
												COLOR_BLUE, COLOR_BLUE, COLOR_BLUE, COLOR_BLUE, COLOR_BLUE};
	glm::vec3 fingerMiddleJointSphere[4]; // leapC 2 index - middle
	glm::vec3 fingerMiddleJointSphereColor[4] {COLOR_GREEN, COLOR_GREEN, COLOR_GREEN, COLOR_GREEN};
	glm::vec3 fingerRingBonesLines[8]; // leapC 3 index - ring
	glm::vec3 fingerRingBonesLinesColor[8] = {COLOR_BLUE, COLOR_BLUE, COLOR_BLUE,
											  COLOR_BLUE, COLOR_BLUE, COLOR_BLUE, COLOR_BLUE, COLOR_BLUE};
	glm::vec3 fingerRingJointSphere[4]; // leapC 3 index - ring
	glm::vec3 fingerRingJointSphereColor[4] = {COLOR_GREEN, COLOR_GREEN, COLOR_GREEN, COLOR_GREEN};
	glm::vec3 fingerPinkyBonesLines[8]; // leapC 4 index - pinky
	glm::vec3 fingerPinkyBonesLinesColor[8] = {COLOR_BLUE, COLOR_BLUE, COLOR_BLUE,
											   COLOR_BLUE, COLOR_BLUE, COLOR_BLUE, COLOR_BLUE, COLOR_BLUE};
	glm::vec3 fingerPinkyJointSphere[4]; // leapC 4 index - pinky
	glm::vec3 fingerPinkyJointSphereColor[4] = {COLOR_GREEN, COLOR_GREEN, COLOR_GREEN, COLOR_GREEN};



	void addFingerJointData(Leap::Finger::Type fType,  glm::vec3 vec1, glm::vec3 vec2, glm::vec3 vec3, glm::vec3 vec4) {
		switch (fType) {
			case 0: // thumb
				fingerThumbJointSphere[0]=vec1;
				fingerThumbJointSphere[1]=vec2;
				fingerThumbJointSphere[2]=vec3;
				break;
			case 1: // index
				fingerIndexJointSphere[0]=vec1;
				fingerIndexJointSphere[1]=vec2;
				fingerIndexJointSphere[2]=vec3;
				fingerIndexJointSphere[3]=vec4;
				break;
			case 2: // middle
				fingerMiddleJointSphere[0]=vec1;
				fingerMiddleJointSphere[1]=vec2;
				fingerMiddleJointSphere[2]=vec3;
				fingerMiddleJointSphere[3]=vec4;
				break;
			case 3: // ring
				fingerRingJointSphere[0]=vec1;
				fingerRingJointSphere[1]=vec2;
				fingerRingJointSphere[2]=vec3;
				fingerRingJointSphere[3]=vec4;
				break;
			case 4: // pinky
				fingerPinkyJointSphere[0]=vec1;
				fingerPinkyJointSphere[1]=vec2;
				fingerPinkyJointSphere[2]=vec3;
				fingerPinkyJointSphere[3]=vec4;
				break;
		}
	}


	void addFingerBoneData(Leap::Finger::Type fType, Leap::Bone::Type bType, glm::vec3 vec1, glm::vec3 vec2) {
		switch (fType) {
			case 0: // thumb
				fingerThumbBonesLines[bType*2]=vec1;
				fingerThumbBonesLines[bType*2+1]=vec2;
				break;
			case 1: // index
				fingerIndexBonesLines[bType*2]=vec1;
				fingerIndexBonesLines[bType*2+1]=vec2;
				break;
			case 2: // middle
				fingerMiddleBonesLines[bType*2]=vec1;
				fingerMiddleBonesLines[bType*2+1]=vec2;
				break;
			case 3: // ring
				fingerRingBonesLines[bType*2]=vec1;
				fingerRingBonesLines[bType*2+1]=vec2;
				break;
			case 4: // pinky
				fingerPinkyBonesLines[bType*2]=vec1;
				fingerPinkyBonesLines[bType*2+1]=vec2;
				break;
		}
	}
	
}
