#ifndef CREATEUSINE_H
#define CREATEUSINE_H

#include <QDialog>

namespace Ui {
class createusine;
}

class createusine : public QDialog
{
    Q_OBJECT

public:
    explicit createusine(QWidget *parent = nullptr);
    ~createusine();

private:
    Ui::createusine *ui;
};

#endif // CREATEUSINE_H
