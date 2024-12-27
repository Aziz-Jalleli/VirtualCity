#include "afficherdetails.h"
#include "ui_afficherdetails.h"

Afficherdetails::Afficherdetails(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Afficherdetails)
{
    ui->setupUi(this);
}

Afficherdetails::~Afficherdetails()
{
    delete ui;
}
void Afficherdetails::setDetails(const QString &details) {
    ui->textBrowser->setText(details); // Ensure `textBrowser` is added in the .ui file
}
