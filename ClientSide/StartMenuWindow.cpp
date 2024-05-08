#include "startmenuwindow.h"
#include "ui_startmenuwindow.h"
#include <QtGui/QGradient> // Include for qlineargradient
#include <QPushButton>
#include <QVBoxLayout> // Assuming vertical layout
#include <QMessageBox>
#include <QTextEdit>
#include <QButtonGroup>
#include <QRadioButton>
#include <QPixmap>
#include "paymentdialog.h"
#include "QLineEdit"
#include "QSplitter"
#include <QObject>

int nrInimi=0;

StartMenuWindow::StartMenuWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::StartMenuWindow)
{
    ui->setupUi(this);
    chat_thread = nullptr;

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
    this->setWindowTitle("CODE-BUDDY");
    Connection::_req_Inimi_nr(nrInimi,ui->nrInimi);
    if(premium == true){
        ui->nrInimi->setText("∞");
        ui->pushButton_7->hide();
    }

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

    QTextEdit *questionTextbox = new QTextEdit(this);
    questionTextbox->setText(QString::fromStdString(ex->getCerinta()));
    questionTextbox->setReadOnly(true);
    layout->addWidget(questionTextbox);

    if(ex->getType()=='G'){
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
                        if(premium==true){
                            ui->nrInimi->setText("∞");
                            ui->pushButton_7->hide();
                        }
                        if(nrInimi==0){
                            QMessageBox::information(nullptr, "Indisponibil", "Ai ramas fara vieti!!");
                            StartMenuWindow::on_pushButton_clicked();
                        }
                    }
                    break;
                }
            }
        });
    }else if(ex->getType() == 'T'){
        QLineEdit *lineEdit = new QLineEdit();
        lineEdit->setPlaceholderText("Scrie raspunsul aici..");
        layout->addWidget(lineEdit);

        QPushButton* verifyButton = new QPushButton("Verify", widget);
        layout->addWidget(verifyButton);

        QObject::connect(verifyButton, &QPushButton::clicked, [=]() {


                    std::string selectedAnswer = lineEdit->text().toStdString();
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
                        if(premium==true){
                            ui->nrInimi->setText("∞");
                            ui->pushButton_7->hide();
                        }
                        if(nrInimi==0){
                            QMessageBox::information(nullptr, "Indisponibil", "Ai ramas fara vieti!!");
                            StartMenuWindow::on_pushButton_clicked();
                        }
                    }
        });
    }else if(ex->getType() == 'B'){
        QListWidget *newListWidget = new QListWidget(this);

        for(auto bloc : ex->getListaRasp())
            newListWidget->addItem(QString::fromStdString(bloc));
        // Add strings to the list

        // Enable drag-and-drop
        newListWidget->setDragEnabled(true);
        newListWidget->setDragDropMode(QAbstractItemView::InternalMove);

        // Optionally, set other properties for better user experience
        newListWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        newListWidget->setDefaultDropAction(Qt::MoveAction);

        layout->addWidget(newListWidget);

        QPushButton* verifyButton = new QPushButton("Verify", widget);
        layout->addWidget(verifyButton);

        QObject::connect(verifyButton, &QPushButton::clicked, [=]() {
            std::string selectedAnswer;

            // Iterate through each item in the list
            for (int i = 0; i < newListWidget->count(); ++i) {
                // Get the item at the current index
                QListWidgetItem *item = newListWidget->item(i);

                // Get the text of the item and add it to the itemOrder vector
                selectedAnswer+= item->text().toStdString();

                if(i!=newListWidget->count()-1)
                    selectedAnswer+= " ";
            }

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
                if(premium==true){
                    ui->nrInimi->setText("∞");
                    ui->pushButton_7->hide();
                }
                if(nrInimi==0){
                    QMessageBox::information(nullptr, "Indisponibil", "Ai ramas fara vieti!!");
                    StartMenuWindow::on_pushButton_clicked();
                }
            }
        });
    }

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
    //lessonTextEdit->setSizeHint(QSize(130, 200));
    lessonTextEdit->setFixedSize(992, 200);
    layout->addWidget(lessonTextEdit);

    // Add a label for exercises
    QLabel* exercisesLabel = new QLabel("Exercises:");
    layout->addWidget(exercisesLabel);

    // Add a QListWidget to display the exercises
    QListWidget* exercisesListWidget = new QListWidget;
    exercisesListWidget->setFixedSize(992, 330);
    for (IExercitiu* exercitiu : lectie->getEx()) {
        QListWidgetItem* item = new QListWidgetItem(exercisesListWidget);
        item->setSizeHint(QSize(200, 240)); // Set the size of each item
        //exercisesListWidget->setItemDelegate(new QItemDelegate(exercisesListWidget));
        exercisesListWidget->addItem(item);
        exercisesListWidget->setItemWidget(item, createExerciseWidget(exercitiu));
    }

    layout->addWidget(exercisesListWidget);
    layout->addSpacerItem(new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Expanding));
    QPushButton* finalizeButton = new QPushButton("Finalizeaza Lectia");
    finalizeButton->setFixedSize(992, 20);
    layout->addWidget(finalizeButton); // Align button to bottom-right corner



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
    if(premium==true){
        ui->nrInimi->setText("∞");
        ui->pushButton_7->hide();
    }
    QLayout* currentLayout = ui->Language1Page->layout();

    deleteLayout(currentLayout);

    QVBoxLayout* buttonLayout = new QVBoxLayout();

    int done_for_color = 1;
    for (const auto& numeLectie : limbaj->getNumeLectii()) {
        QPushButton* button = new QPushButton(QString::fromStdString(numeLectie));
        button->setFixedSize(992, 30);

        button->setStyleSheet("border-radius: 5px; antialiasing: on;");

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
    if(premium==true){
        ui->pushButton_7->hide();
        ui->nrInimi->setText("∞");
    }


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



void StartMenuWindow::on_pushButton_3_clicked()
{
    if(ui->stackedWidget->currentIndex() == 3)
    {
        if(chat_thread)
        {
            ui->stackedWidget->setCurrentIndex(2);
            chat_thread->wait();

            // Delete the thread
            chat_thread->deleteLater();
            chat_thread = nullptr; // Reset

            ui->stackedWidget->setCurrentIndex(3);
        }
        return;
    }
    ui->stackedWidget->setCurrentIndex(3);

    static int iter=0;

    // Delete the existing layout
    QLayout* currentLayout = ui->ChatPage->layout();
    deleteLayout(currentLayout);
    ui->listWidget->clear();
    ui->textEdit->clear();


    if(iter++ == 0)
        Connection::initChat(myUserName);

    for(auto prieten : ChatApp::getInstance().getListaPrieteni())
        ui->listWidget->addItem(QString::fromStdString(prieten));

    if(ui->listWidget->metaObject()->indexOfSignal("itemClicked(QListWidgetItem*)") != -1)
        disconnect(ui->listWidget, &QListWidget::itemClicked, this, &StartMenuWindow::onListItemClicked);
    connect(ui->listWidget, &QListWidget::itemClicked, this, &StartMenuWindow::onListItemClicked);


    ui->textEdit->setReadOnly(true);
}


void StartMenuWindow::onListItemClicked(QListWidgetItem *item) {

    QString clickedText = item->text();
    ui->textEdit->clear();
    std::string conversatie = clickedText.toStdString();

    if(chat_thread)
    {
        ui->stackedWidget->setCurrentIndex(2);
        chat_thread->wait();

        // Delete the thread
        chat_thread->deleteLater();
        chat_thread = nullptr; // Reset

        ui->stackedWidget->setCurrentIndex(3);
    }


    for(auto mesaj : ChatApp::getInstance().getChatByPrieten(conversatie))
    {
        if(mesaj->getEmitator() == "eu")
            appendLeftAlignedText(ui->textEdit, QString::fromStdString("Eu:   " + mesaj->getContinut()));
        else
            appendRightAlignedText(ui->textEdit, QString::fromStdString(mesaj->getEmitator() + ":   " + mesaj->getContinut()));
    }


    chat_thread = new QThread();

    QObject::connect(chat_thread, &QThread::started, [=]() {
        while (item && item->isSelected() && ui->stackedWidget->currentIndex() == 3) {
            Connection::receiveNewMessages(myUserName, conversatie, ui->textEdit);
            QThread::sleep(1);
        }
        qDebug() << "Thread stopped.";
        chat_thread->quit();
    });
    chat_thread->start();

    qDebug()<<"ok";

}


void StartMenuWindow::on_pushButton_8_clicked()
{
    appendLeftAlignedText(ui->textEdit, "Eu:   " + ui->lineEdit->text());
    ChatApp::getInstance().initMesajToConversatie(ui->listWidget->currentItem()->text().toStdString(), ui->lineEdit->text().toStdString());
    try{
        Connection::sendNewMessage(ui->lineEdit->text().toStdString(), ui->listWidget->currentItem()->text().toStdString());
    }catch(int i){
        QMessageBox::information(nullptr, "Server ERROR", "Serverul nu a primit mesajul!");
    }
    ui->lineEdit->clear();
}


void StartMenuWindow::on_AdaugaPrietenBTN_clicked()
{
    std::string numePrieten;
    numePrieten = ui->inputADDprieten->text().toStdString();
    try{
        Connection::addFriend(numePrieten);
    }catch(int i){
        if(i==1){
            ui->listWidget->addItem(QString::fromStdString(numePrieten));
            ChatApp::getInstance().initPrieten(numePrieten);
            ChatApp::getInstance().initConversatie(numePrieten);
        }else
            QMessageBox::information(nullptr, "Adaugarea a esuat", "Utilizatorul nu exista!");
    }
}

