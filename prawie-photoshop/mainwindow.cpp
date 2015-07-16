#include "mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    createWindow();
    createBtns();
    createActions();
    createEkran();
    createLayers();
/*
 *   10.10.244.220/~rudy/qtloop1
 *
    QListWidgetItem *item = new QListWidgetItem("blablabla");
    item->setData(Qt::UserRole, QVariant(5));
    listWidget->insertItem(0,item);



    reakcjanaliste  (int index) {

        QListWidgetItem *item = ui->listWidget->item(index);
        QVariant v = item->data(Qt::UserRole);
        qDebug("%d", index);
        if (v.isValid()) {
            qDebug("Row data: %d", v.toInt());
        } else {
            qDebug("Row data: No data");
        }

    }
    */
}

MainWindow::~MainWindow()
{

}


void MainWindow::createWindow() {
    QDesktopWidget desktopwg;
    QRect windowsize = desktopwg.availableGeometry(desktopwg.primaryScreen());
    this->resize(windowsize.size());
    this->showMaximized();
    this->setWindowTitle("Prawie Photoshop :D");
}

void MainWindow::createEkran() {

    int ekranW, ekranH;
    ekranW = this->width()-300;
    ekranH = this->height()-80;

    warstwy = new QList<layer*>;
    layer::w = ekranW;
    layer::h = ekranH;

    warstwy->push_back(new layer("Podstawa"));
    layer *background = new layer("Tło");
    background->o->zamaluj();
    warstwy->push_back(background);

    Tool::setCurrentLayer(background);
    Tool::bufor = new Obraz(background->o);
    toolPiksel = new ToolPiksel();
    toolLinia = new ToolLinia();
    toolKolko = new ToolKolko();
    toolElipsa = new ToolElipsa();
    toolKrzywe = new ToolKrzywe();
    toolBSpline = new ToolBSpline();
    toolFloodFill = new ToolFloodFill();
    toolScanLine = new ToolScanLine();
    toolTransform = new ToolTransform();
    tool = toolTransform;
        btnTransform->setEnabled(false);
        btnTransform->repaint();

    ekran = new Ekran(this, &tool, warstwy);
    Tool::ekran = ekran;

    ekran->resize(ekranW,ekranH);
    ekran->move(130,40);

    ekran->show();
}

void MainWindow::createBtns()
{

    openAct = new QAction("&Otwórz...", this);
    openAct->setShortcuts(QKeySequence::Open);
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));


    fileMenu = menuBar()->addMenu("&Plik");
    fileMenu->addAction(openAct);


    erozjaAct = new QAction("&Erozja", this);
    connect(erozjaAct, SIGNAL(triggered()), this, SLOT(erozja()));

    dylatacjaAct = new QAction("&Dylatacja", this);
    connect(dylatacjaAct, SIGNAL(triggered()), this, SLOT(dylatacja()));


    morfMenu = menuBar()->addMenu("Przekształcenia morfologiczne");
    morfMenu->addAction(erozjaAct);
    morfMenu->addAction(dylatacjaAct);


    QWidget *layoutVbox = new QWidget(this);
    layoutV = new QVBoxLayout;

    btnPiksel = new QPushButton("Freeform");
    btnLinia = new QPushButton("Linia");
    btnKolko = new QPushButton("Okrąg");
    btnElipsa = new QPushButton("Elipsa");
    btnKrzywe = new QPushButton("Krzywe");
    btnBSpline = new QPushButton("BSpline");
    btnFloodFill = new QPushButton("FloodFill");
    btnScanLine = new QPushButton("ScanLine");
    btnTransform = new QPushButton("Transform");
    btnWyczysc = new QPushButton("Wyczyść");
    btnFgColor = new Przycisk(this, 50, 30, &(Kolory::fg));
    btnFgColor->update();
    btnBgColor = new Przycisk(this, 50, 30, &(Kolory::bg));
    btnBgColor->update();


    layoutV->addWidget(btnPiksel);
    layoutV->addWidget(btnLinia);
    layoutV->addWidget(btnKolko);
    layoutV->addWidget(btnElipsa);
    layoutV->addWidget(btnKrzywe);
    layoutV->addWidget(btnBSpline);
    layoutV->addWidget(btnFloodFill);
    layoutV->addWidget(btnScanLine);
 //   layoutV->addWidget(btnTransform);
    layoutV->addWidget(btnWyczysc);
    layoutV->addWidget(btnFgColor);
    layoutV->addWidget(btnBgColor);

    layoutVbox->setLayout(layoutV);
    layoutVbox->adjustSize();
    layoutVbox->setFixedWidth(100);
    layoutVbox->move(20,30);
    layoutVbox->show();


}

void MainWindow::createLayers()
{

    QWidget *layoutVbox2 = new QWidget(this);
    QVBoxLayout *layoutV2 = new QVBoxLayout;

    QLabel *labelOpacity = new QLabel("Przezroczystość:");

    QHBoxLayout *opacityContainer = new QHBoxLayout;
    spinboxOpacity = new QSpinBox(this);
    spinboxOpacity->setRange(0,100);
    spinboxOpacity->setSingleStep(1);
    spinboxOpacity->setValue(100);
    QLabel *labelProcent = new QLabel("%");
    opacityContainer->addWidget(spinboxOpacity);
    opacityContainer->addWidget(labelProcent);



    QLabel *labelBlendingMode = new QLabel("Tryb mieszania:");
    wybierzTrybMieszania = new QComboBox(this);
    wybierzTrybMieszania->addItem("Normal");
    wybierzTrybMieszania->addItem("Multiply");
    wybierzTrybMieszania->addItem("Screen");
    wybierzTrybMieszania->addItem("Overlay");
    wybierzTrybMieszania->addItem("Darken");
    wybierzTrybMieszania->addItem("Lighten");
    wybierzTrybMieszania->addItem("Difference");
    wybierzTrybMieszania->addItem("Add");
    wybierzTrybMieszania->addItem("Substract");
    wybierzTrybMieszania->addItem("Average");
    wybierzTrybMieszania->addItem("Negation");
    wybierzTrybMieszania->addItem("Exclusion");
    wybierzTrybMieszania->addItem("Soft light");

    QHBoxLayout *VisibilityContainer = new QHBoxLayout;
    QLabel *labelVisibility = new QLabel("Widoczność:");
    visibilityChbox = new QCheckBox(this);
    visibilityChbox->setChecked(true);
    VisibilityContainer->addWidget(labelVisibility);
    VisibilityContainer->addWidget(visibilityChbox);



    QLabel *labelLayers = new QLabel("Warstwy:");
    widgetWarstwy = new QListWidget(this);

    QListWidgetItem *item;
    for (int i = 1; i < warstwy->size(); ++i) {
        item = new QListWidgetItem(warstwy->at(i)->label);
        item->setData(Qt::UserRole, QVariant(warstwy->at(i)->id));
        widgetWarstwy->addItem(item);
    }
    widgetWarstwy->setCurrentRow(0);


    QHBoxLayout *layerOptionsContainer = new QHBoxLayout;
    QPushButton *btnAddLayer = new QPushButton("+");
    btnLayerUp = new QPushButton("Up");
    layerOptionsContainer->addWidget(btnAddLayer);
    layerOptionsContainer->addWidget(btnLayerUp);

    QHBoxLayout *layerOptionsContainer2 = new QHBoxLayout;
    btnDeleteLayer = new QPushButton("-");
    btnLayerDown = new QPushButton("Down");
    layerOptionsContainer2->addWidget(btnDeleteLayer);
    layerOptionsContainer2->addWidget(btnLayerDown);

    UpdateFields();



    layoutV2->addWidget(labelOpacity);
    layoutV2->addLayout(opacityContainer);
    layoutV2->addSpacing(15);
    layoutV2->addWidget(labelBlendingMode);
    layoutV2->addWidget(wybierzTrybMieszania);
    layoutV2->addSpacing(15);
    layoutV2->addLayout(VisibilityContainer);
    layoutV2->addSpacing(15);
    layoutV2->addWidget(labelLayers);
    layoutV2->addWidget(widgetWarstwy);
    layoutV2->addLayout(layerOptionsContainer);
    layoutV2->addLayout(layerOptionsContainer2);

    layoutVbox2->setLayout(layoutV2);
    layoutVbox2->adjustSize();
    layoutVbox2->setFixedWidth(140);
    layoutVbox2->move(width()-160,30);
    layoutVbox2->show();




    connect(widgetWarstwy, SIGNAL(currentRowChanged(int)), this, SLOT(ZmianaWarstwy()));
    connect(btnAddLayer, SIGNAL(clicked()), this, SLOT(DodajWarstwe()));
    connect(btnDeleteLayer, SIGNAL(clicked()), this, SLOT(UsunWarstwe()));
    connect(spinboxOpacity, SIGNAL(valueChanged(int)), this, SLOT(ZmienPrzezroczystosc(int)));
    connect(wybierzTrybMieszania, SIGNAL(currentIndexChanged(int)), this, SLOT(ZmianaTrybuMieszania(int)));
    connect(btnLayerUp, SIGNAL(clicked()), this, SLOT(ZmienKolejnoscWarstwUp()));
    connect(btnLayerDown, SIGNAL(clicked()), this, SLOT(ZmienKolejnoscWarstwDown()));
    connect(visibilityChbox, SIGNAL(toggled(bool)), this, SLOT(ZmienWidocznoscWarstwy(bool)));

}

void MainWindow::createActions()
{
    connect(btnPiksel, SIGNAL(clicked()), this, SLOT(Piksel()));
    connect(btnLinia, SIGNAL(clicked()), this, SLOT(Linia()));
    connect(btnKolko, SIGNAL(clicked()), this, SLOT(Kolko()));
    connect(btnElipsa, SIGNAL(clicked()), this, SLOT(Elipsa()));
    connect(btnKrzywe, SIGNAL(clicked()), this, SLOT(Krzywe()));
    connect(btnBSpline, SIGNAL(clicked()), this, SLOT(BSpline()));
    connect(btnFloodFill, SIGNAL(clicked()), this, SLOT(FloodFill()));
    connect(btnScanLine, SIGNAL(clicked()), this, SLOT(ScanLine()));
    connect(btnTransform, SIGNAL(clicked()), this, SLOT(Transform()));
    connect(btnWyczysc, SIGNAL(clicked()), this, SLOT(Wyczysc()));
}

void MainWindow::uncheckall()
{
    btnPiksel->setEnabled(true);
    btnPiksel->repaint();
    btnLinia->setEnabled(true);
    btnLinia->repaint();
    btnKolko->setEnabled(true);
    btnKolko->repaint();
    btnElipsa->setEnabled(true);
    btnElipsa->repaint();
    btnKrzywe->setEnabled(true);
    btnKrzywe->repaint();
    btnBSpline->setEnabled(true);
    btnBSpline->repaint();
    btnFloodFill->setEnabled(true);
    btnFloodFill->repaint();
    btnScanLine->setEnabled(true);
    btnScanLine->repaint();
    btnTransform->setEnabled(true);
    btnTransform->repaint();
}

void MainWindow::Piksel()
{
    uncheckall();
    btnPiksel->setEnabled(false);
    btnPiksel->repaint();
    tool->sprzatnij();
    tool = toolPiksel;
    update();
}
void MainWindow::Linia()
{
    uncheckall();
    btnLinia->setEnabled(false);
    btnLinia->repaint();
    tool->sprzatnij();
    tool = toolLinia;
    update();
}
void MainWindow::Kolko()
{
    uncheckall();
    btnKolko->setEnabled(false);
    btnKolko->repaint();
    tool->sprzatnij();
    tool = toolKolko;
    update();
}
void MainWindow::Elipsa()
{
    uncheckall();
    btnElipsa->setEnabled(false);
    btnElipsa->repaint();
    tool->sprzatnij();
    tool = toolElipsa;
    update();
}
void MainWindow::Krzywe()
{
    uncheckall();
    btnKrzywe->setEnabled(false);
    btnKrzywe->repaint();
    tool->sprzatnij();
    tool = toolKrzywe;
    update();
}
void MainWindow::BSpline()
{
    uncheckall();
    btnBSpline->setEnabled(false);
    btnBSpline->repaint();
    tool->sprzatnij();
    tool = toolBSpline;
    update();
}
void MainWindow::FloodFill()
{
    uncheckall();
    btnFloodFill->setEnabled(false);
    btnFloodFill->repaint();
    tool->sprzatnij();
    tool = toolFloodFill;
    update();
}
void MainWindow::ScanLine()
{
    uncheckall();
    btnScanLine->setEnabled(false);
    btnScanLine->repaint();
    tool->sprzatnij();
    tool = toolScanLine;
    update();
}
void MainWindow::Transform()
{
    uncheckall();
    btnTransform->setEnabled(false);
    btnTransform->repaint();
    tool->sprzatnij();
    tool = toolTransform;
    update();
}
void MainWindow::Wyczysc()
{
    tool->sprzatnij();
    if (Tool::currentLayer->id == 0)
        tool->przywroc();
    else
        tool->czysc();
    Tool::bufor->wklejObraz(Tool::obraz);
    update();
}

void MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Otwórz plik", "*.jpg");
    if (!fileName.isEmpty()) {
        DodajWarstwe();
        QImage *zdjecie = new QImage(fileName);
        Tool::obraz->wklejObraz(zdjecie);
        Tool::bufor->wklejObraz(Tool::obraz);
        ekran->update();
        delete zdjecie;
    }
}

void MainWindow::erozja()
{
    Tool::currentLayer->zrobErozje();
    update();
}

void MainWindow::dylatacja()
{
    Tool::currentLayer->zrobDylatacje();
    update();
}

void MainWindow::DodajWarstwe()
{

    int nowaId = warstwy->indexOf(Tool::currentLayer) + 1;
    layer *nowa = new layer();

    warstwy->insert(nowaId, nowa);

    QListWidgetItem *item = new QListWidgetItem(nowa->label);
    item->setData(Qt::UserRole, QVariant(nowa->id));

    widgetWarstwy->insertItem(widgetWarstwy->currentRow(), item);
    widgetWarstwy->setCurrentItem(item);
    UpdateFields();
    widgetWarstwy->repaint();

}

void MainWindow::ZmianaWarstwy()
{
    int id = widgetWarstwy->currentItem()->data(Qt::UserRole).toInt();

    layer *current = NULL;
    for (int i = 0; i < warstwy->size(); ++i) {
        if (warstwy->at(i)->id == id) {
            current = warstwy->at(i);
            break;
        }
    }

    if (current != NULL) {
        Tool::setCurrentLayer(current);
        UpdateFields();
    }

}

void MainWindow::UsunWarstwe()
{

    if (Tool::currentLayer->id > 0) {
        int wierszDoUsuniecia = widgetWarstwy->currentRow();
        int idWarstwyDoUsuniecia = widgetWarstwy->currentItem()->data(Qt::UserRole).toInt();
        QListWidgetItem *wiersz = widgetWarstwy->currentItem();
        widgetWarstwy->takeItem(wierszDoUsuniecia);
        widgetWarstwy->setCurrentRow(wierszDoUsuniecia);
        delete wiersz;

        layer *warstwaDoUsuniecia = NULL;
        for (int i = 0; i < warstwy->size(); ++i) {
            if (warstwy->at(i)->id == idWarstwyDoUsuniecia) {
                warstwaDoUsuniecia = warstwy->at(i);
                break;
            }
        }
        int indexWarstwyDoUsuniecia = warstwy->indexOf(warstwaDoUsuniecia);
        layer *nowaAktualnaWarstwa = warstwy->at(indexWarstwyDoUsuniecia-1);
        warstwy->removeOne(warstwaDoUsuniecia);
        Tool::setCurrentLayer(nowaAktualnaWarstwa);
        UpdateFields();

        ekran->update();
    }

}

void MainWindow::ZmienPrzezroczystosc(int x)
{
    Tool::currentLayer->opacity = x;
    ekran->update();
}

void MainWindow::ZmianaTrybuMieszania(int x)
{
    Tool::currentLayer->setBlendingModeId(x);
    ekran->update();
}
void MainWindow::UpdateFields()
{
    spinboxOpacity->setValue(Tool::currentLayer->opacity);
    wybierzTrybMieszania->setCurrentIndex(Tool::currentLayer->blendingModeId);

    visibilityChbox->setChecked( Tool::currentLayer->visibility() );

    btnLayerUp->setDisabled(true);
    btnLayerDown->setDisabled(true);

    int index = warstwy->indexOf( Tool::currentLayer );

    if (index > 2) {
        btnLayerDown->setDisabled(false);
    }
    if (index < warstwy->size()-1 && Tool::currentLayer->id > 0) {
        btnLayerUp->setDisabled(false);
    }

    if (Tool::currentLayer->id == 0){
        btnDeleteLayer->setDisabled(true);
        spinboxOpacity->setDisabled(true);
        wybierzTrybMieszania->setDisabled(true);
        visibilityChbox->setDisabled(true);
    } else {
        btnDeleteLayer->setDisabled(false);
        spinboxOpacity->setDisabled(false);
        wybierzTrybMieszania->setDisabled(false);
        visibilityChbox->setDisabled(false);
    }

}

void MainWindow::ZmienKolejnoscWarstwUp()
{
    ZmienKolejnoscWarstw(1);
}

void MainWindow::ZmienKolejnoscWarstwDown()
{
    ZmienKolejnoscWarstw(-1);
}

void MainWindow::ZmienKolejnoscWarstw(int x)
{
    int current = warstwy->indexOf( Tool::currentLayer );
    warstwy->move(current,current+x);

    current = widgetWarstwy->currentRow();
    QListWidgetItem *item = widgetWarstwy->takeItem(current);
    widgetWarstwy->insertItem(current-x, item);
    widgetWarstwy->setCurrentItem(item);
    widgetWarstwy->repaint();

    ekran->update();
}

void MainWindow::ZmienWidocznoscWarstwy(bool v)
{
    Tool::currentLayer->setVisible(v);
    update();
}
