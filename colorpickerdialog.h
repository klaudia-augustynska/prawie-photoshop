#ifndef COLORPICKERDIALOG_H
#define COLORPICKERDIALOG_H

#include <QDialog>
#include <QRadioButton>
#include <QSpinBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include "kolory.h"
#include "colorslider.h"
#include "colorselect.h"

namespace Ui {
class ColorPickerDialog;
}

class ColorPickerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ColorPickerDialog(QWidget *parent, QColor **);
    ~ColorPickerDialog();

private:
    Ui::ColorPickerDialog *ui;
    colorSelect *clSelect;



    QRadioButton *radioR;
    QRadioButton *radioG;
    QRadioButton *radioB;
    QRadioButton *radioH;
    QRadioButton *radioS;
    QRadioButton *radioV;
    QSpinBox *spinboxR;
    QSpinBox *spinboxG;
    QSpinBox *spinboxB;
    QSpinBox *spinboxH;
    QSpinBox *spinboxS;
    QSpinBox *spinboxV;
    colorSlider *sliderR;
    colorSlider *sliderG;
    colorSlider *sliderB;
    colorSlider *sliderH;
    colorSlider *sliderS;
    colorSlider *sliderV;

public slots:
    void SLOTzmianaKoloru();
    void SLOTzmianaKoloru2();
    void SLOTzmianaKoloruR();
    void SLOTzmianaKoloruG();
    void SLOTzmianaKoloruB();
    void SLOTzmianaKoloruH();
    void SLOTzmianaKoloruS();
    void SLOTzmianaKoloruV();
    void SLOTZmianaTrybu();
};

#endif // COLORPICKERDIALOG_H
