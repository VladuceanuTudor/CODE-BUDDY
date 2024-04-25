/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *loginSCREEN;
    QLabel *labelParagraf;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *labelUser;
    QLineEdit *userIN;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelPassw;
    QLineEdit *passwIN;
    QPushButton *loginBTN;
    QPushButton *ToRegisterBTN;
    QWidget *page_2;
    QGroupBox *groupBox_2;
    QLabel *label_2;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *labelEmailRegister;
    QLineEdit *emailRegisterIN;
    QHBoxLayout *horizontalLayout_5;
    QLabel *labelUsernameRegister;
    QLineEdit *usenameRegisterIN;
    QHBoxLayout *horizontalLayout_7;
    QLabel *labelPassword2;
    QLineEdit *password2IN;
    QHBoxLayout *horizontalLayout_6;
    QLabel *labelPassword1;
    QLineEdit *Password1IN;
    QPushButton *CreateAccBTN;
    QPushButton *ToSignIn;
    QLabel *label_Logo;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1063, 763);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        loginSCREEN = new QWidget(centralwidget);
        loginSCREEN->setObjectName("loginSCREEN");
        loginSCREEN->setGeometry(QRect(30, 70, 1021, 601));
        loginSCREEN->setStyleSheet(QString::fromUtf8(""));
        labelParagraf = new QLabel(loginSCREEN);
        labelParagraf->setObjectName("labelParagraf");
        labelParagraf->setGeometry(QRect(70, 360, 501, 151));
        labelParagraf->setStyleSheet(QString::fromUtf8("font: 10pt \"Segoe Print\";\n"
"color: white"));
        labelParagraf->setWordWrap(true);
        stackedWidget = new QStackedWidget(loginSCREEN);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(620, 60, 341, 431));
        page = new QWidget();
        page->setObjectName("page");
        groupBox = new QGroupBox(page);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(80, 100, 228, 191));
        groupBox->setStyleSheet(QString::fromUtf8(""));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        labelUser = new QLabel(groupBox);
        labelUser->setObjectName("labelUser");

        horizontalLayout->addWidget(labelUser);

        userIN = new QLineEdit(groupBox);
        userIN->setObjectName("userIN");

        horizontalLayout->addWidget(userIN);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        labelPassw = new QLabel(groupBox);
        labelPassw->setObjectName("labelPassw");

        horizontalLayout_2->addWidget(labelPassw);

        passwIN = new QLineEdit(groupBox);
        passwIN->setObjectName("passwIN");
        passwIN->setEchoMode(QLineEdit::Password);

        horizontalLayout_2->addWidget(passwIN);


        verticalLayout->addLayout(horizontalLayout_2);

        loginBTN = new QPushButton(groupBox);
        loginBTN->setObjectName("loginBTN");

        verticalLayout->addWidget(loginBTN);

        ToRegisterBTN = new QPushButton(page);
        ToRegisterBTN->setObjectName("ToRegisterBTN");
        ToRegisterBTN->setGeometry(QRect(150, 300, 101, 29));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        groupBox_2 = new QGroupBox(page_2);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(30, 70, 281, 301));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 110, 63, 20));
        layoutWidget = new QWidget(groupBox_2);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(20, 70, 243, 179));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        labelEmailRegister = new QLabel(layoutWidget);
        labelEmailRegister->setObjectName("labelEmailRegister");

        horizontalLayout_4->addWidget(labelEmailRegister);

        emailRegisterIN = new QLineEdit(layoutWidget);
        emailRegisterIN->setObjectName("emailRegisterIN");

        horizontalLayout_4->addWidget(emailRegisterIN);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        labelUsernameRegister = new QLabel(layoutWidget);
        labelUsernameRegister->setObjectName("labelUsernameRegister");

        horizontalLayout_5->addWidget(labelUsernameRegister);

        usenameRegisterIN = new QLineEdit(layoutWidget);
        usenameRegisterIN->setObjectName("usenameRegisterIN");

        horizontalLayout_5->addWidget(usenameRegisterIN);


        verticalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        labelPassword2 = new QLabel(layoutWidget);
        labelPassword2->setObjectName("labelPassword2");

        horizontalLayout_7->addWidget(labelPassword2);

        password2IN = new QLineEdit(layoutWidget);
        password2IN->setObjectName("password2IN");
        password2IN->setEchoMode(QLineEdit::Password);

        horizontalLayout_7->addWidget(password2IN);


        verticalLayout_2->addLayout(horizontalLayout_7);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        labelPassword1 = new QLabel(layoutWidget);
        labelPassword1->setObjectName("labelPassword1");

        horizontalLayout_6->addWidget(labelPassword1);

        Password1IN = new QLineEdit(layoutWidget);
        Password1IN->setObjectName("Password1IN");
        Password1IN->setEchoMode(QLineEdit::Password);

        horizontalLayout_6->addWidget(Password1IN);


        verticalLayout_2->addLayout(horizontalLayout_6);

        CreateAccBTN = new QPushButton(layoutWidget);
        CreateAccBTN->setObjectName("CreateAccBTN");

        verticalLayout_2->addWidget(CreateAccBTN);

        ToSignIn = new QPushButton(page_2);
        ToSignIn->setObjectName("ToSignIn");
        ToSignIn->setGeometry(QRect(130, 380, 83, 29));
        stackedWidget->addWidget(page_2);
        label_Logo = new QLabel(loginSCREEN);
        label_Logo->setObjectName("label_Logo");
        label_Logo->setGeometry(QRect(130, 70, 421, 321));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1063, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        labelParagraf->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"justify\"><br/>Descoper\304\203 CODE BUDDY, un loc vibrant pentru a-\310\233i dezvolta abilit\304\203\310\233ile de programare! Lec\310\233ii interactive, realiz\304\203ri \310\231i o comunitate pasionat\304\203 te a\310\231teapt\304\203 s\304\203 transformi codul \303\256n creativitate. Aventura \303\256ncepe acum!</p></body></html>", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "SignIn", nullptr));
        labelUser->setText(QCoreApplication::translate("MainWindow", "email:", nullptr));
        labelPassw->setText(QCoreApplication::translate("MainWindow", "Password:", nullptr));
        loginBTN->setText(QCoreApplication::translate("MainWindow", "Login", nullptr));
        ToRegisterBTN->setText(QCoreApplication::translate("MainWindow", "TO Register", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "SingUp", nullptr));
        label_2->setText(QString());
        labelEmailRegister->setText(QCoreApplication::translate("MainWindow", "email:", nullptr));
        labelUsernameRegister->setText(QCoreApplication::translate("MainWindow", "username:", nullptr));
        labelPassword2->setText(QCoreApplication::translate("MainWindow", "password:", nullptr));
        labelPassword1->setText(QCoreApplication::translate("MainWindow", "password check:", nullptr));
        CreateAccBTN->setText(QCoreApplication::translate("MainWindow", "Create Account", nullptr));
        ToSignIn->setText(QCoreApplication::translate("MainWindow", "To SingIN", nullptr));
        label_Logo->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
