#include "toolkrzywe.h"
#include <QDebug>

ToolKrzywe::ToolKrzywe()
{
    L = new QList<Punkty>();
    linia = new ToolLinia();
    otoczenie = 3;
    przesunAut = false;
    przesunMov = false;
    przesunPkt = false;
}

void ToolKrzywe::press(QMouseEvent *e)
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
            if (wOtoczeniu(L->at(i).pkt, G)) {  // TAK
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
            if (wOtoczeniu(L->at(i).mov, G)) {  // TAK
                if (e->buttons() == Qt::LeftButton){ // LPM
                    przesun = i;
                    przesunMov = true;
                } else if (e->buttons() == Qt::RightButton) { // PPM
                    L->removeAt(i);
                    obraz->wklejObraz(bufor);
                    polaczPunkty();
                }
                return;
            }
            if (wOtoczeniu(L->at(i).aut, G)) {  // TAK
                if (e->buttons() == Qt::LeftButton){ // LPM
                    przesun = i;
                    przesunAut = true;
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
        L->push_back(Punkty(e->x(), e->y()));
        polaczPunkty();
    } else if (e->buttons() == Qt::RightButton) {
        obraz->wklejObraz(bufor);
        polaczPunkty(false);
        if (!L->empty())
            L->clear();
        bufor->wklejObraz(obraz);
    }
}

void ToolKrzywe::move(QMouseEvent *e)
{
    if (przesunPkt) {
        Punkt Vmov, Vaut;
        Vmov.x = L->at(przesun).mov->x - L->at(przesun).pkt->x;
        Vmov.y = L->at(przesun).mov->y - L->at(przesun).pkt->y;
        Vaut.x = L->at(przesun).aut->x - L->at(przesun).pkt->x;
        Vaut.y = L->at(przesun).aut->y - L->at(przesun).pkt->y;

        L->at(przesun).pkt->x = e->x();
        L->at(przesun).pkt->y = e->y();
        L->at(przesun).mov->x = e->x() + Vmov.x;
        L->at(przesun).mov->y = e->y() + Vmov.y;
        L->at(przesun).aut->x = e->x() + Vaut.x;
        L->at(przesun).aut->y = e->y() + Vaut.y;
    } else if (przesunMov) {
        L->at(przesun).mov->x = e->x();
        L->at(przesun).mov->y = e->y();
    } else if (przesunAut) {
        L->at(przesun).aut->x = e->x();
        L->at(przesun).aut->y = e->y();
    } else {
        L->back().mov->x = e->x();
        L->back().mov->y = e->y();
        L->back().aut->x = 2 * L->back().pkt->x - e->x();
        L->back().aut->y = 2 * L->back().pkt->y - e->y();
    }

    obraz->wklejObraz(bufor);
    polaczPunkty();
}

void ToolKrzywe::release(QMouseEvent *)
{
    przesunAut = false;
    przesunMov = false;
    przesunPkt = false;
}

void ToolKrzywe::polaczPunkty(bool punkty)
{
    if (punkty) {
        narysujPunkty();
    }


    if (L->size() < 2) return;

    int i, len;
    len = L->size();
    for (i = 1; i < len; ++i)
        rysujKrzywa(*(L->at(i-1).pkt), *(L->at(i-1).mov), *(L->at(i).aut), *(L->at(i).pkt));
}


void ToolKrzywe::rysujKrzywa(Punkt P0, Punkt P1, Punkt P2, Punkt P3) {

    float step;
    float t,x;
    Punkt A(0,0);
    Punkt B(0,0);

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

    A.x = P[0].x;
    A.y = P[0].y;

    t = step;
    for (int i = 1; i <= dokladnosc; ++i, t += step) { // dla roznych t
        x = 1-t;
        B.x =   P[0].x*x*x*x +
                P[1].x*t*x*x*3 +
                P[2].x*t*t*x*3 +
                P[3].x*t*t*t;
        B.y =   P[0].y*x*x*x +
                P[1].y*t*x*x*3 +
                P[2].y*t*t*x*3 +
                P[3].y*t*t*t;

        xx = abs(B.x - A.x);
        yy = abs(B.y - A.y);
        dlugosc += sqrt(xx*xx + yy*yy);

        A.x = B.x;
        A.y = B.y;
    }
    dlugosc = dlugosc/dokladnosc;
    step = idealnaDlugosc * step / dlugosc;


    // policz to

    if (linia == NULL)
        linia = new ToolLinia();

    A.x = P[0].x;
    A.y = P[0].y;

    for (t = step; t < 1; t += step) { // dla roznych t
        x = 1-t;
        B.x =   P[0].x*x*x*x +
                P[1].x*t*x*x*3 +
                P[2].x*t*t*x*3 +
                P[3].x*t*t*t;
        B.y =   P[0].y*x*x*x +
                P[1].y*t*x*x*3 +
                P[2].y*t*t*x*3 +
                P[3].y*t*t*t;
        linia->rysujLinie(A,B);
        A.x = B.x;
        A.y = B.y;
    }
    linia->rysujLinie(A,P[3]);

}

bool ToolKrzywe::wOtoczeniu(Punkt *A, Punkt *O)
{
    if (    A->x <= O->x + otoczenie
         && A->x >= O->x - otoczenie
         && A->y <= O->y + otoczenie
         && A->y >= O->y - otoczenie
       )
        return true;
    return false;
}

void ToolKrzywe::narysujPunkty()
{
    if (L->empty()) return;

    for (int i = 0; i < L->size(); ++i) {
        wypelnijPunkt(*(L->at(i).mov), QColor(200,200,200));
        wypelnijPunkt(*(L->at(i).aut), QColor(200,200,200));
        wypelnijPunkt(*(L->at(i).pkt), QColor(0,0,0));
    }
}

void ToolKrzywe::wypelnijPunkt(Punkt G, QColor c)
{
    --otoczenie;
    for (int i = G.y-otoczenie; i <= G.y+otoczenie; ++i) {
        for (int j = G.x-otoczenie; j <= G.x+otoczenie; ++j) {
            rysujPiksel(j,i,c);
        }
    }
    ++otoczenie;

}

void ToolKrzywe::sprzatnij() {
    przesunAut = false;
    przesunMov = false;
    przesunPkt = false;
    obraz->wklejObraz(bufor);
    polaczPunkty(false);
    bufor->wklejObraz(obraz);
    if (L != NULL)
        L->clear();
}
