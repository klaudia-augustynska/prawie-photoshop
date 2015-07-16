#include "colorpickerdialog.h"
#include "ui_colorpickerdialog.h"

ColorPickerDialog::ColorPickerDialog(QWidget *parent, QColor **c) :
    QDialog(parent),
    ui(new Ui::ColorPickerDialog)
{
    ui->setupUi(this);

    Kolory::nowy->setRed((*c)->red());
    Kolory::nowy->setGreen((*c)->green());
    Kolory::nowy->setBlue((*c)->blue());


    clSelect = new colorSelect(this,270);
    clSelect->move(10,10);
    clSelect->update();

    QWidget *wg = new QWidget(this);
    QVBoxLayout *vl = new QVBoxLayout(wg);

    QHBoxLayout *hH = new QHBoxLayout;
    vl->addLayout(hH);
        sliderH = new colorSlider(this,256,30,'H');
        sliderH->update();
        radioH = new QRadioButton(this);
        QLabel *labelH = new QLabel("H");
        spinboxH = new QSpinBox;
        spinboxH->setRange(0,360);
        spinboxH->setSingleStep(1);
        spinboxH->setValue(Kolory::nowyH);
    hH->addWidget(radioH);
    hH->addWidget(labelH);
    hH->addWidget(spinboxH);
    hH->addWidget(sliderH);

    QHBoxLayout *hS = new QHBoxLayout;
    vl->addLayout(hS);
        radioS = new QRadioButton(this);
        QLabel *labelS = new QLabel("S");
        spinboxS = new QSpinBox;
        spinboxS->setRange(0,100);
        spinboxS->setSingleStep(1);
        spinboxS->setValue(Kolory::nowyS);
        sliderS = new colorSlider(this,256,30,'S');
        sliderS->update();
    hS->addWidget(radioS);
    hS->addWidget(labelS);
    hS->addWidget(spinboxS);
    hS->addWidget(sliderS);

    QHBoxLayout *hV = new QHBoxLayout;
    vl->addLayout(hV);
        radioV = new QRadioButton(this);
        QLabel *labelV = new QLabel("V");
        spinboxV = new QSpinBox;
        spinboxV->setRange(0,100);
        spinboxV->setSingleStep(1);
        spinboxV->setValue(Kolory::nowyV);
        sliderV = new colorSlider(this,256,30,'V');
        sliderV->update();
    hV->addWidget(radioV);
    hV->addWidget(labelV);
    hV->addWidget(spinboxV);
    hV->addWidget(sliderV);



    QHBoxLayout *hR = new QHBoxLayout;
    vl->addLayout(hR);
        radioR = new QRadioButton(this);
        QLabel *labelR = new QLabel("R");
        spinboxR = new QSpinBox;
        spinboxR->setRange(0,255);
        spinboxR->setSingleStep(1);
        spinboxR->setValue(Kolory::nowy->red());
        sliderR = new colorSlider(this,256,30,'R');
        sliderR->update();
    hR->addWidget(radioR);
    hR->addWidget(labelR);
    hR->addWidget(spinboxR);
    hR->addWidget(sliderR);

    QHBoxLayout *hG = new QHBoxLayout;
    vl->addLayout(hG);
        radioG = new QRadioButton(this);
        QLabel *labelG = new QLabel("G");
        spinboxG = new QSpinBox;
        spinboxG->setRange(0,255);
        spinboxG->setSingleStep(1);
        spinboxG->setValue(Kolory::nowy->green());
        sliderG = new colorSlider(this,256,30,'G');
        sliderG->update();
    hG->addWidget(radioG);
    hG->addWidget(labelG);
    hG->addWidget(spinboxG);
    hG->addWidget(sliderG);

    QHBoxLayout *hB = new QHBoxLayout;
    vl->addLayout(hB);
        radioB = new QRadioButton(this);
        QLabel *labelB = new QLabel("B");
        spinboxB = new QSpinBox;
        spinboxB->setRange(0,255);
        spinboxB->setSingleStep(1);
        spinboxB->setValue(Kolory::nowy->blue());
        sliderB = new colorSlider(this,256,30,'B');
        sliderB->update();
    hB->addWidget(radioB);
    hB->addWidget(labelB);
    hB->addWidget(spinboxB);
    hB->addWidget(sliderB);





    switch(Kolory::mode) {
    case 'R':
        radioR->setChecked(true);
        break;
    case 'G':
        radioG->setChecked(true);
        break;
    case 'B':
        radioB->setChecked(true);
        break;
    case 'H':
        radioH->setChecked(true);
        break;
    case 'S':
        radioS->setChecked(true);
        break;
    case 'V':
        radioV->setChecked(true);
        break;
    }

    wg->setLayout(vl);
    wg->adjustSize();
    wg->move(300,10);

    this->adjustSize();

    connect(sliderR, SIGNAL(SIGzmianaKoloru()), this, SLOT(SLOTzmianaKoloru()));
    connect(sliderG, SIGNAL(SIGzmianaKoloru()), this, SLOT(SLOTzmianaKoloru()));
    connect(sliderB, SIGNAL(SIGzmianaKoloru()), this, SLOT(SLOTzmianaKoloru()));
    connect(sliderH, SIGNAL(SIGzmianaKoloru()), this, SLOT(SLOTzmianaKoloru()));
    connect(sliderS, SIGNAL(SIGzmianaKoloru()), this, SLOT(SLOTzmianaKoloru()));
    connect(sliderV, SIGNAL(SIGzmianaKoloru()), this, SLOT(SLOTzmianaKoloru()));
    connect(clSelect, SIGNAL(SIGzmianaKoloru2()), this, SLOT(SLOTzmianaKoloru2()));

    connect(spinboxR, SIGNAL(valueChanged(int)), this, SLOT(SLOTzmianaKoloruR()));
    connect(spinboxG, SIGNAL(valueChanged(int)), this, SLOT(SLOTzmianaKoloruG()));
    connect(spinboxB, SIGNAL(valueChanged(int)), this, SLOT(SLOTzmianaKoloruB()));
    connect(spinboxH, SIGNAL(valueChanged(int)), this, SLOT(SLOTzmianaKoloruH()));
    connect(spinboxS, SIGNAL(valueChanged(int)), this, SLOT(SLOTzmianaKoloruS()));
    connect(spinboxV, SIGNAL(valueChanged(int)), this, SLOT(SLOTzmianaKoloruV()));

    connect(radioR, SIGNAL(clicked()), this, SLOT(SLOTZmianaTrybu()));
    connect(radioG, SIGNAL(clicked()), this, SLOT(SLOTZmianaTrybu()));
    connect(radioB, SIGNAL(clicked()), this, SLOT(SLOTZmianaTrybu()));
    connect(radioH, SIGNAL(clicked()), this, SLOT(SLOTZmianaTrybu()));
    connect(radioS, SIGNAL(clicked()), this, SLOT(SLOTZmianaTrybu()));
    connect(radioV, SIGNAL(clicked()), this, SLOT(SLOTZmianaTrybu()));
}

ColorPickerDialog::~ColorPickerDialog()
{
    delete ui;
    delete sliderR;
    delete sliderG;
    delete sliderB;
}


void ColorPickerDialog::SLOTzmianaKoloru()
{
    sliderR->wypelnij();
    sliderR->update();
    sliderG->wypelnij();
    sliderG->update();
    sliderB->wypelnij();
    sliderB->update();
    sliderH->wypelnij();
    sliderH->update();
    sliderS->wypelnij();
    sliderS->update();
    sliderV->wypelnij();
    sliderV->update();
    clSelect->wypelnij();
    clSelect->pokazBiezacy();
    clSelect->update();
    spinboxR->setValue(Kolory::nowy->red());
    spinboxG->setValue(Kolory::nowy->green());
    spinboxB->setValue(Kolory::nowy->blue());
    spinboxH->setValue(Kolory::nowyH);
    spinboxS->setValue(Kolory::nowyS);
    spinboxV->setValue(Kolory::nowyV);
}


void ColorPickerDialog::SLOTzmianaKoloru2()
{
    sliderR->wypelnij();
    sliderR->update();
    sliderG->wypelnij();
    sliderG->update();
    sliderB->wypelnij();
    sliderB->update();
    sliderH->wypelnij();
    sliderH->update();
    sliderS->wypelnij();
    sliderS->update();
    sliderV->wypelnij();
    sliderV->update();
    spinboxR->setValue(Kolory::nowy->red());
    spinboxG->setValue(Kolory::nowy->green());
    spinboxB->setValue(Kolory::nowy->blue());
    spinboxH->setValue(Kolory::nowyH);
    spinboxS->setValue(Kolory::nowyS);
    spinboxV->setValue(Kolory::nowyV);
}

void ColorPickerDialog::SLOTzmianaKoloruR()
{
    Kolory::nowy->setRed(spinboxR->value());
    SLOTzmianaKoloru();
}
void ColorPickerDialog::SLOTzmianaKoloruG()
{
    Kolory::nowy->setGreen(spinboxG->value());
    SLOTzmianaKoloru();
}
void ColorPickerDialog::SLOTzmianaKoloruB()
{
    Kolory::nowy->setBlue(spinboxB->value());
    SLOTzmianaKoloru();
}
void ColorPickerDialog::SLOTzmianaKoloruH()
{
    Kolory::nowyH = spinboxH->value();
    SLOTzmianaKoloru();
}
void ColorPickerDialog::SLOTzmianaKoloruS()
{
    Kolory::nowyS = spinboxS->value();
    SLOTzmianaKoloru();
}
void ColorPickerDialog::SLOTzmianaKoloruV()
{
    Kolory::nowyV = spinboxV->value();
    SLOTzmianaKoloru();
}
void ColorPickerDialog::SLOTZmianaTrybu()
{
    if (radioR->isChecked())
        Kolory::mode = 'R';
    else if (radioG->isChecked())
        Kolory::mode = 'G';
    else if (radioB->isChecked())
        Kolory::mode = 'B';
    else if (radioH->isChecked())
        Kolory::mode = 'H';
    else if (radioS->isChecked())
        Kolory::mode = 'S';
    else if (radioV->isChecked())
        Kolory::mode = 'V';
    clSelect->wypelnij();
    clSelect->pokazBiezacy();
    clSelect->update();
}
