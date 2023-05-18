#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "entrydialog.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->tableWidget);
    edit = false;
    current_item = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAdd_entry_triggered()
{
    EntryDialog dialog;
    if (dialog.exec() == QDialog::Accepted)
    {
        QTableWidgetItem *date = new QTableWidgetItem(dialog.getDate());
        QTableWidgetItem *title = new QTableWidgetItem(dialog.getTitle());
        QTableWidgetItem *type = new QTableWidgetItem(dialog.getType());
        QTableWidgetItem *odometer = new QTableWidgetItem(dialog.getOdometer());
        QTableWidgetItem *price = new QTableWidgetItem(dialog.getPrice());
        QTableWidgetItem *description = new QTableWidgetItem(dialog.getDescription());

        unsigned next_row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(next_row);

        ui->tableWidget->setItem(next_row, 0, date);
        ui->tableWidget->setItem(next_row, 1, title);
        ui->tableWidget->setItem(next_row, 2, type);
        ui->tableWidget->setItem(next_row, 3, odometer);
        ui->tableWidget->setItem(next_row, 4, price);
        ui->tableWidget->setItem(next_row, 5, description);
    }
}


void MainWindow::on_tableWidget_cellDoubleClicked(int row, int column)
{
    EntryDialog dialog;

    dialog.setDate(ui->tableWidget->item(row, 0)->text());
    dialog.setTitle(ui->tableWidget->item(row, 1)->text());
    //dialog.setType(ui->tableWidget->item(row, 2)->text());
    dialog.setOdometer(ui->tableWidget->item(row, 3)->text());
    dialog.setPrice(ui->tableWidget->item(row, 4)->text());
    dialog.setDescription(ui->tableWidget->item(row, 5)->text());

    int dialogResult = dialog.exec();

    if (dialogResult == QDialog::Accepted)
    {
        ui->tableWidget->item(row, 0)->setText(dialog.getDate());
        ui->tableWidget->item(row, 1)->setText(dialog.getTitle());
        ui->tableWidget->item(row, 2)->setText(dialog.getType());
        ui->tableWidget->item(row, 3)->setText(dialog.getOdometer());
        ui->tableWidget->item(row, 4)->setText(dialog.getPrice());
        ui->tableWidget->item(row, 5)->setText(dialog.getDescription());
    }
    else if (dialogResult == QDialog::Rejected && dialog.deleted)
    {
        ui->tableWidget->item(row, 1)->setText("rejected");
        ui->tableWidget->removeRow(row);
    }
}

