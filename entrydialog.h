#ifndef ENTRYDIALOG_H
#define ENTRYDIALOG_H

#include <QDialog>
#include "QAbstractButton"

namespace Ui {
class EntryDialog;
}

class EntryDialog : public QDialog
{
    Q_OBJECT

public:
    bool deleted;

    explicit EntryDialog(QWidget *parent = nullptr);
    ~EntryDialog();
    QString getTitle();
    QString getType();
    QString getPrice();
    QString getOdometer();
    QString getDate();
    QString getDescription();

    void setTitle(QString text);
    void setType(QString text);
    void setPrice(QString text);
    void setOdometer(QString text);
    void setDate(QString text);
    void setDescription(QString text);

private slots:


    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::EntryDialog *ui;
};

#endif // ENTRYDIALOG_H
