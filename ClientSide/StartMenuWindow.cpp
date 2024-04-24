#include "startmenuwindow.h"
#include "ui_startmenuwindow.h"
#include <QtGui/QGradient> // Include for qlineargradient
#include <QPushButton>
#include <QVBoxLayout> // Assuming vertical layout

StartMenuWindow::StartMenuWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::StartMenuWindow)
{
    ui->setupUi(this);

    // Set background color using linear gradient
    QString styleSheet = "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(85, 85, 85, 255), stop:1 rgba(64, 64, 64, 255));";
    ui->menuNavbar->setStyleSheet(styleSheet);


    // Style buttons within menuNavbar (assuming they are QPushButtons)
    for (auto button : ui->menuNavbar->findChildren<QPushButton*>()) {
        button->setStyleSheet("color: white; background-color: grey; padding: 6px; margin: 2px; border-radius: 6px;");
    }

    int buttonCount = 0; // Counter for assigning different colors

    for (auto button : ui->LanguageSelectMenu->findChildren<QPushButton*>()) {
        QString buttonStyle;

        // Set rounded corners
        buttonStyle.append("border-radius: 6px;margin: 2px;font-size: 16px;");
        button->setFixedSize(100, 50);
        // Assign different colors based on counter
        switch (buttonCount % 4) {
        case 0:
            buttonStyle.append("background-color: lightblue;");
            break;
        case 1:
            buttonStyle.append("background-color: lightgreen;");
            break;
        case 2:
            buttonStyle.append("background-color: lightyellow;");
            break;
        case 3:
            buttonStyle.append("background-color: lightcoral;");
            break;
        }

        buttonCount++;
        button->setStyleSheet(buttonStyle);
    }
    // Remove unused variable (optional)
    // delete menuBarButton;
}

StartMenuWindow::~StartMenuWindow()
{
    delete ui;
}

void StartMenuWindow::on_pushButton_4_clicked()
{
    CLimbaj cpp("Cpp");
    Connection::initLimbaj(cpp);

    cpp.addNumeLectii("Introducere");
    cpp.addNumeLectii("Cap1");
    cpp.addNumeLectii("cap2");
    cpp.addNumeLectii("Cap3");
    QVBoxLayout* buttonLayout = new QVBoxLayout();

    for(auto numeLectie : cpp.getNumeLectii()){
        QPushButton* button = new QPushButton(QString::fromStdString(numeLectie));
        // Optionally connect the button to a slot for functionality
        // connect(button, &QPushButton::clicked, this, &YourClass::onButtonClicked);
        buttonLayout->addWidget(button);
    }
    ui->Language1Page->setLayout(buttonLayout);
    ui->stackedWidget->setCurrentIndex(1);
}


void StartMenuWindow::on_pushButton_5_clicked()
{

}


void StartMenuWindow::on_pushButton_6_clicked()
{

}


void StartMenuWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

