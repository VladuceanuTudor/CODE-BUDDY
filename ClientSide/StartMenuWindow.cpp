#include "startmenuwindow.h"
#include "ui_startmenuwindow.h"
#include <QtGui/QGradient> // Include for qlineargradient
#include <QPushButton>
#include <QVBoxLayout> // Assuming vertical layout
#include <QMessageBox>
#include <QTextEdit>
#include <QListWidget>
#include <QButtonGroup>
#include <QRadioButton>
#include <QPixmap>
#include "paymentdialog.h"

int nrInimi=0;

StartMenuWindow::StartMenuWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::StartMenuWindow)
{
    ui->setupUi(this);

    QPixmap img_inima(":/img/pixelheart.jpg");
    ui->imagine_inima->setPixmap(img_inima.scaled(30,30, Qt::KeepAspectRatio));


    // Set background color using linear gradient
    QString styleSheet = "background-color: rgba(25,21,22,255)";
    ui->label->setStyleSheet("background-color: rgba(0,0,0,0); color: white; font-size: 14px; font-family: 'YourPixelFont'");
    ui->nrInimi->setStyleSheet("background-color: rgba(0,0,0,0); color: white; font-size: 20px; font-family: 'YourPixelFont'");
    ui->imagine_inima->setStyleSheet("background-color: rgba(0,0,0,0); color: white;");
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
            buttonStyle.append("background-color: lightblue; color: black;");
            break;
        case 1:
            buttonStyle.append("background-color: lightgreen; color: black;");
            break;
        case 2:
            buttonStyle.append("background-color: lightyellow; color: black;");
            break;
        case 3:
            buttonStyle.append("background-color: lightcoral; color: black;");
            break;
        }

        buttonCount++;
        button->setStyleSheet(buttonStyle);
    }

    Connection::_req_Inimi_nr(nrInimi,ui->nrInimi);

}

StartMenuWindow::~StartMenuWindow()
{
    delete ui;
}

void deleteLayout(QLayout* currentLayout){
    if (currentLayout) {
        // Clear all layout items:
        while (QLayoutItem* item = currentLayout->takeAt(0)) {
            if (QWidget* widget = item->widget()) {
                delete widget;
            }
            delete item;  // Delete the layout item
        }
        delete currentLayout;
    }
}

QWidget* StartMenuWindow::createExerciseWidget(IExercitiu* ex) {
    QWidget* widget = new QWidget;
    QVBoxLayout* layout = new QVBoxLayout(widget);

    QLabel* questionLabel = new QLabel(QString::fromStdString(ex->getCerinta()));
    layout->addWidget(questionLabel);

    QButtonGroup* answerGroup = new QButtonGroup(widget);
    for (const std::string& answer : ex->getListaRasp()) {
        QRadioButton* radioButton = new QRadioButton(QString::fromStdString(answer));
        layout->addWidget(radioButton);
        answerGroup->addButton(radioButton);
    }

    QPushButton* verifyButton = new QPushButton("Verify", widget);
    layout->addWidget(verifyButton);

    QObject::connect(verifyButton, &QPushButton::clicked, [=]() {
        for (QAbstractButton* abstractButton : answerGroup->buttons()) {
            QRadioButton* radioButton = qobject_cast
                <QRadioButton*>(abstractButton);
            if (radioButton && radioButton->isChecked()) {
                std::string selectedAnswer = radioButton->text().toStdString();
                bool isCorrect = (selectedAnswer == ex->getRaspCorect());
                if(isCorrect == true){
                    ex->setRezolvat();
                    widget->setStyleSheet("color: rgb(0, 185, 0)");
                    deleteLayout(layout);
                    QVBoxLayout* layout = new QVBoxLayout(widget);
                    QLabel *label = new QLabel(QString::fromStdString(ex->getCerinta() + "\n" + "Raspunsul corect:  " + ex->getRaspCorect()));

                    layout->addWidget(label);

                }else{
                    Connection::send_Inimi_decrease();
                    Connection::_req_Inimi_nr(nrInimi, ui->nrInimi);
                    if(nrInimi==0){
                        QMessageBox::information(nullptr, "Indisponibil", "Ai ramas fara vieti!!");
                        StartMenuWindow::on_pushButton_clicked();
                    }
                }
                break;
            }
        }
    });

    widget->setLayout(layout);
    return widget;
}

void StartMenuWindow::displayLectie_Exercitii(ILectie* lectie, std::string numeLectie, CLimbaj* limbaj){
    QLayout* currentLayout = ui->Language1Page->layout();

    deleteLayout(currentLayout);

    QVBoxLayout* layout = new QVBoxLayout;

    // Add a label for the lesson name
    QLabel* nameLabel = new QLabel(QString::fromStdString(numeLectie));
    layout->addWidget(nameLabel);

    // Add a QTextEdit widget to display the lesson text
    QTextEdit* lessonTextEdit = new QTextEdit;
    lessonTextEdit->setReadOnly(true); // Set text edit to read-only
    lessonTextEdit->setText(QString::fromStdString(lectie->getText()));
    layout->addWidget(lessonTextEdit);

    // Add a label for exercises
    QLabel* exercisesLabel = new QLabel("Exercises:");
    layout->addWidget(exercisesLabel);

    // Add a QListWidget to display the exercises
    QListWidget* exercisesListWidget = new QListWidget;
    for (IExercitiu* exercitiu : lectie->getEx()) {
        QListWidgetItem* item = new QListWidgetItem(exercisesListWidget);
        item->setSizeHint(QSize(200, 200)); // Set the size of each item
        exercisesListWidget->addItem(item);
        exercisesListWidget->setItemWidget(item, createExerciseWidget(exercitiu));
    }

    layout->addWidget(exercisesListWidget);

    QPushButton* finalizeButton = new QPushButton("Finalizeaza Lectia");
    finalizeButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    layout->addWidget(finalizeButton, 0, Qt::AlignBottom | Qt::AlignRight); // Align button to bottom-right corner

    // Connect button clicked signal to a slot
    connect(finalizeButton, &QPushButton::clicked, [=]() {
        finalizeLectia(lectie, limbaj, numeLectie);
    });

    // Add layout to the widget
    ui->Language1Page->setLayout(layout);
    ui->stackedWidget->setCurrentIndex(1);
}

void StartMenuWindow::finalizeLectia(ILectie* lectie, CLimbaj* limbaj, std::string numeLectie) {
    bool lectieCompletata = true;
    for(const auto ex : lectie->getEx()){
        if(ex->getRezolvat()==false)
            lectieCompletata = false;
    }

    if(lectieCompletata==true)
        try {
            Connection::send_Exercitiu_DONE(numeLectie, limbaj->getName());
        } catch (int i) {
            QMessageBox::information(nullptr, "Server ERROR", "Serverul nu a primit mesajul!");
    }

    if(limbaj->getName() == "cpp"){
        delete limbaj;
        StartMenuWindow::on_pushButton_4_clicked();
    }else if(limbaj->getName() == "csh"){
        delete limbaj;
        StartMenuWindow::on_pushButton_5_clicked();
    }else{
        delete limbaj;
        StartMenuWindow::on_pushButton_6_clicked();
    }
}

void StartMenuWindow::onLessonButtonClicked(const QString& buttonText, CLimbaj* limbaj)
{
    if(limbaj->getLessonNrByName(buttonText.toStdString()) > limbaj->getCompleted()){
        // qDebug() << limbaj->getLessonNrByName(buttonText.toStdString());
        // qDebug() << limbaj->getCompleted();
        QMessageBox::information(nullptr, "Indisponibil", "Pentru a putea incepe acea lectie te \nrog completeaza-le pe cale\n anterioare prima data!");
    } else if(nrInimi==0){
        QMessageBox::information(nullptr, "Indisponibil", "Ai ramas fara vieti!!");
    }
    else{
        ILectie* lectie = nullptr;
        Connection::_initLectie(lectie, buttonText.toStdString(), limbaj->getName());

        StartMenuWindow::displayLectie_Exercitii(lectie, buttonText.toStdString(), limbaj);

        //qDebug() << "Button clicked:" << buttonText;
    }
}

void StartMenuWindow::printLimbajLessonsMenu(CLimbaj* limbaj){

    Connection::_req_Inimi_nr(nrInimi, ui->nrInimi);
    QLayout* currentLayout = ui->Language1Page->layout();

    deleteLayout(currentLayout);

    QVBoxLayout* buttonLayout = new QVBoxLayout();

    int done_for_color = 1;
    for (const auto& numeLectie : limbaj->getNumeLectii()) {
        QPushButton* button = new QPushButton(QString::fromStdString(numeLectie));

        // Set button background color based on completion status:
        if(done_for_color < limbaj->getCompleted())
            button->setStyleSheet("background-color: lime; color: black;");
        if(done_for_color == limbaj->getCompleted())
            button->setStyleSheet("background-color: yellow; color: black;");

        // Connect the button to a slot that takes the button text as parameter:
        connect(button, &QPushButton::clicked, this,
                [numeLectie, this, limbaj] {  // Capture numeLectie by value
                    onLessonButtonClicked(numeLectie.c_str(), limbaj);
                });

        buttonLayout->addWidget(button);
        done_for_color++;
    }

    ui->Language1Page->setLayout(buttonLayout);
    ui->stackedWidget->setCurrentIndex(1);
}

void StartMenuWindow::on_pushButton_4_clicked()
{
    CLimbaj* cpp = new CLimbaj("cpp");
    Connection::initLimbaj(*cpp);
    StartMenuWindow::printLimbajLessonsMenu(cpp);
}

void StartMenuWindow::on_pushButton_5_clicked()
{
    CLimbaj* csh = new CLimbaj("csh");
    Connection::initLimbaj(*csh);
    StartMenuWindow::printLimbajLessonsMenu(csh);
}

void StartMenuWindow::on_pushButton_6_clicked()
{
    CLimbaj* java = new CLimbaj("java");
    Connection::initLimbaj(*java);
    StartMenuWindow::printLimbajLessonsMenu(java);
}

void StartMenuWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    Connection::_req_Inimi_nr(nrInimi, ui->nrInimi);
}


void StartMenuWindow::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    QLayout* currentLayout = ui->LeaderBoard->layout();

    deleteLayout(currentLayout);

    ui->Title->setFont(QFont("Arial", 16));
    QVBoxLayout *verticalLayout = new QVBoxLayout;

    // Create QPushButton objects for the global and local buttons
    QPushButton *globalButton = new QPushButton("Global");
    QPushButton *localButton = new QPushButton("Local");

    globalButton->setFixedSize(100, 30); // Adjust the size as needed
    localButton->setFixedSize(100, 30);

    // Add the buttons to the horizontal layout
    verticalLayout->addWidget(globalButton);
    verticalLayout->addWidget(localButton);

    connect(globalButton, &QPushButton::clicked, this,
            [verticalLayout, this] {
                LeaderBoard::showGlobalLeaderboard(verticalLayout, this->myUserName);
            });
    connect(localButton, &QPushButton::clicked, this,
            [verticalLayout, this] {
                LeaderBoard::showLocalLeaderboard(verticalLayout, this->myUserName);
            });

    // Add the container widget to your main layout (e.g., a QVBoxLayout)
    ui->LeaderBoard->setLayout(verticalLayout);
}


void StartMenuWindow::on_pushButton_7_clicked()
{
    PaymentDialog* pDialog = new PaymentDialog();
    pDialog->show();
}

