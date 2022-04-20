#pragma once
#include "Utils/Text/String.h"


class Zone
{
public:
    int x;
    int y;
    int width;
    int height;

    Zone(int _x, int _y, int _w, int _h) : x(_x), y(_y), width(_w), height(_h) { }

    virtual ~Zone() {}

    virtual void Draw() = 0;

protected:

    void Clear();

    void Send();
};


class ZoneFPS : public Zone
{
public:

    String<> sring;

    ZoneFPS() : Zone(125, 25, 30, 7) { }

    virtual void Draw();
};
