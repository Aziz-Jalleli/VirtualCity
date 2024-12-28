#ifndef PRODUIREEAU_H
#define PRODUIREEAU_H

#include <QDialog>

namespace Ui {
class produireeau;
}

class produireeau : public QDialog
{
    Q_OBJECT

public:
    explicit produireeau(QWidget *parent = nullptr);
    ~produireeau();
    void populateUsines(const QStringList& UsineNames); // Populate ComboBox
    int getSelectedUsineIndex(); // Get selected house index

private:
    Ui::produireeau *ui;
};

#endif // PRODUIREEAU_H
