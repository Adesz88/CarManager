#include "entrydialog.h"
#include "ui_entrydialog.h"

EntryDialog::EntryDialog(QWidget *parent): QDialog(parent),
    ui(new Ui::EntryDialog)
{
    ui->setupUi(this);
    deleted = false;
}

EntryDialog::~EntryDialog()
{
    delete ui;
}

QString EntryDialog::getTitle()
{
    return ui->titleLineEdit->text();
}

QString EntryDialog::getType()
{
    return ui->typeComboBox->currentText();
}

QString EntryDialog::getPrice()
{
    return ui->priceSpinBox->text();
}

QString EntryDialog::getOdometer()
{
    return ui->odometerSpinBox->text();
}

QString EntryDialog::getDate()
{
    return ui->dateDateEdit->text();
}

QString EntryDialog::getDescription()
{
    return ui->descriptionTextEdit->toPlainText();
}

void EntryDialog::setTitle(QString text)
{
    ui->titleLineEdit->setText(text);
}

// needs an enum
/*void EntryDialog::setType(QString text)
{
    ui->typeComboBox->setCurrentIndex()
}*/

void EntryDialog::setPrice(QString text)
{
    ui->priceSpinBox->setValue(text.toInt());
}

void EntryDialog::setOdometer(QString text)
{
    ui->odometerSpinBox->setValue(text.toInt());
}

void EntryDialog::setDate(QString text)
{
    QDate date;
    date.fromString(text);
    ui->dateDateEdit->setDate(date);
}

void EntryDialog::setDescription(QString text)
{
    ui->descriptionTextEdit->setPlainText(text);
}


void EntryDialog::on_buttonBox_clicked(QAbstractButton *button)
{
    if ((QPushButton*)button == ui->buttonBox->button(QDialogButtonBox::Discard))
    {
        deleted = true;
        close();
    }
}

