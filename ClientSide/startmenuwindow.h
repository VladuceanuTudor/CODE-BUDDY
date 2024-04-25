#ifndef STARTMENUWINDOW_H
#define STARTMENUWINDOW_H

#include <QDialog>
#include "ServerConnection.h"

namespace Ui {
class StartMenuWindow;
}

class StartMenuWindow : public QDialog
{
    Q_OBJECT

public:
    explicit StartMenuWindow(QWidget *parent = nullptr);
    ~StartMenuWindow();

private slots:
    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_clicked();

    void onLessonButtonClicked(const QString& buttonText, CLimbaj* limbaj);

    void printLimbajLessonsMenu(CLimbaj* limbaj);

    void displayLectie_Exercitii(ILectie* lectie, std::string numeLectie);

private:
    Ui::StartMenuWindow *ui;
};

#endif // STARTMENUWINDOW_H
