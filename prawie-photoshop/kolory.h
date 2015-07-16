#ifndef KOLORY_H
#define KOLORY_H

#include <QColor>
#include <QDebug>
#include "math.h"

class Kolory
{
public:
    Kolory();
    static QColor *bg;
    static QColor *fg;
    static QColor *nowy;
    static char mode;
    static int nowyH;
    static int nowyS;
    static int nowyV;
    static void hsl();
    static QColor rgb(float h, float s, float v);
private:
    static void rgbToHsvNormalneProporcje(float h, float s, float v);
    static QColor HsvToRgbNormalneProporcje(float r, float g, float b);
};

#endif // KOLORY_H
