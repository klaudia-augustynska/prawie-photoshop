#ifndef TRANSFORMDIALOG_H
#define TRANSFORMDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QSlider>

#include "punkt.h"

namespace Ui {
class TransformDialog;
}

class TransformDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TransformDialog(Punkt A, Punkt B, QWidget *parent = 0);
    ~TransformDialog();

private:
    Ui::TransformDialog *ui;
    QSpinBox *spinboxT;
    QSpinBox *spinboxR;
    QSpinBox *spinboxS;
};

#endif // TRANSFORMDIALOG_H
