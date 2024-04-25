/********************************************************************************
** Form generated from reading UI file 'startmenuwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STARTMENUWINDOW_H
#define UI_STARTMENUWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StartMenuWindow
{
public:
    QGroupBox *menuNavbar;
    QLabel *label;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QGroupBox *LanguageSelectMenu;
    QStackedWidget *stackedWidget;
    QWidget *ChoicePage;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QWidget *Language1Page;

    void setupUi(QDialog *StartMenuWindow)
    {
        if (StartMenuWindow->objectName().isEmpty())
            StartMenuWindow->setObjectName("StartMenuWindow");
        StartMenuWindow->resize(1094, 780);
        menuNavbar = new QGroupBox(StartMenuWindow);
        menuNavbar->setObjectName("menuNavbar");
        menuNavbar->setGeometry(QRect(0, 10, 1051, 80));
        label = new QLabel(menuNavbar);
        label->setObjectName("label");
        label->setGeometry(QRect(880, 30, 91, 20));
        layoutWidget = new QWidget(menuNavbar);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(20, 30, 431, 31));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName("pushButton");

        horizontalLayout_2->addWidget(pushButton);

        pushButton_2 = new QPushButton(layoutWidget);
        pushButton_2->setObjectName("pushButton_2");

        horizontalLayout_2->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(layoutWidget);
        pushButton_3->setObjectName("pushButton_3");

        horizontalLayout_2->addWidget(pushButton_3);

        LanguageSelectMenu = new QGroupBox(StartMenuWindow);
        LanguageSelectMenu->setObjectName("LanguageSelectMenu");
        LanguageSelectMenu->setGeometry(QRect(30, 120, 1011, 581));
        stackedWidget = new QStackedWidget(LanguageSelectMenu);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(10, 10, 991, 561));
        ChoicePage = new QWidget();
        ChoicePage->setObjectName("ChoicePage");
        layoutWidget1 = new QWidget(ChoicePage);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(300, 210, 401, 121));
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_4 = new QPushButton(layoutWidget1);
        pushButton_4->setObjectName("pushButton_4");

        horizontalLayout->addWidget(pushButton_4);

        pushButton_5 = new QPushButton(layoutWidget1);
        pushButton_5->setObjectName("pushButton_5");

        horizontalLayout->addWidget(pushButton_5);

        pushButton_6 = new QPushButton(layoutWidget1);
        pushButton_6->setObjectName("pushButton_6");

        horizontalLayout->addWidget(pushButton_6);

        stackedWidget->addWidget(ChoicePage);
        Language1Page = new QWidget();
        Language1Page->setObjectName("Language1Page");
        stackedWidget->addWidget(Language1Page);

        retranslateUi(StartMenuWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(StartMenuWindow);
    } // setupUi

    void retranslateUi(QDialog *StartMenuWindow)
    {
        StartMenuWindow->setWindowTitle(QCoreApplication::translate("StartMenuWindow", "Dialog", nullptr));
        menuNavbar->setTitle(QString());
        label->setText(QCoreApplication::translate("StartMenuWindow", "Inimi ramase:", nullptr));
        pushButton->setText(QCoreApplication::translate("StartMenuWindow", "Cursuri", nullptr));
        pushButton_2->setText(QCoreApplication::translate("StartMenuWindow", "Leaderboard", nullptr));
        pushButton_3->setText(QCoreApplication::translate("StartMenuWindow", "Chat", nullptr));
        LanguageSelectMenu->setTitle(QString());
        pushButton_4->setText(QCoreApplication::translate("StartMenuWindow", "C++", nullptr));
        pushButton_5->setText(QCoreApplication::translate("StartMenuWindow", "C#", nullptr));
        pushButton_6->setText(QCoreApplication::translate("StartMenuWindow", "Java", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StartMenuWindow: public Ui_StartMenuWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTMENUWINDOW_H
