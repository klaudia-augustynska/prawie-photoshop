#include "colorslider.h"

colorSlider::colorSlider(QWidget *parent, int w, int h, char mode) :
    QWidget(parent),
    mode(mode),
    w(w),
    h(h)
{
    margines = 6;
    this->setFixedSize(w,h);
    o = new Obraz(w,h);
    this->w = w-2*margines;
    ratio = 255.0 / this->w;
    zrobLadnyMargines();
    wypelnij();
}
void colorSlider::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    if (o != NULL) {
        QImage im(o->dane, o->w, o->h, QImage::Format_ARGB32);
        p.drawImage(0, 0, im);
    }
}

void colorSlider::zrobLadnyMargines()
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

void colorSlider::wypelnij()
{
    QColor c;
    c.setRed(Kolory::nowy->red());
    c.setGreen(Kolory::nowy->green());
    c.setBlue(Kolory::nowy->blue());
    c.setAlpha(255);

    switch (mode) {
        case 'R':
            for (int x = 0; x < w; ++x) {
                c.setRed(ratio*x);
                for (int y = margines; y < height()-margines; ++y)
                    o->rysujPiksel2(x+margines,y,c);
            }
        break;
        case 'G':
            for (int x = 0; x < w; ++x) {
                c.setGreen(ratio*x);
                for (int y = margines; y < height()-margines; ++y)
                    o->rysujPiksel2(x+margines,y,c);
            }
        break;
        case 'B':
            for (int x = 0; x < w; ++x) {
                c.setBlue(ratio*x);
                for (int y = margines; y < height()-margines; ++y)
                    o->rysujPiksel2(x+margines,y,c);
            }
        break;
        case 'H':
            Kolory::hsl();
            for (int x = 0; x < w; ++x) {
                QColor cc(Kolory::rgb(x*360.0/w,Kolory::nowyS,Kolory::nowyV));
                for (int y = margines; y < height()-margines; ++y)
                    o->rysujPiksel2(x+margines,y,cc);
            }
        break;
        case 'S':
            Kolory::hsl();
            for (int x = 0; x < w; ++x) {
                QColor cc(Kolory::rgb(Kolory::nowyH,x*100.0/w,Kolory::nowyV));
                for (int y = margines; y < height()-margines; ++y)
                    o->rysujPiksel2(x+margines,y,cc);
            }
        break;
        case 'V':
            Kolory::hsl();
            for (int x = 0; x < w; ++x) {
                QColor cc(Kolory::rgb(Kolory::nowyH,Kolory::nowyS,x*100.0/w));
                for (int y = margines; y < height()-margines; ++y)
                    o->rysujPiksel2(x+margines,y,cc);
            }
        break;
    }

    zrobLadnyMargines();
    pokazBiezacy();
}

void colorSlider::pokazBiezacy()
{
    int biez;
    switch (mode) {
        case 'R':
            biez = Kolory::nowy->red() * w / 255 + margines;
        break;
        case 'G':
            biez = Kolory::nowy->green() * w / 255 + margines;
        break;
        case 'B':
            biez = Kolory::nowy->blue() * w / 255 + margines;
        break;
        case 'H':
            biez = Kolory::nowyH * w / 360 + margines;
        break;        
        case 'S':
            biez = Kolory::nowyS * w / 100 + margines;
        break;
        case 'V':
            biez = Kolory::nowyV * w / 100 + margines;
        break;
    }
    int m = margines/2;

    for (int y = 0; y <= margines; ++y) {
        for (int x = biez-m; x <= biez+m; ++x)
            o->rysujPiksel2(x,y,Qt::black);
        m -= 1;
    }

    m = margines/2;
    for (int y = height()-1; y >= height()-margines; --y) {
        for (int x = biez-m; x <= biez+m; ++x)
            o->rysujPiksel2(x,y,Qt::black);
        m -= 1;
    }
}

void colorSlider::reagujNaMyszke(QMouseEvent *e)
{
    QColor c;
    switch (mode) {
        case 'R':
            if (e->x() < margines)
                Kolory::nowy->setRed(0);
            else if (e->x() < margines+w)
                Kolory::nowy->setRed((e->x()-margines) * ratio);
            else
                Kolory::nowy->setRed(255);
        break;
        case 'G':
            if (e->x() < margines)
                Kolory::nowy->setGreen(0);
            else if (e->x() < margines+w)
                Kolory::nowy->setGreen((e->x()-margines) * ratio);
            else
                Kolory::nowy->setGreen(255);
        break;
        case 'B':
            if (e->x() < margines)
                Kolory::nowy->setBlue(0);
            else if (e->x() < margines+w)
                Kolory::nowy->setBlue((e->x()-margines) * ratio);
            else
                Kolory::nowy->setBlue(255);
        break;
        case 'H':
            if (e->x() < margines)
                Kolory::nowyH = 0;
            else if (e->x() < margines+w)
                Kolory::nowyH = ((e->x()-margines) * 360.0/w);
            else
                Kolory::nowyH = 360;
            c = (Kolory::rgb(Kolory::nowyH,Kolory::nowyS,Kolory::nowyV));
            Kolory::nowy->setRed(c.red());
            Kolory::nowy->setGreen(c.green());
            Kolory::nowy->setBlue(c.blue());
        break;
        case 'S':
            if (e->x() < margines)
                Kolory::nowyS = 0;
            else if (e->x() < margines+w)
                Kolory::nowyS = ((e->x()-margines) * 100.0/w);
            else
                Kolory::nowyS = 100;
            c = Kolory::rgb(Kolory::nowyH,Kolory::nowyS,Kolory::nowyV);
            Kolory::nowy->setRed(c.red());
            Kolory::nowy->setGreen(c.green());
            Kolory::nowy->setBlue(c.blue());
        break;
        case 'V':
            if (e->x() < margines)
                Kolory::nowyV = 0;
            else if (e->x() < margines+w)
                Kolory::nowyV = ((e->x()-margines) * 100.0/w);
            else
                Kolory::nowyV = 100;
            c = Kolory::rgb(Kolory::nowyH,Kolory::nowyS,Kolory::nowyV);
            Kolory::nowy->setRed(c.red());
            Kolory::nowy->setGreen(c.green());
            Kolory::nowy->setBlue(c.blue());
        break;

    }

    emit SIGzmianaKoloru();
    zrobLadnyMargines();
    pokazBiezacy();
}

void colorSlider::mousePressEvent(QMouseEvent *e)
{
    setFocus();
    reagujNaMyszke(e);
    update();
}

void colorSlider::mouseMoveEvent(QMouseEvent *e)
{
    reagujNaMyszke(e);
    update();
}

void colorSlider::mouseReleaseEvent(QMouseEvent *e) {
}
