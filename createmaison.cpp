#include "createmaison.h"
#include "ui_createmaison.h"

createmaison::createmaison(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::createmaison)
{
    ui->setupUi(this);

    Maison createMaison();
}

createmaison::~createmaison()
{
    delete ui;
}
Maison createmaison::createMaison()
{
    // Extract data from input fields
    QString name = ui->lineEdit->text();
    int capacity = ui->spinBox->value();
    // Create a new Maison object using the input data
    Maison newMaison(0,name, capacity);

    return newMaison;
}

