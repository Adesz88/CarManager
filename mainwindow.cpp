#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "entrydialog.h"
#include "string.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    class User {
    public:
        unsigned age;
        std::string name;

        User() {
            name = "somebody";
            age = 20;
        }
    };

    ui->setupUi(this);
    setCentralWidget(ui -> tableWidget);
    User somebody;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionAdd_entry_triggered()
{
    EntryDialog dialog;
    dialog.exec();
}

