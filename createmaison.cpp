#include "createmaison.h"
#include "ui_createmaison.h"

createmaison::createmaison(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::createmaison)
{
    ui->setupUi(this);
}

createmaison::~createmaison()
{
    delete ui;
}
