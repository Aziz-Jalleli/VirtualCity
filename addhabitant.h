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
    int getHabitants() const;

private:
    Ui::addhabitant *ui;
};

#endif // ADDHABITANT_H
