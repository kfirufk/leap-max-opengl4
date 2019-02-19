//
// Created by Zohar Azar on 2019-01-26.
//

#ifndef LEAP_TUXLEAP_H
#define LEAP_TUXLEAP_H

#include "LeapConfig.h"
#include "Leap.h"
#include "TuxLeapHand.h"
#include <vector>

namespace TuxLeap {
    using namespace Leap;

    class SampleListener : public Listener {
    public:

        virtual void onInit(const Controller &);

        virtual void onConnect(const Controller &);

        virtual void onDisconnect(const Controller &);

        virtual void onExit(const Controller &);

        virtual void onFrame(const Controller &);

        virtual void onFocusGained(const Controller &);

        virtual void onFocusLost(const Controller &);

        virtual void onDeviceChange(const Controller &);

        virtual void onServiceConnect(const Controller &);

        virtual void onServiceDisconnect(const Controller &);

    private:
    };

    void initLeapMotion();
    void closeLeapMotion();

    const std::string fingerNames[] = {"Thumb", "Index", "Middle", "Ring", "Pinky"};
    const std::string boneNames[] = {"Metacarpal", "Proximal", "Middle", "Distal"};
    const std::string stateNames[] = {"STATE_INVALID", "STATE_START", "STATE_UPDATE", "STATE_END"};

    extern Controller controller;
    extern SampleListener listener;
    extern std::vector<TuxLeapHand *> hands;




}
#endif //LEAP_TUXLEAP_H
