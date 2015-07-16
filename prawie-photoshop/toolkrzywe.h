#ifndef TOOLKRZYWE_H
#define TOOLKRZYWE_H

#include "tool.h"
#include "toollinia.h"
#include <QList>

struct Punkty
{
public:
    Punkty(int x, int y)
    {
        pkt = new Punkt(x,y);
        mov = new Punkt(x,y);
        aut = new Punkt(x,y);
    };

    Punkt *pkt;
    Punkt *mov;
    Punkt *aut;
};

class ToolKrzywe : public Tool
{
public:
    ToolKrzywe();
    void press(QMouseEvent *);
    void move(QMouseEvent *);
    void release(QMouseEvent *);
    void sprzatnij();
private:
    void polaczPunkty(bool punkty = true);
    void rysujKrzywa(Punkt P0, Punkt P1, Punkt P2, Punkt P3);
    bool wOtoczeniu(Punkt *A, Punkt *O);
    void narysujPunkty();
    void wypelnijPunkt(Punkt G, QColor c);
    QList<Punkty> *L;
    Punkt P[4];
    int przesun;
    ToolLinia *linia;
    int otoczenie;
    bool przesunPkt;
    bool przesunAut;
    bool przesunMov;
};

#endif // TOOLKRZYWE_H
