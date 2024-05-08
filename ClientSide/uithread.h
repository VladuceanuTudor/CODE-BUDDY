#ifndef UITHREAD_H
#define UITHREAD_H
#include <QObject>
#include <QTextEdit>
#include "chatapp.h"
#include "Utils.h"
#include <QThread>

class UIThread : public QObject {
    Q_OBJECT
public:
    explicit UIThread(QObject *parent = nullptr);

public slots:
    void updateUI(QTextEdit *textEdit, std::string numePrieten);
};

#endif // UITHREAD_H
