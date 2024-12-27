#ifndef AFFICHERDETAILS_H
#define AFFICHERDETAILS_H

#include <QDialog>

namespace Ui {
class Afficherdetails;
}

class Afficherdetails : public QDialog
{
    Q_OBJECT

public:
    explicit Afficherdetails(QWidget *parent = nullptr);
    ~Afficherdetails();
    void setDetails(const QString &details);
private:
    Ui::Afficherdetails *ui;
};

#endif // AFFICHERDETAILS_H
