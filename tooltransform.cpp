#include "tooltransform.h"

ToolTransform::ToolTransform()
{
    jestZaznaczenie = false;
}

void ToolTransform::press(QMouseEvent *e)
{
    if (!jestZaznaczenie)
        bufor->wklejObraz(obraz);
    A.x = e->x();
    A.y = e->y();

}

void ToolTransform::move(QMouseEvent *e)
{
    if (jestZaznaczenie)
    {
        obraz->wklejObraz(bufor);
        jestZaznaczenie = false;
    }

        B.x = e->x();
        B.y = e->y();
        obraz->wklejObraz(bufor);
        rysujZaznaczenie();
}

void ToolTransform::release(QMouseEvent *e)
{
    if (jestZaznaczenie)
    {
        obraz->wklejObraz(bufor);
        jestZaznaczenie = false;
    }
    else
    {
        rysujZaznaczenieKoncowe();
        jestZaznaczenie = true;
        TransformDialog *dialog = new TransformDialog(A, B, Tool::ekran);
        if (dialog->exec() == QDialog::Accepted) {
        }
        delete dialog;
    }
}

void ToolTransform::sprzatnij()
{
    obraz->wklejObraz(bufor);
    jestZaznaczenie = false;
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
}
