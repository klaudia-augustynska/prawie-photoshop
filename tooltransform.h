#ifndef TOOLTRANSFORM_H
#define TOOLTRANSFORM_H

#include "tool.h"
#include "transform.h"
#include "transformdialog.h"



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

    Punkt A, B;
    bool jestZaznaczenie;
};

#endif // TOOLTRANSFORM_H
