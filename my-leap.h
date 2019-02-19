//
// Created by Zohar Azar on 2019-01-13.
//

#ifndef LEAP_MY_LEAP_H
#define LEAP_MY_LEAP_H

#define SHOW_DEBUG false

#include <iostream>
#include <cstring>
#include <sstream>
#include <vector>
#include <OpenGL/OpenGL.h>
#include "LeapConfig.h"
#include "Leap.h"

using namespace Leap;
std::mutex read_mutex;

std::vector<float> fingersBonesTriangles;
std::vector<float> fingersBonesTrianglesColors;

class SampleListener : public Listener {
public:
    virtual void onInit(const Controller&);
    virtual void onConnect(const Controller&);
    virtual void onDisconnect(const Controller&);
    virtual void onExit(const Controller&);
    virtual void onFrame(const Controller&);
    virtual void onFocusGained(const Controller&);
    virtual void onFocusLost(const Controller&);
    virtual void onDeviceChange(const Controller&);
    virtual void onServiceConnect(const Controller&);
    virtual void onServiceDisconnect(const Controller&);

private:
};

const std::string fingerNames[] = {"Thumb", "Index", "Middle", "Ring", "Pinky"};
const std::string boneNames[] = {"Metacarpal", "Proximal", "Middle", "Distal"};
const std::string stateNames[] = {"STATE_INVALID", "STATE_START", "STATE_UPDATE", "STATE_END"};
std::vector<GLfloat> fingerBonesTriangles;
std::vector<GLfloat> fingerBonesTrianglesColors;
bool isFingerBonesRendered = false;
bool isFingerBonesComputed = false;

void SampleListener::onInit(const Controller& controller) {
    std::cout << "Initialized" << std::endl;
}

void SampleListener::onConnect(const Controller& controller) {
    std::cout << "Connected" << std::endl;
    controller.enableGesture(Gesture::TYPE_CIRCLE);
    controller.enableGesture(Gesture::TYPE_KEY_TAP);
    controller.enableGesture(Gesture::TYPE_SCREEN_TAP);
    controller.enableGesture(Gesture::TYPE_SWIPE);
}

void SampleListener::onDisconnect(const Controller& controller) {
    // Note: not dispatched when running in a debugger.
    std::cout << "Disconnected" << std::endl;
}

void SampleListener::onExit(const Controller& controller) {
    std::cout << "Exited" << std::endl;
}

void SampleListener::onFrame(const Controller& controller) {
    // Get the most recent frame and report some basic information
    if (!isFingerBonesComputed) {
        fingersBonesTriangles.clear();
        fingersBonesTrianglesColors.clear();
        const Frame frame = controller.frame();
        if (SHOW_DEBUG) {
            std::cout << "Frame id: " << frame.id()
                      << ", timestamp: " << frame.timestamp()
                      << ", hands: " << frame.hands().count()
                      << ", extended fingers: " << frame.fingers().extended().count()
                      << ", tools: " << frame.tools().count()
                      << ", gestures: " << frame.gestures().count() << std::endl;
        }

        HandList hands = frame.hands();

        for (HandList::const_iterator hl = hands.begin(); hl != hands.end(); ++hl) {

            // Get the first hand
            const Hand hand = *hl;
            std::string handType = hand.isLeft() ? "Left hand" : "Right hand";
            if (SHOW_DEBUG) {
                std::cout << std::string(2, ' ') << handType << ", id: " << hand.id()
                          << ", palm position: " << hand.palmPosition() << std::endl;
            }


            if (SHOW_DEBUG) {
                // Get the hand's normal vector and direction
                const Vector normal = hand.palmNormal();
                const Vector direction = hand.direction();

                // Calculate the hand's pitch, roll, and yaw angles
                std::cout << std::string(2, ' ') << "pitch: " << direction.pitch() * RAD_TO_DEG << " degrees, "
                          << "roll: " << normal.roll() * RAD_TO_DEG << " degrees, "
                          << "yaw: " << direction.yaw() * RAD_TO_DEG << " degrees" << std::endl;
            }

            // Get the Arm bone
            if (SHOW_DEBUG) {
                Arm arm = hand.arm();
                std::cout << std::string(2, ' ') << "Arm direction: " << arm.direction()
                          << " wrist position: " << arm.wristPosition()
                          << " elbow position: " << arm.elbowPosition() << std::endl;
            }

            // Get fingers
            const FingerList fingers = hand.fingers();
            for (FingerList::const_iterator fl = fingers.begin(); fl != fingers.end(); ++fl) {
                const Finger finger = *fl;
                if (SHOW_DEBUG) {
                    std::cout << std::string(4, ' ') << fingerNames[finger.type()]
                              << " finger, id: " << finger.id()
                              << ", length: " << finger.length()
                              << "mm, width: " << finger.width() << std::endl;
                }

                // Get finger bones
                /*if (finger.type() == 1) { // index finger
                    std::ostringstream fingerStr;
                    fingerStr << "normalize: " << finger.direction().x << " " << finger.direction().y << " " << finger.direction().z;
                    std::cout << fingerStr.str() << "\n";
                    fingerStr.clear();
                }*/
//            if (finger.type() == 0) {

                for (int b = 0; b <5; b++) {
                    Bone::Type boneType = static_cast<Bone::Type>(b);
                    Bone bone = finger.bone(boneType);

                    Vector usedBasic = bone.basis().zBasis;


                    if (finger.type() != 1) {
                        fingersBonesTrianglesColors.push_back(1.0f);
                        fingersBonesTrianglesColors.push_back(1.0f);
                        fingersBonesTrianglesColors.push_back(1.0f);
                        if (b==2) {
                            printf("bone: %d x: %f y: %f z: %f\n", b, usedBasic.x, usedBasic.y, usedBasic.z);
                        }

                    } else {
                        fingersBonesTrianglesColors.push_back(0.0f);
                        fingersBonesTrianglesColors.push_back(1.0f);
                        fingersBonesTrianglesColors.push_back(0.0f);

                    }
                    fingersBonesTrianglesColors.push_back(1.0f);
                    fingersBonesTriangles.push_back(usedBasic.x);
                    fingersBonesTriangles.push_back(usedBasic.y);
                    fingersBonesTriangles.push_back(usedBasic.z);


                }
            }
            /*if (hand.isRight()) {
                printf("%.2f %.2f %.2f %.2f %.2f", fingerY[0], fingerY[1], fingerY[2], fingerY[3], fingerY[4]);
            } else {
                printf("%.2f %.2f %.2f %.2f %.2f", fingerY[4], fingerY[3], fingerY[2], fingerY[1], fingerY[0]);
            }*/
            //printf("\n");

        }
        isFingerBonesComputed = true;
        isFingerBonesRendered = false;


        // Get tools
        const ToolList tools = frame.tools();
        for (ToolList::const_iterator tl = tools.begin(); tl != tools.end(); ++tl) {
            const Tool tool = *tl;
            std::cout << std::string(2, ' ') << "Tool, id: " << tool.id()
                      << ", position: " << tool.tipPosition()
                      << ", direction: " << tool.direction() << std::endl;
        }

        // Get gestures
        const GestureList gestures = frame.gestures();
        for (int g = 0; g < gestures.count(); ++g) {
            Gesture gesture = gestures[g];

            switch (gesture.type()) {
                case Gesture::TYPE_CIRCLE: {
                    CircleGesture circle = gesture;
                    std::string clockwiseness;

                    if (circle.pointable().direction().angleTo(circle.normal()) <= PI / 2) {
                        clockwiseness = "clockwise";
                    } else {
                        clockwiseness = "counterclockwise";
                    }

                    // Calculate angle swept since last frame
                    float sweptAngle = 0;
                    if (circle.state() != Gesture::STATE_START) {
                        CircleGesture previousUpdate = CircleGesture(controller.frame(1).gesture(circle.id()));
                        sweptAngle = (circle.progress() - previousUpdate.progress()) * 2 * PI;
                    }
                    std::cout << std::string(2, ' ')
                              << "Circle id: " << gesture.id()
                              << ", state: " << stateNames[gesture.state()]
                              << ", progress: " << circle.progress()
                              << ", radius: " << circle.radius()
                              << ", angle " << sweptAngle * RAD_TO_DEG
                              << ", " << clockwiseness << std::endl;
                    break;
                }
                case Gesture::TYPE_SWIPE: {
                    SwipeGesture swipe = gesture;
                    std::cout << std::string(2, ' ')
                              << "Swipe id: " << gesture.id()
                              << ", state: " << stateNames[gesture.state()]
                              << ", direction: " << swipe.direction()
                              << ", speed: " << swipe.speed() << std::endl;
                    break;
                }
                case Gesture::TYPE_KEY_TAP: {
                    KeyTapGesture tap = gesture;
                    std::cout << std::string(2, ' ')
                              << "Key Tap id: " << gesture.id()
                              << ", state: " << stateNames[gesture.state()]
                              << ", position: " << tap.position()
                              << ", direction: " << tap.direction() << std::endl;
                    break;
                }
                case Gesture::TYPE_SCREEN_TAP: {
                    ScreenTapGesture screentap = gesture;
                    std::cout << std::string(2, ' ')
                              << "Screen Tap id: " << gesture.id()
                              << ", state: " << stateNames[gesture.state()]
                              << ", position: " << screentap.position()
                              << ", direction: " << screentap.direction() << std::endl;
                    break;
                }
                default:
                    std::cout << std::string(2, ' ') << "Unknown gesture type." << std::endl;
                    break;
            }
        }

        if (!frame.hands().isEmpty() || !gestures.isEmpty()) {
            //std::cout << std::endl;
        }
    }
}

void SampleListener::onFocusGained(const Controller& controller) {
    std::cout << "Focus Gained" << std::endl;
}

void SampleListener::onFocusLost(const Controller& controller) {
    std::cout << "Focus Lost" << std::endl;
}

void SampleListener::onDeviceChange(const Controller& controller) {
    std::cout << "Device Changed" << std::endl;
    const DeviceList devices = controller.devices();

    for (int i = 0; i < devices.count(); ++i) {
        std::cout << "id: " << devices[i].toString() << std::endl;
        std::cout << "  isStreaming: " << (devices[i].isStreaming() ? "true" : "false") << std::endl;
    }
}

void SampleListener::onServiceConnect(const Controller& controller) {
    std::cout << "Service Connected" << std::endl;
}

void SampleListener::onServiceDisconnect(const Controller& controller) {
    std::cout << "Service Disconnected" << std::endl;
}

#endif //LEAP_MY_LEAP_H
