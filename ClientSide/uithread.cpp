#include "uithread.h"

UIThread::UIThread(QObject *parent) : QObject(parent) {;}
void UIThread::updateUI(QTextEdit *textEdit, std::string numePrieten)
{   int i=100;
    while (i--) {


        textEdit->clear();
        for (userMessage* mesaj : ChatApp::getInstance().getChatByPrieten(numePrieten))
            if(mesaj->getEmitator() == "eu")
                appendLeftAlignedText(textEdit, QString::fromStdString("Eu:   " + mesaj->getContinut()));
            else
                appendRightAlignedText(textEdit, QString::fromStdString(mesaj->getEmitator() + ":   " + mesaj->getContinut()));

        QThread::sleep(5); // Sleep for 1 second before updating UI again
    }
}
