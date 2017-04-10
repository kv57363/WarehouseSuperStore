#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "container.h"
#include "container_sales.h"
#include <QSignalMapper>
#include <QString>
#include <QDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSignalMapper* signalMapper = new QSignalMapper(this);
    connect(ui->addLog, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->saveLog, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->addProfile, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->saveProfile, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->newLog, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->newProfile, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->addLog, "addLog");
    signalMapper->setMapping(ui->saveLog, "saveLog");
    signalMapper->setMapping(ui->addProfile, "addProfile");
    signalMapper->setMapping(ui->saveProfile, "saveProfile");
    signalMapper->setMapping(ui->newLog, "newLog");
    signalMapper->setMapping(ui->newProfile, "newProfile");
    connect(signalMapper, SIGNAL(mapped(QString)), this, SLOT(onAction(QString)));
    connect(ui->addUser, SIGNAL(clicked()), this, SLOT(addUser()));

}

void MainWindow::onAction(QString action)
{
 if(action == "addLog")
    openFile(action);
 if(action == "addProfile")
    openFile(action);
 if(action == "saveLog")
    saveFile(action);
 if(action == "saveProfile")
    saveFile(action);
 if(action == "newLog")
    clearTable(action);
 if(action == "newProfile")
    clearTable(action);
}

void MainWindow::openFile(QString currentTab)
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"/path/to/file/",tr("Text Files (*.txt)"));
    std::string fileNameString = fileName.toStdString();
    std::cout<<fileNameString<<std::endl;
    if(fileNameString == ""){}
    else
    {
        if(currentTab == "addProfile")
        {
             Container users(fileNameString);
        }
        else if(currentTab == "addLog")
        {
            Container_sales sales(fileNameString);
                std::cout<<"WHAT THE FUCK"<<std::endl;
            int *quantities = sales.getQuantities(), *IDs = sales.getMemberID();
                std::cout<<"WHAT THE FUCK"<<std::endl;
            std::string *items = sales.getItemList();
                std::cout<<"WHAT THE FUCK"<<std::endl;
            for(int i = 0; i < sales.list_size(); i++)
            {
                int k = 1;
                ui->SaleLogs->setRowCount(i);
                ui->SaleLogs->setItem(i,k,new QTableWidgetItem(QString::number(quantities[k-1])));
            }
        }
    }
}

void MainWindow::saveFile(QString currentTab)
{
    QString fileNames = QFileDialog::getSaveFileName(this, tr("Save File"),"/path/to/file/",tr("Text Files (*.txt)"));
}

void MainWindow::clearTable(QString tableName)
{
    if(tableName == "SaleLogs")
        ui->SaleLogs->setRowCount(0);
    else if (tableName == "UserLogs")
        ui->UserLogs->setRowCount(0);
}

void MainWindow::addUser()
{
    bool isPref;
    QString ID = ui->UserIDText_2->toPlainText(),
            name = ui->NameText->toPlainText(),
            expDate = ui->ExpiresText->toPlainText();
    if(ui->isPrefered->isChecked())
        isPref = true;
    else
        isPref = false;
   //members.addMember(name.toStdString(),ID.toInt(),isPref,expDate.toInt());
    ui->UserIDText_2->clear();
    ui->NameText->clear();
    ui->ExpiresText->clear();
    ui->isPrefered->setChecked(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}
