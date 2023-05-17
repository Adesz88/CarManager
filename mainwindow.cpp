#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "entrydialog.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->tableWidget);
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
        QTableWidgetItem *title = new QTableWidgetItem(dialog.getTitle());

        unsigned next_row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(next_row);

        ui->tableWidget->setItem(next_row, 0, title);
    }
}

