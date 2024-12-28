#include "createusine.h"
#include "ui_createusine.h"

createusine::createusine(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::createusine)
{
    ui->setupUi(this);
}

createusine::~createusine()
{
    delete ui;
}
