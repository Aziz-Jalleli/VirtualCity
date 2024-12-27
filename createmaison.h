#ifndef CREATEMAISON_H
#define CREATEMAISON_H

#include <QDialog>
#include "Maison.h"

namespace Ui {
class createmaison;
}

class createmaison : public QDialog
{
    Q_OBJECT

public:
    explicit createmaison(QWidget *parent = nullptr);
     Maison createMaison();
    ~createmaison();

private:
    Ui::createmaison *ui;
};

#endif // CREATEMAISON_H
