#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QPixmap>
//#include <QtSql/QSql>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    QPixmap pix(":/img/Logo.jpg");
    int w = ui->label_Logo->width();
    int h = ui->label_Logo->height();
    ui->label_Logo->setPixmap(pix.scaled(w,h, Qt::KeepAspectRatio));
    //ui->label_Logo->setPixmap(pix);
    try{
    Connection::init_and_start_connection("172.16.39.93", 5520);
    }catch(char const* error){
        QMessageBox::information(nullptr, "Connerction error", error);
        exit(0);
    }

    this->setStyleSheet("background-color: #121313;");
    ui->groupBox->setStyleSheet("color: white");
    ui->groupBox_2->setStyleSheet("color: white");
    ui->ToRegisterBTN->setStyleSheet("color: white");
    ui->ToSignIn->setStyleSheet("color: white");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loginBTN_clicked()
{
    QString username = ui->userIN->text();
    QString password = ui->passwIN->text();
    int Status=0;
    Connection::send_login(username.toStdString(), password.toStdString(), Status);

    if(Status==1){
        hide();
        startMenuWindow = new StartMenuWindow();
        startMenuWindow->show();
    }
}


void MainWindow::on_ToSignIn_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_ToRegisterBTN_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_CreateAccBTN_clicked()
{
    std::string email = ui->emailRegisterIN->text().toStdString();
    std::string username = ui->usenameRegisterIN->text().toStdString();
    std::string passw1 = ui->Password1IN->text().toStdString();
    std::string passw2 = ui->password2IN->text().toStdString();

    int Status=0;
    Connection::send_register(email, username, passw1, Status);

    if(Status==1){
        QMessageBox::information(nullptr, "Account created", "Now please login \nin your new account!:)");
        ui->stackedWidget->setCurrentIndex(0);
        ui->ToRegisterBTN->hide();
        // hide();
        // startMenuWindow = new StartMenuWindow();
        // startMenuWindow->show();
    }
}

