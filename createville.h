#ifndef CREATEVILLE_H
#define CREATEVILLE_H

#include <QDialog>

namespace Ui {
class createville;
}

class createville : public QDialog
{
    Q_OBJECT

public:
    explicit createville(QWidget *parent = nullptr);
    ~createville();

private:
    Ui::createville *ui;
};

#endif // CREATEVILLE_H
