#ifndef PRODUIREELECTRICITE_H
#define PRODUIREELECTRICITE_H

#include <QDialog>

namespace Ui {
class produireelectricite;
}

class produireelectricite : public QDialog
{
    Q_OBJECT

public:
    explicit produireelectricite(QWidget *parent = nullptr);
    ~produireelectricite();
    void populateUsines(const QStringList& UsineNames); // Populate ComboBox
    int getSelectedUsineIndex(); // Get selected house indexs
private:
    Ui::produireelectricite *ui;
};

#endif // PRODUIREELECTRICITE_H
