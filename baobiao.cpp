#include "baobiao.h"
#include "ui_baobiao.h"
#include "global.h"
#include <QTableWidgetItem>

baobiao::baobiao(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::baobiao)
{
#ifdef ARM
    setWindowFlags(Qt::FramelessWindowHint);
#endif

    ui->setupUi(this);
    //ui->tabWidget->setTabText(0,"机型");
    //ui->tabWidget->setTabText(1,"usb口");
    ui->JixingTab->setColumnWidth(0,150);
    ui->JixingTab->setColumnWidth(1,350);
    ui->JixingTab->setColumnWidth(2,210);
    ui->JixingTab->setRowCount(12);

    ui->UsbTab->setColumnWidth(0,150);
    ui->UsbTab->setColumnWidth(1,350);
    ui->UsbTab->setColumnWidth(2,210);
    ui->UsbTab->setRowCount(12);


    //set the date display policy
    ui->FromdateEdit->setDate(QDate::currentDate());
    ui->TodateEdit->setDate(QDate::currentDate());

    ui->searchBtn->setAutoFillBackground(true);

    this->setWindowTitle(tr("报表"));
    this->setFixedSize(800,480);
}

baobiao::~baobiao()
{
    delete ui;
}

void baobiao::OnReturn()
{
    this->close();
}
void baobiao::OnSearchData()
{
    ui->JixingTab->clear();
    ui->JixingTab->setHorizontalHeaderLabels(QStringList()<< tr("日期")<<tr("机型")<<tr("安装数量"));
    ui->UsbTab->clear();
    ui->UsbTab->setHorizontalHeaderLabels(QStringList()<<tr("日期")<<tr("USB口")<<tr("安装数量"));
    string dateFrom = ui->FromdateEdit->text().remove('-').toStdString();
    string dateTo = ui->TodateEdit->text().remove('-').toStdString();
    int nMod = 0;
    if( ui->tabWidget->currentIndex() == 0)
        nMod = 0;
    else if( ui->tabWidget->currentIndex() == 1)
        nMod = 1;

    if( nMod == 0)
    {
        int total = 0;
        vector<reportInfo> res;
        res.clear();
        reportDB rDB;
        rDB.getModel(dateFrom,dateTo, res);

        for (size_t nRow = 0; nRow < res.size(); nRow++)
        {
            for( int nCol = 0; nCol < 3; nCol++)
            {
                QTableWidgetItem* newItem = NULL;
                switch(nCol)
                {
                    case 0:
                        newItem = new QTableWidgetItem(QString::fromStdString(res[nRow].installDate.c_str()));
                        break;
                    case 1:
                        newItem = new QTableWidgetItem(QString::fromStdString(res[nRow].model.c_str()));
                        break;
                    case 2:
                        QString ss = QString("%1").arg(res[nRow].count);
                        total += res[nRow].count;
                        newItem = new QTableWidgetItem(ss);
                        break;
                }
                ui->JixingTab->setItem(nRow,nCol,newItem);
            }
        }

        ui->totalLabel->setText(QString().setNum(total));
    }
    else if( nMod == 1)
    {
        int total = 0;
        vector<reportInfo> res;
        res.clear();
        reportDB rDB;
        rDB.getUsb(dateFrom,dateTo, res);

        for (size_t nRow = 0; nRow < res.size(); nRow++)
        {
            for( int nCol = 0; nCol < 3; nCol++)
            {
                QTableWidgetItem* newItem = NULL;
                switch(nCol)
                {
                    case 0:
                        newItem = new QTableWidgetItem(QString::fromStdString(res[nRow].installDate.c_str()));
                        break;
                    case 1:
                        {
                            QString tmp = QString("%1").arg(res[nRow].portIdx);
                            newItem = new QTableWidgetItem(tmp);
                            break;
                        }
                    case 2:
                        {
                            QString ss = QString("%1").arg(res[nRow].count);
                            total += res[nRow].count;
                            newItem = new QTableWidgetItem(ss);
                            break;
                        }
                }
                ui->UsbTab->setItem(nRow,nCol,newItem);
            }
        }

        ui->totalLabel->setText(QString().setNum(total));
    }
}
