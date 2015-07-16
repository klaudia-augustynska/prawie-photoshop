#include "ekran.h"
#include <QDebug>

Ekran::Ekran(QWidget *parent, Tool **t, QList<layer*> *w) :
    QWidget(parent),
    tool(t),
    warstwy(w)
{
}

bool Ekran::wcisnietyShift = false;
bool Ekran::wcisnietyCtrl = false;

void Ekran::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    mieszajWarstwy();

    if (Tool::obraz != NULL) {
        QImage im(warstwy->at(0)->o->dane, Tool::obraz->w, Tool::obraz->h, QImage::Format_ARGB32);
        p.drawImage(0, 0, im);
    }
}

void Ekran::mousePressEvent(QMouseEvent *e) {
    setFocus();
    (*tool)->press(e);
    update();
}

void Ekran::mouseMoveEvent(QMouseEvent *e) {

    (*tool)->move(e);
    update();

}

void Ekran::mouseReleaseEvent(QMouseEvent *e) {
    (*tool)->release(e);
    update();
}

void Ekran::keyPressEvent(QKeyEvent *e) {
    switch (e->key()) {
    case Qt::Key_Shift:
        wcisnietyShift = true;
        wcisnietyCtrl = true;
        break;
    }
}

void Ekran::keyReleaseEvent(QKeyEvent *) {
    wcisnietyShift = false;
    wcisnietyCtrl = false;
}

void Ekran::mieszajWarstwy()
{
    for (int i = 1; i < warstwy->size(); ++i) {
        if (warstwy->at(i)->visibility())
            warstwy->at(0)->blend(warstwy->at(i));
    }
}
