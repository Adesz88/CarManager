#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "entrydialog.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Car manager");
    setCentralWidget(ui->tableWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAdd_entry_triggered()
{
    EntryDialog dialog;
    dialog.setUIForNewEntry();

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
    dialog.setUIForEdit();

    dialog.setDate(ui->tableWidget->item(row, 0)->text());
    dialog.setTitle(ui->tableWidget->item(row, 1)->text());
    dialog.setType(ui->tableWidget->item(row, 2)->text());
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
    // delete selected entry
    else if (dialogResult == QDialog::Rejected && dialog.deleted)
    {
        ui->tableWidget->removeRow(row);
    }
}

void MainWindow::on_actionSave_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, "Save As");
    if (!filename.isEmpty())
    {
        QFile file(filename);       
        if (file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream out(&file);
            unsigned row_count = ui->tableWidget->rowCount();

            for (unsigned row = 0; row < row_count; ++row)
            {
                for (unsigned collumn = 0; collumn < 6; ++collumn)
                {
                    QString cell = ui->tableWidget->item(row, collumn)->text();
                    out << cell << ';';
                }

                if (row < row_count - 1)
                {
                    out << Qt::endl;
                }
            }

            file.close();
        }
    }
    return;
}


void MainWindow::on_actionOpen_triggered()
{
     QString filename = QFileDialog::getOpenFileName(this, "Open");
    if (!filename.isEmpty())
    {
        QFile file(filename);
        if(file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream in(&file);

            // clear table
            while(ui->tableWidget->rowCount() != 0)
            {
                ui->tableWidget->removeRow(0);
            }

            while(!in.atEnd())
            {
                QString line = in.readLine();
                QStringList cells = line.split(';');

                unsigned next_row = ui->tableWidget->rowCount();
                ui->tableWidget->insertRow(next_row);

                for (int i = 0; i < cells.length(); ++i) {
                    QTableWidgetItem *item = new QTableWidgetItem(cells[i]);
                    ui->tableWidget->setItem(next_row, i, item);
                }
            }

            file.close();
        }
    }
    return;
}

