#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "paymentdialog.h"
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
    Connection::init_and_start_connection("25.16.102.33", 5520);
    }catch(char const* error){
        QMessageBox::information(nullptr, "Connection error", error);
        exit(0);
    }

    this->setStyleSheet("background-color: #121313;");
    ui->groupBox->setStyleSheet("color: white");
    ui->groupBox_2->setStyleSheet("color: white");
    ui->ToRegisterBTN->setStyleSheet("color: white");
    ui->ToSignIn->setStyleSheet("color: white");
    this->setWindowTitle("Log-in CODE BUDDY");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loginBTN_clicked()
{
    QString username = ui->userIN->text();
    QString password = ui->passwIN->text();

    int correctness = loginCorectnessCheck(username.toStdString(), password.toStdString());
    //for admin bypass
    if(username.toStdString()=="a")correctness=0;
    switch (correctness){
    case 1:
        QMessageBox::information(nullptr, "Incorect email", "Please type a valid email address!");
        return;
    case 2:
        QMessageBox::information(nullptr, "Incorect password", "The password may only contain alphanumeric caracters!");
        return;
    default:
        break;
    }
    int Status=0;
    std::string aux_username;
    Connection::send_login(username.toStdString(), password.toStdString(), Status, aux_username);
    if(Status==1){
        hide();
        startMenuWindow = new StartMenuWindow();
        startMenuWindow->myUserName=aux_username;
        startMenuWindow->show();
        static int iter=0;
        if(iter++ == 0)
            Connection::initChat(aux_username);
    }else if(Status == 2){
        hide();
        premium=true;
        startMenuWindow = new StartMenuWindow();
        startMenuWindow->myUserName=aux_username;
        startMenuWindow->show();
        static int iter=0;
        if(iter++ == 0)
            Connection::initChat(aux_username);
    }else{
        QMessageBox::information(nullptr, "Login failed", "Incorect credentials used!");
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
    int correctness = registerCorectnessCheck(email, username, passw1, passw2);
    switch(correctness){
    case 1:
        QMessageBox::information(nullptr, "Incorect password", "The first and second password don't match!");
        return;
    case 2:
        QMessageBox::information(nullptr, "Incorect email", "Please type a valid email address!");
        return;
    case 3:
        QMessageBox::information(nullptr, "Incorect username", "The username may only contain alphanumeric caracters or _ !");
        return;
    case 4:
        QMessageBox::information(nullptr, "Incorect password", "The password may only contain alphanumeric caracters!");
        return;
    default:
        break;
    }
    int Status=0;
    Connection::send_register(email, username, passw1, Status);

    if(Status==1){
        QMessageBox::information(nullptr, "Account created", "Now please login \nin your new account!:)");
        ui->stackedWidget->setCurrentIndex(0);
        ui->ToRegisterBTN->hide();
        // hide();
        // startMenuWindow = new StartMenuWindow();
        // startMenuWindow->show();
    }else if (Status==2){
        QMessageBox::information(nullptr, "Register failed!", "This username is already in use!");
    }else if (Status==3){
        QMessageBox::information(nullptr, "Register failed!", "This email is already in use!");
    }else{
        QMessageBox::information(nullptr, "Register failed!", "Server error!");
    }
}


void MainWindow::on_passwIN_returnPressed()
{
    MainWindow::on_loginBTN_clicked();
}


void MainWindow::on_userIN_returnPressed()
{
    MainWindow::on_loginBTN_clicked();
}

