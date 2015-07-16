#ifndef COLORSLIDER_H
#define COLORSLIDER_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

#include "obraz.h"
#include "math.h"

class colorSlider : public QWidget
{
    Q_OBJECT
public:
    explicit colorSlider(QWidget *parent, int w, int h, char mode);
    void paintEvent(QPaintEvent *);
    Obraz *o;
    char mode;
    void wypelnij();

signals:
    void SIGzmianaKoloru();

private:
    void zrobLadnyMargines();
    int margines;
    float ratio;
    int w,h;

    void pokazBiezacy();
    void reagujNaMyszke(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *);

    void mouseMoveEvent(QMouseEvent *);

    void mouseReleaseEvent(QMouseEvent *);

};

#endif // COLORSLIDER_H
