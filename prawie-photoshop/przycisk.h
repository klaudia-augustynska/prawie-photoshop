#ifndef PRZYCISK_H
#define PRZYCISK_H

#include <QWidget>
#include <QPainter>
#include "colorpickerdialog.h"
#include "kolory.h"

class Przycisk : public QWidget
{
    Q_OBJECT
public:
    explicit Przycisk(QWidget *parent, int w, int h, QColor **c);
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    QColor **c;
    ColorPickerDialog *dialog;


signals:

public slots:

};

#endif // PRZYCISK_H
