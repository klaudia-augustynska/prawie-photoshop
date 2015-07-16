#ifndef LAYER_H
#define LAYER_H

#include <QString>
#include <QStack>
#include "obraz.h"
#include "punkt.h"
#include "math.h"

class layer
{
public:
    layer(QString l = "");
    void setBlocked(bool);
    void setVisible(bool);
    bool visibility();
    void blend(layer *);
    void setBlendingModeId(int);
    void zrobErozje();
    void zrobDylatacje();

    static int idCounter;
    int id;
    static int w,h;
    static int pole;
    Obraz *o;
    int opacity;
    enum blendingModes {
        NORMAL,
        MULTIPLY,
        SCREEN,
        OVERLAY,
        DARKEN,
        LIGHTEN,
        DIFFERENCE,
        ADD,
        SUBSTRACT,
        AVERAGE,
        NEGATION,
        EXCLUSION,
        SOFT_LIGHT
    };

    layer::blendingModes blendingModeId;
    QString label;

private:
    bool blocked;
    bool visible;


    int Ar, Ag, Ab, Aa;
    int Br, Bg, Bb, Ba;
    double Aalpha, Balpha;
    double Aopacity, Bopacity;

    inline void blend_wypelnijZmienne(int i, layer *l)
    {
        Ar = l->o->dane[4*i];
        Ag = l->o->dane[4*i+1];
        Ab = l->o->dane[4*i+2];
        Aa = l->o->dane[4*i+3];
        Br = o->dane[4*i];
        Bg = o->dane[4*i+1];
        Bb = o->dane[4*i+2];
        Ba = o->dane[4*i+3];
        Aalpha = (double) Aa / 255.0 * Aopacity;
        Balpha = (double) Ba / 255.0 * Bopacity;
    }

    inline void blend_zapiszPiksela(int i)
    {
        Balpha = Aalpha + Balpha * (1.0 - Aalpha);
        Ba = 1.0 * Balpha * 255.0;

        if (Br > 255)
            Br = 255;
        if (Bg > 255)
            Bg = 255;
        if (Bb > 255)
            Bb = 255;
        if (Ba > 255)
            Ba = 255;

        o->dane[4*i] = Br;
        o->dane[4*i+1] = Bg;
        o->dane[4*i+2] = Bb;
        o->dane[4*i+3] = Ba;
    }

};

#endif // LAYER_H
