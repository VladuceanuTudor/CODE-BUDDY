#ifndef STARTMENUWINDOW_H
#define STARTMENUWINDOW_H

#include <QDialog>
#include "leaderboard.h"
#include "Utils.h"
#include <QListWidgetItem>
#include <QThread>
#include "uithread.h"


namespace Ui {
class StartMenuWindow;
}

class StartMenuWindow : public QDialog
{
    Q_OBJECT

public:
    explicit StartMenuWindow(QWidget *parent = nullptr);
    ~StartMenuWindow();
    std::string myUserName;
    QThread* chat_thread;

private slots:
    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_clicked();

    void onLessonButtonClicked(const QString& buttonText, CLimbaj* limbaj);

    void printLimbajLessonsMenu(CLimbaj* limbaj);

    void displayLectie_Exercitii(ILectie* lectie, std::string numeLectie, CLimbaj* limbaj);

    void on_pushButton_2_clicked();

    QWidget* createExerciseWidget(IExercitiu* ex);

    void finalizeLectia(ILectie* lectie, CLimbaj* limbaj, std::string numeLectie);

    void on_pushButton_7_clicked();

    void on_pushButton_3_clicked();
    void on_pushButton_8_clicked();
    void onListItemClicked(QListWidgetItem *item);

    void on_AdaugaPrietenBTN_clicked();

private:
    Ui::StartMenuWindow *ui;

};

#endif // STARTMENUWINDOW_H
