#ifndef TOOL_H
#define TOOL_H

#include <QMouseEvent>
#include "obraz.h"
#include "math.h"
#include "punkt.h"
#include "kolory.h"
#include "layer.h"
#include <QDebug>

class Tool
{
public:
    Tool();
    virtual void press(QMouseEvent *);
    virtual void move(QMouseEvent *);
    virtual void release(QMouseEvent *);
    virtual void sprzatnij();
    inline void rysujPiksel(int x, int y)
    {
        if (x < 0 || y < 0 || x >= obraz->w || y >= obraz->h)
            return;
        int adr = 4*(y*obraz->w + x);
        obraz->dane[adr]   = Kolory::fg->blue();
        obraz->dane[adr+1] = Kolory::fg->green();
        obraz->dane[adr+2] = Kolory::fg->red();
        obraz->dane[adr+3] = Kolory::fg->alpha();
    }
    inline void rysujPiksel(int x, int y, QColor c)
    {
        if (x < 0 || y < 0 || x >= obraz->w || y >= obraz->h)
            return;
        int adr = 4*(y*obraz->w + x);
        obraz->dane[adr]   = c.blue();
        obraz->dane[adr+1] = c.green();
        obraz->dane[adr+2] = c.red();
        obraz->dane[adr+3] = c.alpha();
    }
    inline void rysujPiksel2(int x, int y)
    {
        int adr = 4*(y*obraz->w + x);
        obraz->dane[adr]   = Kolory::fg->blue();
        obraz->dane[adr+1] = Kolory::fg->green();
        obraz->dane[adr+2] = Kolory::fg->red();
        obraz->dane[adr+3] = Kolory::fg->alpha();
    }
    inline void setColor(Punkt P)
    {
        int adr = 4*(P.y*obraz->w + P.x);
        obraz->dane[adr]   = Kolory::fg->blue();
        obraz->dane[adr+1] = Kolory::fg->green();
        obraz->dane[adr+2] = Kolory::fg->red();
        obraz->dane[adr+3] = Kolory::fg->alpha();
    }
    inline void setColor(int x, int y)
    {
        int adr = 4*(y*obraz->w + x);
        obraz->dane[adr]   = Kolory::fg->blue();
        obraz->dane[adr+1] = Kolory::fg->green();
        obraz->dane[adr+2] = Kolory::fg->red();
        obraz->dane[adr+3] = Kolory::fg->alpha();
    }
    inline void przywroc() {
        int pole = 4* obraz->w*obraz->h;
        for (int i = 0; i < pole; i +=4) {
            obraz->dane[i]    = Kolory::bg->blue();
            obraz->dane[i+1]  = Kolory::bg->green();
            obraz->dane[i+2]  = Kolory::bg->red();
            obraz->dane[i+3]  = Kolory::bg->alpha();
        }
    }
    inline void czysc() {
        int pole = 4* obraz->w*obraz->h;
        for (int i = 0; i < pole; i +=4) {
            obraz->dane[i]    = 0;
            obraz->dane[i+1]  = 0;
            obraz->dane[i+2]  = 0;
            obraz->dane[i+3]  = 0;
        }
    }
    static void setCurrentLayer(layer *);
    QColor getColor(Punkt);
    QColor getColor(int x, int y);
    static Obraz *bufor;
    static Obraz *obraz;
    static layer *currentLayer;
    static QWidget *ekran;
    int xpocz;
    int ypocz;
};

#endif // TOOL_H
