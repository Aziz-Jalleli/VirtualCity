#ifndef ADDHABITANT_H
#define ADDHABITANT_H

#include <QDialog>

namespace Ui {
class addhabitant;
}

class addhabitant : public QDialog
{
    Q_OBJECT

public:
    explicit addhabitant(QWidget *parent = nullptr);
    ~addhabitant();
    void populateHouses(const QStringList& houseNames); // Populate ComboBox
    int getSelectedHouseIndex(); // Get selected house index
    int getHabitants(); // Get number of habitants


private:
    Ui::addhabitant *ui;
};

#endif // ADDHABITANT_H
