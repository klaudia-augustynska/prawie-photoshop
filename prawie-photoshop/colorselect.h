#ifndef COLORSELECT_H
#define COLORSELECT_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

#include "obraz.h"
#include "math.h"

class colorSelect : public QWidget
{
    Q_OBJECT
public:
    explicit colorSelect(QWidget *parent, int n);
    void paintEvent(QPaintEvent *);
    Obraz *o;
    void wypelnij();
    void pokazBiezacy(int biezX = -1, int biezY = -1);

signals:
    void SIGzmianaKoloru2();

private:
    void zrobLadnyMargines();
    int margines;
    float ratio, ratio2, ratio3;
    char mode;
    int n;

    void rysujOkrag(int xpocz, int ypocz, int promien, int, int, int);
    void reagujNaMyszke(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *);

    void mouseMoveEvent(QMouseEvent *);

    void mouseReleaseEvent(QMouseEvent *);

    Obraz *bufor;
    
};

#endif // COLORSELECT_H
