#include "addhabitant.h"
#include "ui_addhabitant.h"

addhabitant::addhabitant(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::addhabitant)
{
    ui->setupUi(this);
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);

    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

}

addhabitant::~addhabitant()
{
    delete ui;
}
int addhabitant::getHabitants()
{
    return ui->spinBox->value(); // Retrieve the value from the QSpinBox
}
void addhabitant::populateHouses(const QStringList& houseNames) {
    ui->comboBox->clear();
    ui->comboBox->addItems(houseNames);
}

int addhabitant::getSelectedHouseIndex() {
    return ui->comboBox->currentIndex();
}
