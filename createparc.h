#ifndef CREATEPARC_H
#define CREATEPARC_H

#include <QDialog>

namespace Ui {
class createparc;
}

class createparc : public QDialog
{
    Q_OBJECT

public:
    explicit createparc(QWidget *parent = nullptr);
    ~createparc();

private:
    Ui::createparc *ui;
};

#endif // CREATEPARC_H
