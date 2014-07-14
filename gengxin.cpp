#include "gengxin.h"
#include "ui_gengxin.h"
#include <QtDebug>
#include <QMessageBox>


Gengxin::Gengxin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Gengxin)
{
    //setWindowFlags(Qt::FramelessWindowHint);
    ui->setupUi(this);
    this->setWindowTitle(tr("更新"));
    ui->labUp->setText(tr("系统正在登录中...\n请不要插/拔数据线进行安装工作或进行其他操作"));
    MvLoading = new QMovie(":/images/loading.gif");
    ui->labMv->setMovie(MvLoading);
    this->ui->pushBtnTerm->setVisible(false);

    SetBtnInvis();
}

Gengxin::~Gengxin()
{
    delete ui;
}

void Gengxin::SetBtnInvis()
{
    ui->ConfirmBtn->setVisible(false);
    ui->CancleBtn->setVisible(false);
    ui->pushBtnTerm->setVisible(true);
}
void Gengxin::OnOk()
{
    ui->ConfirmBtn->setVisible(false);
    ui->CancleBtn->setVisible(false);
    ui->pushBtnTerm->setVisible(true);
    StartUpdate();
    qDebug()<<"Updating...";
}
void Gengxin::OnTerm()
{
    if (m_dataUp)
        m_dataUp->quit();

    reject();
}

void Gengxin::OnCancle()
{
    this->close();
}

bool Gengxin::getUpdateState()
{
    return m_updateState;
}

void Gengxin::UpDone()
{
    bool pkgState = m_dataUp->GetPkgState();
    bool apkState = m_dataUp->GetApkState();

    QString strState;
    if (pkgState)
        strState += "安装包数据库更新成功!\n";
    else
        strState += "安装包数据库更新失败\n";
    if (apkState)
        strState += "安装包更新成功\n";
    else
        strState += "安装包更新失败\n";

    QMessageBox::critical(this, windowTitle(), strState);

    if (pkgState && apkState)
    {
        m_updateState = true;
        accept();
    }
    else
    {   
        m_updateState = false;
        reject();
    }
}

void Gengxin::StopUpdate()
{
}

void Gengxin::updateVersion()
{
    bool devState = m_dataUp->GetDevState();

    QString strState;
    if (devState)
        strState += "软件版本更新成功!自动重启软件!\n";
    else
        strState += "软件版本更新失败!\n";

    QMessageBox::critical(this, windowTitle(), strState);

    if (devState)
    {
        qApp->quit();
        QProcess::startDetached(qApp->applicationFilePath(), QStringList());
    }
}

void Gengxin::StartUpdate()
{
    MvLoading->start();
    m_dataUp = new DataUpdate;
    connect(m_dataUp, SIGNAL(devFinish()), this, SLOT(updateVersion()));
    m_dataUp->GetDeviceVer();

    connect(m_dataUp, SIGNAL(CloseUp()), this, SLOT(UpDone()));
    m_dataUp->updateData();
}

