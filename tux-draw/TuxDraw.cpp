//
// Created by Zohar Azar on 2019-02-01.
//

#include "TuxDraw.h"

TuxDraw::TuxDraw() {
    vIsDrawDataComputed=false;
    vIsDrawDataRendered=false;
}


bool TuxDraw::isDrawDataComputed() const {
    return vIsDrawDataComputed;
}

void TuxDraw::setIsDrawDataComputed(bool isDrawDataComputed) {
    isDrawDataComputed = isDrawDataComputed;
    setIsDrawDataRendered(false);
}

bool TuxDraw::isDrawDataRendered() const {
    return vIsDrawDataRendered;
}

void TuxDraw::setIsDrawDataRendered(bool isDrawDataRendered) {
    isDrawDataRendered = isDrawDataRendered;
    if (isDrawDataRendered) {
        setIsDrawDataComputed(false);
    }
}

namespace TuxDrawContainer {
    TuxDraw *tuxDraw;
    bool isDisplayReady = false;
    bool isDrawing = false;
};
