#include "toolelipsa.h"

ToolElipsa::ToolElipsa()
{
    szkicuj = true;
    linia = new ToolLinia();
    kat2 = 0;
}

void ToolElipsa::press(QMouseEvent *e)
{
    if (e->buttons() == Qt::LeftButton) {
        if (szkicuj == true) { // zmieniaj promienie
            P1.x = e->x();
            P1.y = e->y();
            bufor->wklejObraz(obraz);
        } else { // zmieniaj kąt
            P3.x = e->x();
            P3.y = e->y();
        }
    }
    else if (e->buttons() == Qt::RightButton) {
        szkicuj = true;
        kat2 = 0;
    }
}

void ToolElipsa::move(QMouseEvent *e)
{
    if (szkicuj == true) { // zmieniaj promienie
        if (e->x() < 0 || e->y() < 0 || e->x() >= obraz->w || e->y() >= obraz->h)
            return;
        obraz->wklejObraz(bufor);
        P2.x = e->x();
        P2.y = e->y();
        rysujElipse();
    } else { // zmieniaj kąt
        obraz->wklejObraz(bufor);
        P4.x = e->x();
        P4.y = e->y();
        obliczKat();
        rysujElipse();
    }

}

void ToolElipsa::release(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {

        szkicuj = false;
    }

}

void ToolElipsa::rysujElipse(int x2, int y2, int kat, int steps)
{

    int x1 = xpocz;
    int y1 = ypocz;

    float rotate = 0.01745 * kat;
    float sinalfa = sin(rotate);
    float cosalfa = cos(rotate);

    if (x2 < x1)
        x2 = 2*x1 - x2;
    if (y2 > y1)
        y2 = 2*y1 - y2;

    int rw = x2-x1;
    int rh = y2-y1;
    if (Ekran::wcisnietyShift)
        rh = rw;

    if (!steps)
        steps = rw;

    float angle;

    int xt = rw*cos(0);
    int yt = rh*sin(0);

    int px0 = x1 + cosalfa * xt - sinalfa * yt;
    int py0 = y1 + sinalfa * xt + cosalfa * yt;

    int px1, py1;
   /*     int xx = x1+rw*cos(0);
        int yy = y1+rh*sin(0);*/

    for (int i = 1; i <= steps; ++i) {
        angle = 1.0 * i/steps * 6.28;
        xt = rw*cos(angle);
        yt = rh*sin(angle);
        px1 = x1 + cosalfa * xt - sinalfa * yt;
        py1 = y1 + sinalfa * xt + cosalfa * yt;
        linia->xpocz = px1;
        linia->ypocz = py1;
        linia->rysujLinie(px0, py0);
     /*       linia->xpocz = x1+xt;
            linia->ypocz = y1+yt;
            linia->rysujLinie(xx, yy);*/
        px0 = px1;
        py0 = py1;
           /* xx = xt+x1;
            yy = yt+y1;*/
    }

}


void ToolElipsa::rysujElipse()
{

    int x1 = P1.x;
    int y1 = P1.y;
    int x2 = P2.x;
    int y2 = P2.y;
    float rotate = kat2;
    int steps = 100;

    float sinalfa = sin(rotate);
    float cosalfa = cos(rotate);

    if (x2 < x1)
        x2 = 2*x1 - x2;
    if (y2 > y1)
        y2 = 2*y1 - y2;

    int rw = x2-x1;
    int rh = y2-y1;
    if (Ekran::wcisnietyShift)
        rh = rw;

    if (!steps)
        steps = rw;

    float angle;

    int xt = rw*cos(0);
    int yt = rh*sin(0);

    int px0 = x1 + cosalfa * xt - sinalfa * yt;
    int py0 = y1 + sinalfa * xt + cosalfa * yt;

    int px1, py1;
   /*     int xx = x1+rw*cos(0);
        int yy = y1+rh*sin(0);*/

    for (int i = 1; i <= steps; ++i) {
        angle = 1.0 * i/steps * 6.28;
        xt = rw*cos(angle);
        yt = rh*sin(angle);
        px1 = x1 + cosalfa * xt - sinalfa * yt;
        py1 = y1 + sinalfa * xt + cosalfa * yt;
        linia->xpocz = px1;
        linia->ypocz = py1;
        linia->rysujLinie(px0, py0);
     /*       linia->xpocz = x1+xt;
            linia->ypocz = y1+yt;
            linia->rysujLinie(xx, yy);*/
        px0 = px1;
        py0 = py1;
           /* xx = xt+x1;
            yy = yt+y1;*/
    }

}

void ToolElipsa::obliczKat()
{
    kat2 += atan2(abs(P4.y-P3.y),abs(P4.x-P1.x));
   /* if (P4.x < P1.x) {
        if (P4.y < P1.y) { // III
            kat2 += 3.14;
        } else { // II
            kat2 += 1.57;
        }
    } else if (P4.y < P1.y) { // IV
        kat2 += 4.71;
    }*/
}

void ToolElipsa::sprzatnij() {
    szkicuj = true;
    kat2 = 0;
    bufor->wklejObraz(obraz);
}
