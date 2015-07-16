#include "toollinia.h"

ToolLinia::ToolLinia()
{
}

void ToolLinia::press(QMouseEvent *e)
{
    xpocz = e->x();
    ypocz = e->y();
    bufor->wklejObraz(obraz);
}

void ToolLinia::move(QMouseEvent *e)
{
    if (e->x() < 0 || e->y() < 0 || e->x() >= obraz->w || e->y() >= obraz->h)
        return;
    obraz->wklejObraz(bufor);
    rysujLinie(Punkt(xpocz,ypocz), Punkt(e->x(),e->y()));
}

void ToolLinia::release(QMouseEvent *)
{
    bufor->wklejObraz(obraz);
}

void ToolLinia::rysujLinie(int x2, int y2)
{
    int x1 = xpocz;
    int y1 = ypocz;

    if (x1 > x2) {
        int temp = x1;
        x1 = x2;
        x2 = temp;
        temp = y1;
        y1 = y2;
        y2 = temp;
    }

    if (abs(x2-x1) > abs(y2-y1)) {

        if (x1 == x2)
            ++x2;

        double A = 1.0 * (y2-y1) / (x2-x1);
        double B = 1.0 * (y2 - A*x2);

        for (int i = x1; i < x2; ++i) {
            rysujPiksel(i,A*i + B);
        }

    } else {

        if (x1 == x2)
            ++x2;

        double A = 1.0 * (y2-y1) / (x2-x1);
        double B = 1.0 * (-A * x1) + y1;

        if (A == 0)
            ++A;

        if (y1 > y2) {
            int temp = x1;
            x1 = x2;
            x2 = temp;
            temp = y1;
            y1 = y2;
            y2 = temp;
        }

        for (int i = y1; i <= y2; i++) {
            rysujPiksel((i-B)/A, i);
        }
    }

}


void ToolLinia::rysujLinie(Punkt A, Punkt B)
{
    A.round();
    B.round();

    if (A.x == B.x) { // pionowa linia
        if (A.y > B.y)
            A.swapY(&B);
        for (int i = A.y; i <= B.y; ++i)
            rysujPiksel(A.x,i);
    }
    else
        if (A.y == B.y) { // pozioma linia
            if (B.x < A.x)
                A.swapX(&B);
            for (int i = A.x; i <= B.x; ++i)
                rysujPiksel(i,A.y);
        }
    else
        if (abs(A.y - B.y) > abs(A.x - B.x)) { // y > x - rysowanie po `y`
            if (B.x < A.x)
                A.swap(&B);
            float a = 1.0 * (B.y-A.y) / (B.x-A.x);
            float b = 1.0 * (-a * A.x) + A.y;
            if (A.y > B.y)
                A.swapY(&B);
            for (int i = A.y; i <= B.y; ++i)
                rysujPiksel((i-b)/a, i);
        }
    else { // rysowanie po `x`
        if (B.y < A.y)
            A.swap(&B);
        float a = 1.0 * (B.y-A.y) / (B.x-A.x);
        float b = 1.0 * (B.y - a*B.x);
        if (A.x > B.x)
            A.swapX(&B);
        for (int i = A.x; i <= B.x; ++i)
            rysujPiksel(i,a*i + b);
    }

}

void ToolLinia::sprzatnij() {
    bufor->wklejObraz(obraz);
}
