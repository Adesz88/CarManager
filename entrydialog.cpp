#include "entrydialog.h"
#include "ui_entrydialog.h"

EntryDialog::EntryDialog(QWidget *parent): QDialog(parent),
    ui(new Ui::EntryDialog)
{
    ui->setupUi(this);

    QDate date = QDate::currentDate();
    ui->dateDateEdit->setDate(date);
    ui->dateDateEdit->setDisplayFormat("yyyy. MM. dd.");
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
    return ui->descriptionTextEdit->toPlainText().replace('\n', ' ');
}

void EntryDialog::setTitle(QString text)
{
    ui->titleLineEdit->setText(text);
}

void EntryDialog::setType(QString text)
{
    int index = ui->typeComboBox->findText(text);
    index == -1 ? ui->typeComboBox->setCurrentIndex(0)
                : ui->typeComboBox->setCurrentIndex(index);
}

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
    QDate date = QDate::fromString(text, "yyyy. MM. dd.");
    ui->dateDateEdit->setDate(date);
}

void EntryDialog::setDescription(QString text)
{
    ui->descriptionTextEdit->setPlainText(text);
}

void EntryDialog::setUIForNewEntry()
{
    setWindowTitle("Add new entry");
    ui->buttonBox->addButton("Add", QDialogButtonBox::ButtonRole::AcceptRole);
    ui->buttonBox->addButton(QDialogButtonBox::Cancel);
}

void EntryDialog::setUIForEdit()
{
    setWindowTitle("Edit entry");
    ui->buttonBox->addButton("Update", QDialogButtonBox::ButtonRole::AcceptRole);
    ui->buttonBox->addButton(QDialogButtonBox::Cancel);
    ui->buttonBox->addButton("Delete", QDialogButtonBox::ButtonRole::DestructiveRole);
}

void EntryDialog::on_buttonBox_clicked(QAbstractButton *button)
{
    if (button->text() == "Delete")
    {
        deleted = true;
        close();
    }
}

