#include "tooltransform.h"

ToolTransform::ToolTransform()
{
    jestZaznaczenie = false;
    angle1 = 0;
    angle2 = 0;
    otoczenie = 3;
    operacja = UNDEFINED;
    tlo = Kolory::bg;
    transparent = new QColor(255,255,255,0);
}

void ToolTransform::press(QMouseEvent *e)
{

    // JEŚLI NIE MA ZAZNACZENIA: zapisz punkt startowy
    if (!jestZaznaczenie) {
        A.x = e->x();
        A.y = e->y();
        PunktyKontrolne.clear();
        bufor->wklejObraz(obraz);
        if (Tool::currentLayer->id == 0)
            tlo = Kolory::bg;
        else
            tlo = transparent;
    }

    // JEŚLI JEST ZAZNACZENIE:
    else {
        if (!PunktyKontrolne.empty()) {

            Punkt *G = new Punkt;
            G->x = e->x();
            G->y = e->y();

            // a) jeśli klikam na punkt kontrolny - SKALOWANIE
            for (int i = 0; i < PunktyKontrolne.size(); ++i) {
                if (wOtoczeniu(&(PunktyKontrolne.at(i)), G)) {
                    operacja = SKALOWANIE;
                    break;
                }
            }

            // b) jeśli klikam poza punkt kontrolny

            //    i)  jeśli klikam wewnątrz zaznaczenia - TRANSLACJA
            if (operacja == UNDEFINED &&
                G->x >= A.x &&
                G->x <= B.x &&
                G->y >= A.y &&
                G->y <= B.y
            ) {
                operacja = TRANSLACJA;
            }

            //    ii) jeśli klikam poza zaznaczeniem:
            //          I)  jeśli było przesunięcie - ROTACJA
            //          II) jeśli nie było przesunięcia - koniec
            // ...

            delete G;
        }

    // zapisz punkt początkowy operacji
        AA.x = e->x();
        AA.y = e->y();

    }
}

void ToolTransform::move(QMouseEvent *e)
{
    obraz->wklejObraz(bufor);
    // JEŚLI NIE MA ZAZNACZENIA:
    if (!jestZaznaczenie) {
        // rysuj tymczasowe zaznaczenie
        B.x = e->x();
        B.y = e->y();
        rysujZaznaczenie();
    }

    // JEŚLI JEST ZAZNACZENIE:
    else {
        BB.x = e->x();
        BB.y = e->y();

        if (operacja == UNDEFINED)
            operacja = ROTACJA;

    // wykonaj wybraną operację
        wykonajOperacje();
    // otocz ją Zaznaczeniem Końcowym
     //   rysujZaznaczenieKoncowe();
    // narysuj Zaznaczenie Początkowe dla porównania
        //rysujZaznaczenie();
    }
}

void ToolTransform::release(QMouseEvent *e)
{
    if (!jestZaznaczenie) {
        // JEŚLI NIE MA ZAZNACZENIA:
        // zapisz punkt końcowty zaznaczenia
        B.x = e->x();
        B.y = e->y();

        if (A.x > B.x)
            A.swapX(&B);
        if (A.y > B.y)
            A.swapY(&B);

        // zapisz punkty kontrolne na jakąś listę
        /*
         0  1  2
         7     3
         6  5  4
         */

        PunktyKontrolne.push_back(Punkt(A)); //0
        PunktyKontrolne.push_back(Punkt((A.x + B.x)/2, A.y)); //1
        PunktyKontrolne.push_back(Punkt(B.x, A.y)); //2
        PunktyKontrolne.push_back(Punkt(B.x, (A.y + B.y)/2)); //3
        PunktyKontrolne.push_back(Punkt(B.x, B.y)); //4
        PunktyKontrolne.push_back(Punkt((A.x + B.x)/2, B.y)); //5
        PunktyKontrolne.push_back(Punkt(A.x, B.y)); //6
        PunktyKontrolne.push_back(Punkt(A.x, (A.y + B.y)/2)); //7

        // zapisz punkt środkowy
        // ...

        // rysuj zaznaczenie końcowe
        rysujZaznaczenieKoncowe();

        jestZaznaczenie = true;
    }

    else {

        if (operacja == UNDEFINED) {
            // zapisz transformację do obrazu
            obraz->wklejObraz(bufor);
            // obraz po transformacji
            if (!PunktyKontrolne.empty())
                PunktyKontrolne.clear();
            bufor->wklejObraz(obraz);
            jestZaznaczenie = false;
        }
        operacja = UNDEFINED;

        A.x += BB.x-AA.x;
        A.y += BB.y-AA.y;
        B.x += BB.x-AA.x;
        B.y += BB.y-AA.y;

      //  jestZaznaczenie = false;
    }
}

void ToolTransform::rysujZaznaczenie()
{

    Punkt Od(A);
    Punkt Do(B);

    if (A.x > B.x)
        Od.swapX(&Do);
    if (A.y > B.y)
        Od.swapY(&Do);



    for (int x = Od.x; x <= Do.x; ) {
        for (int j = 0; j < 5 && x <= Do.x; ++j, ++x) {
            obraz->rysujPiksel2(x,Od.y,Qt::white);
            obraz->rysujPiksel2(x,Do.y,Qt::white);
        }
        for (int j = 0; j < 5 && x <= Do.x; ++j, ++x) {
            obraz->rysujPiksel2(x,Od.y,Qt::black);
            obraz->rysujPiksel2(x,Do.y,Qt::black);
        }
    }


    for (int y = Od.y; y <= Do.y; ) {
        for (int j = 0; j < 5 && y <= Do.y; ++j, ++y) {
            obraz->rysujPiksel2(Od.x,y,Qt::white);
            obraz->rysujPiksel2(Do.x,y,Qt::white);
        }
        for (int j = 0; j < 5 && y <= Do.y; ++j, ++y) {
            obraz->rysujPiksel2(Od.x,y,Qt::black);
            obraz->rysujPiksel2(Do.x,y,Qt::black);
        }
    }

}

void ToolTransform::rysujZaznaczenieKoncowe()
{

    obraz->wklejObraz(bufor);

    Punkt Od(A);
    Punkt Do(B);

    if (Od.x > Do.x)
        Od.swapX(&Do);
    if (Od.y > Do.y)
        Od.swapY(&Do);

    for (int x = Od.x; x <= Do.x; ++x) {
        obraz->rysujPiksel2(x,Od.y,Qt::black);
        obraz->rysujPiksel2(x,Do.y,Qt::black);
    }

    for (int y = Od.y; y <= Do.y; ++y) {
        obraz->rysujPiksel2(Od.x,y,Qt::black);
        obraz->rysujPiksel2(Do.x,y,Qt::black);
    }

    // narysuj punkty od transformacji
    rysujPunkty();
}

void ToolTransform::rysujPunkty()
{
    for (int i = 0; i < PunktyKontrolne.size(); ++i)
        rysujPunkt(&PunktyKontrolne[i]);
}

void ToolTransform::rysujPunkt(const Punkt *P)
{
    short x = P->x - otoczenie;
    short y = P->y - otoczenie;
    short srednica = otoczenie*2;
    for (short i = 0; i < srednica; ++i) {
        for (short j = 0; j < srednica; ++j) {
            rysujPiksel(x+i,y+j,QColor(0,0,0));
        }
    }
}

bool ToolTransform::wOtoczeniu(const Punkt *A, Punkt *O)
{
    if (    A->x <= O->x + otoczenie
         && A->x >= O->x - otoczenie
         && A->y <= O->y + otoczenie
         && A->y >= O->y - otoczenie
       )
        return true;
    return false;
}

void ToolTransform::wykonajOperacje()
{
    obraz->wklejObraz(bufor);
    switch (operacja) {
        case TRANSLACJA: translacja(); break;
        case ROTACJA: rotacja(); break;
        case SKALOWANIE: skalowanie(); break;
        default: break;
    }
}

void ToolTransform::skalowanie()
{

}

void ToolTransform::translacja()
{
    Punkt roznica(BB.x-AA.x, BB.y-AA.y);


    for (int x = A.x; x <= B.x; ++x) {
        for (int y = A.y; y <= B.y; ++y) {
            obraz->rysujPiksel(x,y,*tlo);
        }
    }
    for (int x = A.x; x <= B.x; ++x) {
        for (int y = A.y; y <= B.y; ++y) {
            QColor L = QColor(bufor->getColor(x,y));
            QColor B = QColor(obraz->getColor(x+roznica.x,y+roznica.y));

            QColor g(0,0,0);
            g.setRed( blend_normal(B.red(), L.red(), (double) L.alpha() / 255.0));
            g.setGreen( blend_normal(B.green(), L.green(), (double) L.alpha() / 255.0));
            g.setBlue( blend_normal(B.blue(), L.blue(), (double) L.alpha() / 255.0));
            g.setAlpha( (double) L.alpha() / 255.0 + (double) B.alpha() / 255.0 * (1.0 - (double) L.alpha() / 255.0) );

            obraz->rysujPiksel(x+roznica.x,y+roznica.y, g);
        }
    }
}

void ToolTransform::rotacja()
{

}

void ToolTransform::sprzatnij()
{
    // ustaw poczatkowy kąt
    // zrób że nie ma zaznaczenia
    jestZaznaczenie = false;
    angle1 = 0;
    angle2 = 0;
    PunktyKontrolne.clear();
    operacja = UNDEFINED;
}

