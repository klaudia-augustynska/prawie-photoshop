#include "toolscanline.h"

ToolScanLine::ToolScanLine()
{
    L = new QList<Punkt>();
    linia = new ToolLinia();
    otoczenie = 3;
    przesunPkt = false;
}

void ToolScanLine::press(QMouseEvent *e)
{

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

void ToolScanLine::move(QMouseEvent *e)
{
    if (przesunPkt) {
        L->replace(przesun, Punkt(e->x(), e->y()));
        obraz->wklejObraz(bufor);
        polaczPunkty();
    }
}

void ToolScanLine::release(QMouseEvent *)
{
    przesunPkt = false;
}

void ToolScanLine::polaczPunkty(bool punkty)
{
    obraz->wklejObraz(bufor);

    if (L->size() < 2) {
        narysujPunkty();
        return;
    }

    int i, len;
    len = L->size();
    for (i = 1; i < len; ++i) {
        linia->rysujLinie(L->at(i-1),L->at(i));
    }
    linia->rysujLinie(L->at(i-1),L->at(0));
    wypelnij();
    if (punkty) {
        narysujPunkty();
    }
}

void ToolScanLine::wypelnij()
{
    if (L->size() < 3) return;

    // wyodrębnij obszar figury

    int miny, maxy;
    miny = maxy = L->at(0).y;
    int minx, maxx;
    minx = maxx = L->at(0).x;

    for (int i = 1; i < L->size(); ++i) {
        if (L->at(i).y < miny)
            miny = L->at(i).y;
        else if (L->at(i).y > maxy)
            maxy = L->at(i).y;

        if (L->at(i).x < minx)
            minx = L->at(i).x;
        else if (L->at(i).x > maxx)
            maxx = L->at(i).x;
    }

    // wypełnij

    L->push_back(L->at(0)); // polacz ostatni odcinek z pierwszym

    for (int y = miny; y <= maxy; ++y) { // dla kazdego wiersza
        // 1) znajdź przecięcia
        QList<int> iksy;
        for (int i = 1; i < L->size(); ++i) { // dla kazdego odcinka
            Punkt A(L->at(i-1));
            Punkt B(L->at(i));

            if (A.y == B.y)
                continue;
            else if (A.y > B.y)
                A.swap(&B);
            if (y < A.y || y >= B.y)
                continue;

            int x;
            x = abs((B.x - A.x)/(B.y - A.y) * (y - A.y) + A.x);

            iksy.push_back(x);
        } // END dla odcinka

        // 2) posortuj
        qSort(iksy);

        // 3) pomaluj
        for (int i = 1; i < iksy.size(); i+=2) {
            for (int x = iksy.at(i-1); x <= iksy.at(i); ++x )
                rysujPiksel(x,y);
        }

    } // END dla wiersza
    L->pop_back();

}

bool ToolScanLine::wOtoczeniu(const Punkt *A, Punkt *O)
{
    if (    A->x <= O->x + otoczenie
         && A->x >= O->x - otoczenie
         && A->y <= O->y + otoczenie
         && A->y >= O->y - otoczenie
       )
        return true;
    return false;
}

void ToolScanLine::narysujPunkty()
{
    if (L->empty()) return;

    for (int i = 0; i < L->size(); ++i) {
        wypelnijPunkt(L->at(i), QColor(0,0,0));
    }
}

void ToolScanLine::wypelnijPunkt(Punkt G, QColor c)
{
    --otoczenie;
    for (int i = G.y-otoczenie; i <= G.y+otoczenie; ++i) {
        for (int j = G.x-otoczenie; j <= G.x+otoczenie; ++j) {
            rysujPiksel(j,i,c);
        }
    }
    ++otoczenie;

}

void ToolScanLine::sprzatnij() {
    przesunPkt = false;
    obraz->wklejObraz(bufor);
    polaczPunkty(false);
    bufor->wklejObraz(obraz);
    if (L != NULL)
        L->clear();
}
