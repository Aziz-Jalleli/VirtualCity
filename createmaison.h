#ifndef CREATEMAISON_H
#define CREATEMAISON_H

#include <QDialog>

namespace Ui {
class createmaison;
}

class createmaison : public QDialog
{
    Q_OBJECT

public:
    explicit createmaison(QWidget *parent = nullptr);
    ~createmaison();

private:
    Ui::createmaison *ui;
};

#endif // CREATEMAISON_H
