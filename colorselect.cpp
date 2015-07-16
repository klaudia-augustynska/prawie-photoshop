#include "colorselect.h"

colorSelect::colorSelect(QWidget *parent, int n) :
    QWidget(parent),
    n(n)
{
    margines = 6;
    this->setFixedSize(n,n);
    o = new Obraz(n,n);
    bufor = new Obraz(n,n);
    this->n = n-(2*margines);
    ratio = 255.0 / n;
    ratio2 = 100.0/n;
    ratio3 = 360.0/n;

    wypelnij();
    pokazBiezacy();
}
void colorSelect::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    if (o != NULL) {
        QImage im(o->dane, o->w, o->h, QImage::Format_ARGB32);
        p.drawImage(0, 0, im);
    }
}
void colorSelect::zrobLadnyMargines()
{
    for (int x = 0; x < margines; ++x)
        for (int y = 0; y < height(); ++y)
            o->rysujPiksel2(x,y,QColor(0,0,0,0));
    for (int x = margines; x < width()-margines; ++x) {
        for (int y = 0; y < margines; ++y)
            o->rysujPiksel2(x,y,QColor(0,0,0,0));
        for (int y = height()-1; y >= height()-margines; --y)
            o->rysujPiksel2(x,y,QColor(0,0,0,0));
    }
    for (int x = width()-1; x >= width()-margines; --x)
        for (int y = 0; y < height(); ++y)
            o->rysujPiksel2(x,y,QColor(0,0,0,0));
}

void colorSelect::wypelnij()
{
    QColor c, cc;
    float a, b;
    c.setRed(Kolory::nowy->red());
    c.setGreen(Kolory::nowy->green());
    c.setBlue(Kolory::nowy->blue());
    c.setAlpha(255);

    switch (Kolory::mode) {
        case 'R':
            for (int x = margines; x < n+margines; ++x) {
                int q = ratio*x;
                if (q > 255) q = 255;
                c.setBlue(q);
                for (int y = margines; y < n+margines; ++y) {
                    q = ratio*y;
                    if (q > 255) q = 255;
                    c.setGreen(q);
                    o->rysujPiksel2(x,y,c);
                }
            }
        break;
        case 'G':
            for (int x = margines; x < n+margines; ++x) {
                int q = ratio*x;
                if (q > 255) q = 255;
                c.setBlue(q);
                for (int y = margines; y < n+margines; ++y) {
                    q = ratio*y;
                    if (q > 255) q = 255;
                    c.setRed(q);
                    o->rysujPiksel2(x,y,c);
                }
            }
        break;
        case 'B':
            for (int x = margines; x < n+margines; ++x) {
                int q = ratio*x;
                if (q > 255) q = 255;
                c.setRed(q);
                for (int y = margines; y < n+margines; ++y) {
                    q = ratio*y;
                    if (q > 255) q = 255;
                    c.setGreen(q);
                    o->rysujPiksel2(x,y,c);
                }
            }
        break;
        case 'H':
            Kolory::hsl();
            for (int x = 0; x < n; ++x) {
                for (int y = 0; y <= n; ++y) {
                    a = x*ratio2;
                    b = y*ratio2;
                    if (a > 100)
                        a = 100;
                    if (b > 100)
                        b = 100;
                    cc = Kolory::rgb(Kolory::nowyH,a,b);
                    o->rysujPiksel(x+margines,n+margines-y,cc);
                }
            }
        break;

        case 'S':
            Kolory::hsl();
            for (int x = 0; x < n; ++x) {
                for (int y = 0; y <= n; ++y) {
                    a = x*ratio3;
                    b = y*ratio2;
                    if (a > 360)
                        a = 360;
                    if (b > 100)
                        b = 100;
                    QColor cc(Kolory::rgb(a,Kolory::nowyS,b));
                    o->rysujPiksel(x+margines,n+margines-y,cc);
                }
            }
        break;

        case 'V':
            Kolory::hsl();
            for (int x = 0; x < n; ++x) {
                for (int y = 0; y <= n; ++y) {
                    a = x*ratio3;
                    b = y*ratio2;
                    if (a > 360)
                        a = 360;
                    if (b > 100)
                        b = 100;
                    QColor cc(Kolory::rgb(a,b,Kolory::nowyV));
                    o->rysujPiksel(x+margines,n+margines-y,cc);
                }
            }
        break;
    }

}

void colorSelect::pokazBiezacy(int biezX, int biezY)
{
    zrobLadnyMargines();

    if (biezX == -1 || biezY == -1)
    switch (Kolory::mode) {
        case 'R':
            biezX = 1.0 * Kolory::nowy->blue() * n / 255 + margines;
            biezY = 1.0 * Kolory::nowy->green() * n / 255 + margines;
        break;
        case 'G':
            biezX = 1.0 * Kolory::nowy->blue() * n / 255 + margines;
            biezY = 1.0 * Kolory::nowy->red() * n / 255 + margines;
        break;
        case 'B':
            biezX = 1.0 * Kolory::nowy->red() * n / 255 + margines;
            biezY = 1.0 * Kolory::nowy->green() * n / 255 + margines;
        break;
        case 'H':
            biezX = 1.0 * Kolory::nowyS * n / 100 + margines;
            biezY = 1.0 * (100 - Kolory::nowyV) * n / 100 + margines;
        break;
        case 'S':
            biezX = 1.0 * Kolory::nowyH * n / 360 + margines;
            biezY = 1.0 * (100 - Kolory::nowyV) * n / 100 + margines;
        break;
        case 'V':
            biezX = 1.0 * Kolory::nowyH * n / 360 + margines;
            biezY = 1.0 * (100 - Kolory::nowyS) * n / 100 + margines;
        break;
    }
    else {
        if (biezX < margines)
            biezX = margines;
        else if (biezX > margines+n)
            biezX = n+margines;
        if (biezY < margines)
            biezY = margines;
        else if (biezY > margines+n)
            biezY = n+margines;
    }

    rysujOkrag(biezX,biezY,5, 255,255,255);
    rysujOkrag(biezX,biezY,6, 0,0,0);


}

void colorSelect::rysujOkrag(int xpocz, int ypocz, int promien, int r, int g, int b)
{
    int x1 = xpocz;
    int y1 = ypocz;

 //   int promien = sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
    int promien2 = promien*promien;

    int punkt = ceil(sqrt(promien2 / 2));
    int temp;

    for (int i = -punkt; i < punkt; ++i) {
        temp = sqrt(promien2 - i*i);
        o->rysujPiksel(i+x1,  temp + y1, QColor(r,g,b));
        o->rysujPiksel(i+x1, -temp + y1, QColor(r,g,b));
        o->rysujPiksel( temp + x1, i+y1, QColor(r,g,b));
        o->rysujPiksel(-temp + x1, i+y1, QColor(r,g,b));
    }

}

void colorSelect::reagujNaMyszke(QMouseEvent *e)
{
    /*
    1_|_4_|_7
      |   |
    2 | 5 | 8
    __|___|__
    3 | 6 | 9

    */

    if (e->x() < margines) {
        if (e->y() < margines) // 1
            *(Kolory::nowy) = o->getColor(margines,margines);
        else if (e->y() < margines+n) // 2
            *(Kolory::nowy) = o->getColor(margines,e->y());
        else // 3
            *(Kolory::nowy) = o->getColor(margines,n+margines-1);
    }
    else if (e->x() < margines+n) {
        if (e->y() < margines) // 4
            *(Kolory::nowy) = o->getColor(e->x(),margines);
        else if (e->y() < margines+n) // 5
            *(Kolory::nowy) = o->getColor(e->x(),e->y());
        else // 6
            *(Kolory::nowy) = o->getColor(e->x(),n+margines-1);
    }
    else {
        if (e->y() < margines) // 7
            *(Kolory::nowy) = o->getColor(n+margines-1,margines);
        else if (e->y() < margines+n) // 8
            *(Kolory::nowy) = o->getColor(n+margines-1,e->y());
        else // 9
            *(Kolory::nowy) = o->getColor(n+margines-1,n+margines-1);
    }

    emit SIGzmianaKoloru2();
}

void colorSelect::mousePressEvent(QMouseEvent *e)
{
    setFocus();
    reagujNaMyszke(e);
    bufor->wklejObraz(o);
    update();
}

void colorSelect::mouseMoveEvent(QMouseEvent *e)
{
    o->wklejObraz(bufor);
    reagujNaMyszke(e);
    update();
}

void colorSelect::mouseReleaseEvent(QMouseEvent *e) {
}
