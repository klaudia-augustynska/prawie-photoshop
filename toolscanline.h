#ifndef TOOLSCANLINE_H
#define TOOLSCANLINE_H

#include "tool.h"
#include "toollinia.h"
#include <QList>

class ToolScanLine : public Tool
{
public:
    ToolScanLine();
    void press(QMouseEvent *);
    void move(QMouseEvent *);
    void release(QMouseEvent *);
    void sprzatnij();
private:
    void polaczPunkty(bool punkty = true);
    void wypelnij();
    bool wOtoczeniu(const Punkt *A, Punkt *O);
    void narysujPunkty();
    void wypelnijPunkt(Punkt G, QColor c);
    QList<Punkt> *L;
    int przesun;
    ToolLinia *linia;
    int otoczenie;
    bool przesunPkt;
};

#endif // TOOLSCANLINE_H
