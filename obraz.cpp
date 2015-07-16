#include "obraz.h"

Obraz::Obraz(int w, int h)
{
    this->w = w;
    this->h = h;
    dane = new unsigned char[w*h*4];
    int pole = 4*w*h;
    for (int i = 0; i < pole; i+=4) {
        dane[i] = 255; // B
        dane[i+1] = 255; // G
        dane[i+2] = 255; // R
        dane[i+3] = 0; // A
    }
}

Obraz::Obraz(Obraz *o) {
    w = o->w;
    h = o->h;
    dane = new unsigned char[w*h*4];
    wklejObraz(o);
}

void Obraz::wklejObraz(Obraz *o) {
    int pole = this->w*this->h;
    for (int i = 0; i < pole; ++i) {
        this->dane[4*i]    = o->dane[4*i]; // B
        this->dane[4*i+1]  = o->dane[4*i+1]; // G
        this->dane[4*i+2]  = o->dane[4*i+2]; // R
        this->dane[4*i+3]  = o->dane[4*i+3]; // A
    }
}

void Obraz::wklejObraz(QImage *o) {

    for (int i = 0; i < this->h; ++i) {
        for (int j = 0; j < this->w; ++j) {
            if (j < o->width() && i < o->height()) {
                dane[4*(i*w+j)  ] = o->bits()[4*(i*o->width()+j)  ];
                dane[4*(i*w+j)+1] = o->bits()[4*(i*o->width()+j)+1];
                dane[4*(i*w+j)+2] = o->bits()[4*(i*o->width()+j)+2];
                dane[4*(i*w+j)+3] = o->bits()[4*(i*o->width()+j)+3];
            }
            else {
                dane[4*(i*w+j)]   = 0;
                dane[4*(i*w+j)+1] = 0;
                dane[4*(i*w+j)+2] = 0;
                dane[4*(i*w+j)+3] = 0;
            }
        }
    }

}

QColor Obraz::getColor(int x, int y)
{
    int adr = 4*(y*w + x);
    QColor wynik;

    wynik.setBlue(dane[adr]);
    wynik.setGreen(dane[adr+1]);
    wynik.setRed(dane[adr+2]);
    wynik.setAlpha(dane[adr+3]);

    return wynik;
}
