#ifndef TOOLELIPSA_H
#define TOOLELIPSA_H

#include "tool.h"
#include "toollinia.h"
#include "ekran.h"

class ToolElipsa : public Tool
{
public:
    ToolElipsa();
    void press(QMouseEvent *);
    void move(QMouseEvent *);
    void release(QMouseEvent *);
    void sprzatnij();
private:
    void rysujElipse(int x2, int y2, int kat = 0, int steps = 0);
    void rysujElipse();
    void obliczKat();
    ToolLinia *linia;
    bool szkicuj;
    Punkt G;

    Punkt P1, P2, P3, P4;
    float kat2;
};

#endif // TOOLELIPSA_H
