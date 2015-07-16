#include "toolkolko.h"

ToolKolko::ToolKolko()
{
}

void ToolKolko::press(QMouseEvent *e)
{
    xpocz = e->x();
    ypocz = e->y();
    bufor->wklejObraz(obraz);
}

void ToolKolko::move(QMouseEvent *e)
{
    if (e->x() < 0 || e->y() < 0 || e->x() >= obraz->w || e->y() >= obraz->h)
        return;
    obraz->wklejObraz(bufor);
    rysujOkrag(e->x(),e->y());
}

void ToolKolko::release(QMouseEvent *)
{
    bufor->wklejObraz(obraz);
}

void ToolKolko::rysujOkrag(int x2, int y2)
{
    int x1 = xpocz;
    int y1 = ypocz;

    if (x2 < x1)
        x2 = 2*x1 - x2;
    if (y2 > y1)
        y2 = 2*y1 - y2;

    int promien = sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
    int promien2 = promien*promien;

    int punkt = ceil(sqrt(promien2 / 2));
    int temp;

    for (int i = -punkt; i < punkt; ++i) {
        temp = sqrt(promien2 - i*i);
        rysujPiksel(i+x1,  temp + y1);
        rysujPiksel(i+x1, -temp + y1);
        rysujPiksel( temp + x1, i+y1);
        rysujPiksel(-temp + x1, i+y1);
    }

}

void ToolKolko::sprzatnij() {
    bufor->wklejObraz(obraz);
}
