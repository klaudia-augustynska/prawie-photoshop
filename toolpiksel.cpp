#include "toolpiksel.h"
#include <QDebug>

ToolPiksel::ToolPiksel()
{
}

void ToolPiksel::press(QMouseEvent *e)
{

    rysujPiksel(e->x(),e->y());

    linia = new ToolLinia();
    linia->xpocz = e->x();
    linia->ypocz = e->y();
}

void ToolPiksel::move(QMouseEvent *e)
{
    linia->rysujLinie(e->x(),e->y());
    linia->xpocz = e->x();
    linia->ypocz = e->y();
}

void ToolPiksel::release(QMouseEvent *)
{
    bufor->wklejObraz(obraz);
}

void ToolPiksel::sprzatnij() {
    bufor->wklejObraz(obraz);
}

