#include "paymentdialog.h"
#include "ui_paymentdialog.h"
#include <QMessageBox>

bool premium=false;

PaymentDialog::PaymentDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PaymentDialog)
{
    ui->setupUi(this);

    this->setWindowTitle("Informatii privind plata");
    QRegularExpressionValidator *card_nr_validator = new QRegularExpressionValidator(QRegularExpression("[0-9 ]{1,19}"), ui->imputNrCard);
    ui->imputNrCard->setValidator(card_nr_validator);

    ui->imputNrCard->setPlaceholderText("xxxx xxxx xxxx xxxx");

    QRegularExpressionValidator *card_nume_validator = new QRegularExpressionValidator(QRegularExpression("[A-Za-z ]{1,50}"), ui->imputNume);
    ui->imputNume->setValidator(card_nume_validator);

    QIntValidator *cvv_validator = new QIntValidator(0, 999, ui->imputCVV);
    ui->imputCVV->setValidator(cvv_validator);
    ui->imputCVV->setPlaceholderText("xxx");
}

PaymentDialog::~PaymentDialog()
{
    delete ui;
}

void PaymentDialog::on_btnCumpara_clicked()
{
    QString imputNrCard = ui->imputNrCard->text();
    QString imputNume = ui->imputNume->text();
    QString imputAnExp = ui->imputAnExp->currentText();
    QString imputLunaExp = ui->imputLunaExp->currentText();
    QString imputCVV = ui->imputCVV->text();
    qDebug() << imputNrCard.toStdString();

    int status = Connection::send_payment(imputNrCard.toStdString(), imputNume.toStdString(), imputCVV.toStdString(), imputAnExp.toStdString(), imputLunaExp.toStdString());
    if(status==1)
    {premium = true;
        this->hide();}
    else
        QMessageBox::information(nullptr, "Tranzactie refuzata", "Cardul nu este valid!");
}

