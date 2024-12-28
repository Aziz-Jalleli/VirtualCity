#include "produireelectricite.h"
#include "ui_produireelectricite.h"

produireelectricite::produireelectricite(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::produireelectricite)
{
    ui->setupUi(this);
}

produireelectricite::~produireelectricite()
{
    delete ui;
}
void produireelectricite::populateUsines(const QStringList& UsineNames) {
    ui->comboBox->clear();
    ui->comboBox->addItems(UsineNames);
}

int produireelectricite::getSelectedUsineIndex() {
    return ui->comboBox->currentIndex();
}
