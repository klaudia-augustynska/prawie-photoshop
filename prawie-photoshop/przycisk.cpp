#include "przycisk.h"

Przycisk::Przycisk(QWidget *parent, int w, int h, QColor **d) :
    QWidget(parent),
    c(d)
{
    this->setFixedSize(w,h);
}

void Przycisk::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.fillRect(0,0,width(), height(), QColor((*c)->red(),(*c)->green(),(*c)->blue(),255));
}

void Przycisk::mousePressEvent(QMouseEvent *e) {
    setFocus();

    dialog = new ColorPickerDialog(0,c);
    if (dialog->exec() == QDialog::Accepted) {
        (*c)->setRed(Kolory::nowy->red());
        (*c)->setGreen(Kolory::nowy->green());
        (*c)->setBlue(Kolory::nowy->blue());
    }
    delete dialog;

    update();
}
