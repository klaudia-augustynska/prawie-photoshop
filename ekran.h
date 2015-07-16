#ifndef EKRAN_H
#define EKRAN_H

#include <QWidget>
#include <QPainter>
#include <QList>
#include "obraz.h"
#include "tool.h"
#include "layer.h"

class Ekran : public QWidget
{
    Q_OBJECT
public:
    explicit Ekran(QWidget *parent, Tool **t, QList<layer*> *warstwy);
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);

    Obraz *obraz;
    Tool **tool;
    QList<layer*> *warstwy;
    static bool wcisnietyShift;
    static bool wcisnietyCtrl;
private:
    void mieszajWarstwy();
    
signals:
    
public slots:
    
};

#endif // EKRAN_H
