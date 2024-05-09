#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "startmenuwindow.h"

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

    void on_loginBTN_clicked();

    void on_ToSignIn_clicked();

    void on_ToRegisterBTN_clicked();

    void on_CreateAccBTN_clicked();

    void on_passwIN_returnPressed();

    void on_userIN_returnPressed();

private:
    Ui::MainWindow *ui;
    StartMenuWindow* startMenuWindow;
};
#endif // MAINWINDOW_H
