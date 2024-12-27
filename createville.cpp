#include "createville.h"
#include "ui_createville.h"

createville::createville(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::createville)
{
    ui->setupUi(this);
}

createville::~createville()
{
    delete ui;
}
