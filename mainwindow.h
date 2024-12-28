#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"Maison.h"
#include"ville.h"
#include"usine.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Create_Maison_clicked();

    void on_Ajouter_Habitant_clicked();

    void on_Create_Ville_clicked();

    void on_Create_Usine_clicked();

    void on_Produire_eau_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::MainWindow *ui;
    std::shared_ptr<Maison> m1;
    std::shared_ptr<Ville> v1;
    std::shared_ptr<usine> u1;
};
#endif // MAINWINDOW_H
