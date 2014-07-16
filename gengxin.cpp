#include "gengxin.h"
#include "ui_gengxin.h"
#include "global.h"
#include <QMessageBox>


Gengxin::Gengxin(bool start, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Gengxin)
{
    QString msg = tr("系统正在更新中...\n请不要插/拔数据线进行安装工作或进行其他操作");
    if (start) msg = tr("系统版本更新中...\n请不要插/拔数据线进行安装工作或进行其他操作");
    //setWindowFlags(Qt::FramelessWindowHint);
    ui->setupUi(this);
    this->setWindowTitle(tr("更新"));
    
    ui->labUp->setText(msg);
    MvLoading = new QMovie(":/images/loading.gif");
    ui->labMv->setMovie(MvLoading);
    this->ui->pushBtnTerm->setVisible(false);

    SetBtnInvis();
}

Gengxin::~Gengxin()
{
    delete ui;
}

void Gengxin::closeEvent(QCloseEvent* e)
{
    e->ignore();
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
    updateStartVersion();

    bool devState = m_dataUp->GetDevState();

    if (devState && Global::s_needRestart)
    {
        QString exePath = qApp->applicationFilePath();
        QString newExe = exePath + ".bak";
        QFile::remove(exePath);
        QFile::copy(newExe, exePath);
        qApp->quit();
        QProcess::startDetached(exePath, QStringList());
    }
}

void Gengxin::updateStartVersion()
{
    //bool devState = m_dataUp->GetDevState();
    bool devState = true;
    Global::s_needRestart = true;

    QString strState;
    if (devState && Global::s_needRestart)
        strState = "软件版本更新成功!自动重启软件!\n";
    else if (!devState)
        strState = "软件版本更新失败!\n";

    if (!strState.isEmpty())
        QMessageBox::critical(this, windowTitle(), strState);
}

void Gengxin::StartUpdate()
{
    MvLoading->start();
    m_dataUp = new DataUpdate;
    //connect(m_dataUp, SIGNAL(devFinish()), this, SLOT(updateVersion()));
    m_dataUp->GetDeviceVer();

    connect(m_dataUp, SIGNAL(CloseUp()), this, SLOT(UpDone()));
    m_dataUp->updateData();
}

void Gengxin::StartUpSoft()
{
    MvLoading->start();
    m_dataUp = new DataUpdate;
    //connect(m_dataUp, SIGNAL(devFinish()), this, SLOT(updateStartVersion()));
    //m_dataUp->GetDeviceVer();
    updateStartVersion();
}
