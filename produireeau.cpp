#include "produireeau.h"
#include "ui_produireeau.h"

produireeau::produireeau(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::produireeau)
{
    ui->setupUi(this);
}

produireeau::~produireeau()
{
    delete ui;
}
void produireeau::populateUsines(const QStringList& UsineNames) {
    ui->comboBox->clear();
    ui->comboBox->addItems(UsineNames);
}

int produireeau::getSelectedUsineIndex() {
    return ui->comboBox->currentIndex();
}
