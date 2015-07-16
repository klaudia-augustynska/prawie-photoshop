#include "toolbspline.h"
#include <QDebug>

ToolBSpline::ToolBSpline()
{
    L = new QList<Punkt>();
    linia = new ToolLinia();
    otoczenie = 3;
    przesunPkt = false;
}

void ToolBSpline::press(QMouseEvent *e)
{
/*

klikam:
1. na punkt
    LPM: przesuwam
    PPM: usuwam
2. poza punktem
    LPM: dodaję punkt
    PPM: zapisuję krzywą

 */


    // czy klikniecie bylo na punkt?
    if (!L->empty()) {
        Punkt *G = new Punkt;
        G->x = e->x();
        G->y = e->y();
        for (int i = 0; i < L->size(); ++i) {
            if (wOtoczeniu(&(L->at(i)), G)) {  // TAK
                if (e->buttons() == Qt::LeftButton){ // LPM
                    przesun = i;
                    przesunPkt = true;
                } else if (e->buttons() == Qt::RightButton) { // PPM
                    L->removeAt(i);
                    obraz->wklejObraz(bufor);
                    polaczPunkty();
                }
                return;
            }
        }
        delete G;

        // jeśli doszło tutaj, to znaczy że nie zostało kliknięte na punkt
    }

    if (e->buttons() == Qt::LeftButton) {
        L->push_back(Punkt(e->x(), e->y()));
        polaczPunkty();
    } else if (e->buttons() == Qt::RightButton) {
        obraz->wklejObraz(bufor);
        polaczPunkty(false);
        if (!L->empty())
            L->clear();
        bufor->wklejObraz(obraz);
    }
}

void ToolBSpline::move(QMouseEvent *e)
{
    if (przesunPkt) {
        L->replace(przesun, Punkt(e->x(), e->y()));
        obraz->wklejObraz(bufor);
        polaczPunkty();
    }
}

void ToolBSpline::release(QMouseEvent *)
{
    przesunPkt = false;
}

void ToolBSpline::polaczPunkty(bool punkty)
{
    if (punkty) {
        narysujPunkty();
    }

    if (L->size() < 4) return;

    int i, len;
    len = L->size();
    for (i = 3; i < len; ++i)
        rysujKrzywa(L->at(i-3), L->at(i-2), L->at(i-1), L->at(i));
}


void ToolBSpline::rysujKrzywa(Punkt P0, Punkt P1, Punkt P2, Punkt P3) {

    float step;
    float t;
    Punkt A(0,0);
    Punkt B(0,0);
    float t3, t2;

    P[0] = P0;
    P[1] = P1;
    P[2] = P2;
    P[3] = P3;

    // wyznacz optymalny krok

    float xx, yy, dlugosc, idealnaDlugosc, dokladnosc;
    dokladnosc = 10;
    step = 1/dokladnosc;
    idealnaDlugosc = 3;
    dlugosc = 0;

    A.x = (P[0].x + P[1].x*4 + P[2].x)/6;
    A.y = (P[0].y + P[1].y*4 + P[2].y)/6;

    t = step;
    for (int i = 1; i <= dokladnosc; ++i, t += step) { // dla roznych t
        t2 = t*t;
        t3 = t2*t;

        B.x =  (
                P[0].x * (-t3 + 3*t2 - 3*t + 1) +
                P[1].x * (3*t3 - 6*t2 + 4) +
                P[2].x * (-3*t3 + 3*t2 + 3*t + 1) +
                P[3].x * (t3)
               ) / 6;
        B.y =  (
                P[0].y * (-t3 + 3*t2 - 3*t + 1) +
                P[1].y * (3*t3 - 6*t2 + 4) +
                P[2].y * (-3*t3 + 3*t2 + 3*t + 1) +
                P[3].y * (t3)
               ) / 6;

        xx = abs(B.x - A.x);
        yy = abs(B.y - A.y);
        dlugosc += sqrt(xx*xx + yy*yy);

        A.x = B.x;
        A.y = B.y;
    }
    dlugosc = dlugosc/dokladnosc;
    step = idealnaDlugosc * step / dlugosc;


    // policz to

    A.x = (P[0].x + P[1].x*4 + P[2].x)/6;
    A.y = (P[0].y + P[1].y*4 + P[2].y)/6;


    for (t = step; t < 1; t += step) { // dla roznych t
        t2 = t*t;
        t3 = t2*t;
        B.x =  (
                P[0].x * (-t3 + 3*t2 - 3*t + 1) +
                P[1].x * (3*t3 - 6*t2 + 4) +
                P[2].x * (-3*t3 + 3*t2 + 3*t + 1) +
                P[3].x * (t3)
               ) / 6;
        B.y =  (
                P[0].y * (-t3 + 3*t2 - 3*t + 1) +
                P[1].y * (3*t3 - 6*t2 + 4) +
                P[2].y * (-3*t3 + 3*t2 + 3*t + 1) +
                P[3].y * (t3)
               ) / 6;
        linia->rysujLinie(A,B);
        A.x = B.x;
        A.y = B.y;
    }

}

bool ToolBSpline::wOtoczeniu(const Punkt *A, Punkt *O)
{
    if (    A->x <= O->x + otoczenie
         && A->x >= O->x - otoczenie
         && A->y <= O->y + otoczenie
         && A->y >= O->y - otoczenie
       )
        return true;
    return false;
}

void ToolBSpline::narysujPunkty()
{
    if (L->empty()) return;

    for (int i = 0; i < L->size(); ++i) {
        wypelnijPunkt(L->at(i), QColor(0,0,0));
    }
}

void ToolBSpline::wypelnijPunkt(Punkt G, QColor c)
{
    --otoczenie;
    for (int i = G.y-otoczenie; i <= G.y+otoczenie; ++i) {
        for (int j = G.x-otoczenie; j <= G.x+otoczenie; ++j) {
            rysujPiksel(j,i,c);
        }
    }
    ++otoczenie;

}

void ToolBSpline::sprzatnij() {
    przesunPkt = false;
    obraz->wklejObraz(bufor);
    polaczPunkty(false);
    bufor->wklejObraz(obraz);
    if (L != NULL)
        L->clear();
}
