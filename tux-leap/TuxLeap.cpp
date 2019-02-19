//
// Created by Zohar Azar on 2019-01-26.
//

#include "TuxLeap.h"
#include "TuxLeapHand.h"
#include "../tux-draw/TuxDraw.h"

using namespace TuxLeap;

namespace TuxLeap {
    Controller controller;
    SampleListener listener;
    std::vector<TuxLeapHand *> hands;
}

void SampleListener::onInit(const Controller& controller) {
    std::cout << "Initialized Tux-Leap" << std::endl;
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
    if (!TuxDrawContainer::isDrawing) {
        // Get the most recent frame and report some basic information
        const Frame frame = controller.frame();

        HandList hands = frame.hands();
        TuxLeap::hands.clear();
        if (hands.count() > 0) {
            for (HandList::const_iterator hl = hands.begin(); hl != hands.end(); ++hl) {
                TuxLeap::hands.push_back(new TuxLeapHand(*hl));
            }
            if (TuxDrawContainer::isDisplayReady) {
                TuxDrawContainer::tuxDraw->draw();
            }
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

void TuxLeap::initLeapMotion() {
    controller.addListener(listener); // init leap
    controller.setPolicy(Leap::Controller::POLICY_BACKGROUND_FRAMES);
}

void TuxLeap::closeLeapMotion() {
    controller.removeListener(listener);
}

