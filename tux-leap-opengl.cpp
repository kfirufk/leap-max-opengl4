//
// Created by Zohar Azar on 2019-01-29.
//

#include "./tux-draw/TuxDraw.h"
#include "./tux-leap/TuxLeap.h"

int main() {
    TuxLeap::initLeapMotion();
    TuxDrawContainer::tuxDraw = new TuxDraw();
    TuxDrawContainer::tuxDraw->init();
    TuxLeap::closeLeapMotion();
    return 0;
}