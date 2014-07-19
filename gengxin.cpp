#include "gengxin.h"
#include "ui_gengxin.h"
#include "global.h"


Gengxin::Gengxin(bool start, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Gengxin)
{
    m_dataUp = NULL;

    QString msg = tr("系统数据正在更新中...\n请不要插/拔数据线进行安装工作或进行其他操作");
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
    {
        m_dataUp->quit();
    }

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
    int pkgState = m_dataUp->GetPkgState();
    int apkState = m_dataUp->GetApkState();

    QString strState;

    switch (apkState)
    {
        case 0 : strState += "安装包更新成功!\n"; break;
        case 1 : strState += "安装包更新失败!\n"; break;
        case 2 : strState += "安装包无需更新!\n"; break;
        case 3 : strState += "安装包更新不完全!\n"; break;
        case 4 : strState += "服务器链接错误!\n"; break;
        default : break;
    }

    switch (pkgState)
    {
        case 0 : strState += "安装包数据库更新成功!\n"; break;
        case 1 : strState += "安装包数据库更新失败!\n"; break;
        case 2 : strState += "安装包数据库无需更新!\n"; break;
        case 4 : strState += "服务器链接错误!\n"; break;
        default : break;
    }

    QMessageBox::critical(this, windowTitle(), strState);

    if ((apkState == 0 || apkState == 2) && 
            (pkgState == 0 || pkgState == 2))
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
        QString cmd = "unzip ";
        cmd += UPDATE_FILE_NAME;
        QFile::remove(exePath);
        QProcess::execute(cmd);
#ifdef ARM
        Global::reboot();
#else
        qApp->quit();
        QProcess::startDetached(exePath, QStringList());
#endif
    }
}

void Gengxin::updateStartVersion()
{
    int devState = m_dataUp->GetDevState();

    QString strState;
    if (devState == 0 && Global::s_needRestart)
        strState = "软件版本更新成功!自动重启软件!\n";
    else if (devState == 2)
        strState = "软件版本无需更新!\n";
    else if (devState == 1)
        strState = "软件版本更新失败!\n";
    else if (devState == 4)
        strState = "服务器链接错误!\n";

    if (!strState.isEmpty())
        QMessageBox::critical(this, windowTitle(), strState);
}

void Gengxin::StartUpdate()
{
    MvLoading->start();
    if (m_dataUp == NULL)
        m_dataUp = new DataUpdate;
    //connect(m_dataUp, SIGNAL(devFinish()), this, SLOT(updateVersion()));
    m_dataUp->GetDeviceVer();

    m_dataUp->GetApkLibVer();
    UpDone();
    //connect(m_dataUp, SIGNAL(CloseUp()), this, SLOT(UpDone()));
    //m_dataUp->updateData();
}

void Gengxin::StartUpSoft()
{
    MvLoading->start();
    if (m_dataUp == NULL)
        m_dataUp = new DataUpdate;
    //connect(m_dataUp, SIGNAL(devFinish()), this, SLOT(updateStartVersion()));
    m_dataUp->GetDeviceVer();
    updateStartVersion();
}
