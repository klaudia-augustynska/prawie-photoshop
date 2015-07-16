#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDesktopWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QSpinBox>
#include <QComboBox>
#include <QListWidget>
#include <QListWidgetItem>
#include <QList>
#include <QCheckBox>

#include <QAction>
#include <QMenuBar>
#include <QToolBar>
#include <QFileDialog>

#include "layer.h"
#include "kolory.h"
#include "ekran.h"
#include "obraz.h"
#include "tool.h"
#include "toolpiksel.h"
#include "toollinia.h"
#include "toolkolko.h"
#include "toolelipsa.h"
#include "toolkrzywe.h"
#include "toolbspline.h"
#include "toolfloodfill.h"
#include "toolscanline.h"
#include "tooltransform.h"
#include "przycisk.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void Piksel();
    void Kolko();
    void Linia();
    void Elipsa();
    void Krzywe();
    void BSpline();
    void FloodFill();
    void ScanLine();
    void Transform();
    void Wyczysc();
  /*  void setValueR(int);
    void setValueG(int);
    void setValueB(int);
    void setValueA(int);*/
    void open();
    void erozja();
    void dylatacja();
    void DodajWarstwe();
    void UsunWarstwe();
    void ZmianaWarstwy();
    void ZmienPrzezroczystosc(int);
    void ZmianaTrybuMieszania(int);
    void ZmienKolejnoscWarstwUp();
    void ZmienKolejnoscWarstwDown();
    void ZmienWidocznoscWarstwy(bool);

private:
    void createWindow();
    void createEkran();
    void createActions();
    void createBtns();
    void createLayers();
    void uncheckall();
    void UpdateFields();
    void ZmienKolejnoscWarstw(int);
    QHBoxLayout *layoutH;

    QVBoxLayout *layoutV;
    QSlider *sliderR;
    QSlider *sliderG;
    QSlider *sliderB;
    QSlider *sliderA;
    QSpinBox *spinboxR;
    QSpinBox *spinboxG;
    QSpinBox *spinboxB;
    QSpinBox *spinboxA;
    QPushButton *btnPiksel;
    QPushButton *btnLinia;
    QPushButton *btnKolko;
    QPushButton *btnElipsa;
    QPushButton *btnKrzywe;
    QPushButton *btnBSpline;
    QPushButton *btnFloodFill;
    QPushButton *btnScanLine;
    QPushButton *btnTransform;
    QPushButton *btnWyczysc;
    Przycisk *btnFgColor;
    Przycisk *btnBgColor;
    Ekran *ekran;
    Tool *tool;
    Tool *toolPiksel;
    Tool *toolLinia;
    Tool *toolKolko;
    Tool *toolElipsa;
    Tool *toolKrzywe;
    Tool *toolBSpline;
    Tool *toolFloodFill;
    Tool *toolScanLine;
    Tool *toolTransform;

    QMenu *fileMenu;
        QAction *openAct;
    QMenu *morfMenu;
        QAction *erozjaAct;
        QAction *dylatacjaAct;

    QList<layer*> *warstwy;
    QListWidget *widgetWarstwy;
    QSpinBox *spinboxOpacity;
    QComboBox *wybierzTrybMieszania;
    QPushButton *btnDeleteLayer;
    QPushButton *btnLayerUp;
    QPushButton *btnLayerDown;
    QCheckBox *visibilityChbox;

};

#endif // MAINWINDOW_H
