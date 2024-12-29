#include "createparc.h"
#include "ui_createparc.h"

createparc::createparc(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::createparc)
{
    ui->setupUi(this);
}

createparc::~createparc()
{
    delete ui;
}
