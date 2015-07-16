#ifndef TOOLBSPLINE_H
#define TOOLBSPLINE_H

#include "tool.h"
#include "toollinia.h"
#include <QList>

class ToolBSpline : public Tool
{
public:
    ToolBSpline();
    void press(QMouseEvent *);
    void move(QMouseEvent *);
    void release(QMouseEvent *);
    void sprzatnij();
private:
    void polaczPunkty(bool punkty = true);
    void rysujKrzywa(Punkt P0, Punkt P1, Punkt P2, Punkt P3);
    bool wOtoczeniu(const Punkt *A, Punkt *O);
    void narysujPunkty();
    void wypelnijPunkt(Punkt G, QColor c);
    QList<Punkt> *L;
    Punkt P[4];
    int przesun;
    ToolLinia *linia;
    int otoczenie;
    bool przesunPkt;

};

#endif // TOOLBSPLINE_H
