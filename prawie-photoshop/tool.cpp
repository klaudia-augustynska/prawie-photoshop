#include "tool.h"

Tool::Tool()
{
}

Obraz* Tool::obraz = NULL;
Obraz* Tool::bufor = NULL;
layer* Tool::currentLayer = NULL;
QWidget* Tool::ekran = NULL;

void Tool::press(QMouseEvent *)
{

}
void Tool::move(QMouseEvent *)
{

}
void Tool::release(QMouseEvent *)
{

}
void Tool::sprzatnij()
{

}
QColor Tool::getColor(Punkt P)
{
    int adr = 4*(P.y*obraz->w + P.x);
    QColor wynik;

    wynik.setBlue(obraz->dane[adr]);
    wynik.setGreen(obraz->dane[adr+1]);
    wynik.setRed(obraz->dane[adr+2]);
    wynik.setAlpha(obraz->dane[adr+3]);

    return wynik;
}

QColor Tool::getColor(int x, int y)
{
    int adr = 4*(y*obraz->w + x);
    QColor wynik;

    wynik.setBlue(obraz->dane[adr]);
    wynik.setGreen(obraz->dane[adr+1]);
    wynik.setRed(obraz->dane[adr+2]);
    wynik.setAlpha(obraz->dane[adr+3]);

    return wynik;
}

void Tool::setCurrentLayer(layer *l)
{
    currentLayer = l;
    obraz = l->o;
    if (bufor != NULL)
        bufor->wklejObraz(obraz);
    else
        bufor = new Obraz(obraz);
}

