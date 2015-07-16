#include "kolory.h"

Kolory::Kolory()
{
    hsl();
}

QColor* Kolory::bg = new QColor(252,247,231,255);
QColor* Kolory::fg = new QColor(249,0,105,255);
QColor* Kolory::nowy = new QColor(249,0,105,255);

char Kolory::mode = 'H';
int Kolory::nowyH = 50;
int Kolory::nowyS = 50;
int Kolory::nowyV = 50;

void Kolory::hsl()
{
    // r,g,b = [0,1]
    // h     = [0,60]
    // s,v   = [0,1]

    float r,g,b;

    r = 1.0 * nowy->red() / 255;
    g = 1.0 * nowy->green() / 255;
    b = 1.0 * nowy->blue() / 255;

    float h,s,v;

    float M,m;
    M = m = r;
    if (g > M) M = g;
    if (b > M) M = b;
    if (g < m) m = g;
    if (b < m) m = b;

    float C = M-m;

    // VALUE
    v = M;

    if (M != 0)
        s = C/M;
    else {
        s = 0;
        h = 0;
        nowyH = h;
        nowyS = s*100;
        nowyV = v*100;
        return;
    }

    if (M == r)
        h = (g-b) / C;
    else if (M == g)
        h = 2 + (b-r) / C;
    else
        h = 4 + (r-g) / C;
    h *= 60;
    if (h < 0)
        h += 360;

    nowyH = h;
    nowyS = s*100;
    nowyV = v*100;

}

QColor Kolory::rgb(float h, float s, float v)
{
    float r,g,b;

    int i;
    float f,p,q,t;

    s /= 100;
    v /= 100;

    if (s == 0) {
        r = g = b = v;
        return QColor(r*255,g*255,b*255);
    }

    h /= 60;

    i = floor(h);
    f = h - i;			// factorial part of h
    p = v * ( 1.0 - s );
    q = v * ( 1.0 - s * f );
    t = v * ( 1.0 - s * ( 1.0 - f ) );

    switch( i ) {
        case 0:
            r = v;
            g = t;
            b = p;
            break;
        case 1:
            r = q;
            g = v;
            b = p;
            break;
        case 2:
            r = p;
            g = v;
            b = t;
            break;
        case 3:
            r = p;
            g = q;
            b = v;
            break;
        case 4:
            r = t;
            g = p;
            b = v;
            break;
        default:
            r = v;
            g = p;
            b = q;
            break;
    }
    return QColor(r*255,g*255,b*255);

}

