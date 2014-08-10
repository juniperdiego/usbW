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
    Palette.setBrush(QPalette::Background, QBrush(QPixmap(":/images/blue.png")));
    this->setPalette(Palette);
    this->setFixedSize(120,190);
    Palette.setColor(QPalette::WindowText, Qt::white);
    ui->labNum->setText(tr(""));
    ui->labStatus->setText(tr(""));
    ui->labNum->setPalette(Palette);
    ui->labStatus->setPalette(Palette);
    ui->labUa->setPalette(Palette);
    ui->labPerc->setPalette(Palette);
    ui->progBar_Install->setRange(0,99);
    ui->progBar_Install->setTextVisible(false);
    ui->progBar_Install->setVisible(false);
    ui->labPerc->setVisible(false);
    ui->labUa->setVisible(false);

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
        QString model = usbState->model;
        if (model.length() > 9) model = model.right(9);
        ui->labUa->setText(model);
        ui->labUa->setVisible(true);
        this->StartPercLab();
        this->StartProcBar();
    }
    else if (usbState->install_state == 1)
    {
        this->percRun();
        this->progRun();
    }
    else if(usbState->install_state == 2)
    {
        this->SetStatus(tr("完成"));
        this->StopProcBar();
        this->StopPercLab();
    }
    else if(usbState->install_state == 0)
    {
        this->SetStatus(tr("空闲"));
        ui->progBar_Install->setVisible(false);
        ui->labPerc->setVisible(false);
        ui->labUa->setVisible(false);
    }
    else if(usbState->install_state == 3)
    {
        this->SetStatus(tr("中断"));
        this->StopProcBar();
        this->StopPercLab();
        ui->progBar_Install->setVisible(false);
        ui->labPerc->setVisible(false);
    }
    else if(usbState->install_state == 4)
    {
        this->SetStatus(tr("失败"));
        this->StopProcBar();
        this->StopPercLab();
        ui->progBar_Install->setVisible(false);
        ui->labPerc->setVisible(false);
    }
    else if(usbState->install_state == 5)
    {
        this->SetStatus(tr("准备中"));
    }
    setPaletteWithStatus();
}

void
DevWdg::setPaletteWithStatus()
{
    QString bgImgStr = ":/images/blue.png";
    if(usbState->install_state == 2)
        bgImgStr = ":/images/green.png";
    else if (usbState->install_state == 3 || usbState->install_state == 4)
        bgImgStr = ":/images/red.png";

    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(QPixmap(bgImgStr)));
    setPalette(palette);
}

DevWdg::~DevWdg()
{
    delete ui;
}
