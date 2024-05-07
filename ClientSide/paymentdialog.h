#ifndef PAYMENTDIALOG_H
#define PAYMENTDIALOG_H

#include <QDialog>
#include "ServerConnection.h"

extern bool premium;

namespace Ui {
class PaymentDialog;
}

class PaymentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PaymentDialog(QWidget *parent = nullptr);
    ~PaymentDialog();

private slots:
    void on_btnCumpara_clicked();

private:
    Ui::PaymentDialog *ui;
};

#endif // PAYMENTDIALOG_H
