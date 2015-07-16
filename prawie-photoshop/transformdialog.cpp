#include "transformdialog.h"
#include "ui_transformdialog.h"

TransformDialog::TransformDialog(Punkt A, Punkt B, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TransformDialog)
{
    ui->setupUi(this);

    if (A.x > B.x)
        A.swapX(&B);
    if (A.y > B.y)
        A.swapY(&B);



}

TransformDialog::~TransformDialog()
{
    delete ui;
}
