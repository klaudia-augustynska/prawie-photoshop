#ifndef PUNKT_H
#define PUNKT_H

#include "math.h"
#include <QString>

class Punkt
{
public:
    Punkt();
    Punkt(float x, float y);
    Punkt(const Punkt&);
    Punkt operator * (float);
    Punkt operator + (Punkt);
    Punkt& operator = (const Punkt&);
    Punkt& operator *= (const float&);
    Punkt& operator += (const Punkt&);
    void swap(Punkt *);
    void swapX(Punkt *);
    void swapY(Punkt *);
    void round();
    bool naOdcinku(Punkt, Punkt);
    QString GetPunkt();
    float x;
    float y;
};

#endif // PUNKT_H
