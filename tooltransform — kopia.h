#ifndef TOOLTRANSFORM_H
#define TOOLTRANSFORM_H

#include <QList>
#include "tool.h"
#include "punkt.h"

class ToolTransform : public Tool
{
public:
    ToolTransform();
    void press(QMouseEvent *);
    void move(QMouseEvent *);
    void release(QMouseEvent *);
    void sprzatnij();

private:
    void rysujZaznaczenie();
    void rysujZaznaczenieKoncowe();
    void rysujPunkty();
    void rysujPunkt(const Punkt *);
    bool wOtoczeniu(const Punkt *A, Punkt *O);
    void wykonajOperacje();
    void translacja();
    void skalowanie();
    void rotacja();
    inline unsigned char blend_normal(unsigned char B, unsigned char L, float O)
    {	unsigned char a = (O * (L) + (1.0f - O) * B);
        if (a > 255) return 255;
        return a;
    }

    bool jestZaznaczenie;
    short angle1, angle2;
    Punkt A, B, AA, BB;
    QList<Punkt> PunktyKontrolne;
    enum Operacja {
        UNDEFINED,
        TRANSLACJA,
        SKALOWANIE,
        ROTACJA
    } operacja;
    short otoczenie;
    QColor *tlo;
    QColor *transparent;
};

#endif // TOOLTRANSFORM_H
