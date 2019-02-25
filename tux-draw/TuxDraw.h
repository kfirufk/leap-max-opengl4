//
// Created by Zohar Azar on 2019-01-26.
//

#ifndef LEAP_TUXDRAW_H
#define LEAP_TUXDRAW_H

#include <string>


class TuxDraw {
private:
    bool vIsDrawDataComputed;
    bool vIsDrawDataRendered;

public:

    TuxDraw();

    void display();

    bool isDrawDataComputed() const;

    void setIsDrawDataComputed(bool isDrawDataComputed);

    bool isDrawDataRendered() const;

    void setIsDrawDataRendered(bool isDrawDataRendered);

    int init();
    void draw();
    void drawText(std::string txt, float x, float y, float z);
};

namespace TuxDrawContainer {
    extern bool isDisplayReady;
    extern TuxDraw *tuxDraw;
    extern bool isDrawing;
};

#endif //LEAP_TUXDRAW_H
