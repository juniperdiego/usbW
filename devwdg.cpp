#include "devwdg.h"
#include "ui_devwdg.h"
#include "tongxin.h"
#include "mainwindow.h"
#include <QPalette>

tongXin* tongXin::_self = NULL;

DevWdg::DevWdg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DevWdg)
{
    ui->setupUi(this);
    this->setAutoFillBackground(true);
    QPalette Palette;
    Palette.setBrush(QPalette::Background, QBrush(QPixmap(":/images/bluebg.png")));
    this->setPalette(Palette);
    this->setFixedSize(100,190);
    Palette.setColor(QPalette::WindowText, Qt::white);
    ui->labNum->setText(tr(""));
    ui->labStatus->setText(tr(""));
    ui->labNum->setPalette(Palette);
    ui->labStatus->setPalette(Palette);
    ui->labPerc->setPalette(Palette);
    ui->progBar_Install->setRange(0,99);
    ui->progBar_Install->setTextVisible(false);
    ui->progBar_Install->setVisible(false);
    ui->labPerc->setVisible(false);

    connect(tongXin::getTongXin(), SIGNAL(updateState(int)), this, SLOT(onUpdateState(int)));
}

void DevWdg::SetNum(QString strNum)
{
    ui->labNum->setText(strNum);
}

void DevWdg::SetStatus(QString strStatus) //End Use
{
    this->strStatus = strStatus;
    ui->labStatus->setText(strStatus);
}

void DevWdg::setApkNum(int nIns, int nTotal)
{
    this->nInsApk = nIns;
    this->nTotalApk = nTotal;
}

void DevWdg::StartPercLab()
{
    ui->labPerc->setVisible(true);
    percRun();
}

void DevWdg::StopPercLab()
{
    if( this->strStatus == tr("安装中"))
    {
        QString strLab = tr("%1/%2").arg(nTotalApk).arg(nTotalApk);
        ui->labPerc->setText(strLab);
    }
    else
    {
        ui->labPerc->setVisible(false);
    }
}

void DevWdg::StartProcBar()
{
    ui->progBar_Install->setVisible(true);
    ui->progBar_Install->setRange(0, nTotalApk);
    progRun();
}

void DevWdg::StopProcBar()
{
    if( this->strStatus == tr("安装中"))
    {
        ui->progBar_Install->setValue(nTotalApk);
    }
    else
    {
        ui->progBar_Install->setVisible(false);
    }
}

void DevWdg::progRun()
{
    ui->progBar_Install->setValue(nInsApk);
}

void DevWdg::percRun()
{
    this->setApkNum((int)this->usbState->apk_num ,(int)usbState->apk_total);
    QString strLab = tr("%1/%2").arg(nInsApk).arg(nTotalApk);
    ui->labPerc->setText(strLab);
}

void DevWdg::onUpdateState(int num) 
{
    qDebug()<<"onUpdateState"<<num;
    MainWindow::s_devArray[num]->DevWdgPrecess(&(Global::usb_state[num]));;
}

void DevWdg::DevWdgPrecess(USB_State* usbState)
{
    this->usbState = usbState;
    if((this->strStatus == tr("空闲") && usbState->install_state ==1) || (this->strStatus == tr("中断") && usbState->install_state ==1))
    {
        this->SetStatus(tr("安装中"));
        this->StartPercLab();
        this->StartProcBar();
    }
    if (usbState->install_state == 1)
    {
        this->percRun();
        this->progRun();
    }
    if(usbState->install_state == 2)
    {
        this->SetStatus(tr("完成"));
        this->StopProcBar();
        this->StopPercLab();
    }
    if(usbState->install_state == 0)
    {
        this->SetStatus(tr("空闲"));
        ui->progBar_Install->setVisible(false);
        ui->labPerc->setVisible(false);
    }
    if(usbState->install_state == 3)
    {
        this->SetStatus(tr("中断"));
        this->StopProcBar();
        this->StopPercLab();
        ui->progBar_Install->setVisible(false);
        ui->labPerc->setVisible(false);
    }
    if(usbState->install_state == 4)
    {
        this->SetStatus(tr("失败"));
        this->StopProcBar();
        this->StopPercLab();
        ui->progBar_Install->setVisible(false);
        ui->labPerc->setVisible(false);
    }
}

DevWdg::~DevWdg()
{
    delete ui;
}
