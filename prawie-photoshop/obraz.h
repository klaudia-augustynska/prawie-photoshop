#ifndef OBRAZ_H
#define OBRAZ_H

#include <QColor>
#include <QImage>
#include "kolory.h"

class Obraz
{
public:
    Obraz(int,int);
    Obraz(Obraz *o);
    void wklejObraz(Obraz *);
    void wklejObraz(QImage *);
    inline void rysujPiksel(int x, int y, QColor c)
    {
        if (x < 0 || y < 0 || x >= w || y >= h)
            return;
        int adr = 4*(y*w + x);
        dane[adr]   = c.blue();
        dane[adr+1] = c.green();
        dane[adr+2] = c.red();
        dane[adr+3] = c.alpha();
    }
    inline void rysujPiksel2(int x, int y, QColor c)
    {
        int adr = 4*(y*w + x);
        dane[adr]   = c.blue();
        dane[adr+1] = c.green();
        dane[adr+2] = c.red();
        dane[adr+3] = c.alpha();
    }
    inline void zamaluj() {
        int pole = w*h;
        for (int i = 0; i < pole; ++i) {
            dane[4*i]    = Kolory::bg->blue();
            dane[4*i+1]  = Kolory::bg->green();
            dane[4*i+2]  = Kolory::bg->red();
            dane[4*i+3]  = 255;
        }
    }
    int w,h;
    unsigned char *dane;
    QColor getColor(int x, int y);
};

#endif // OBRAZ_H
