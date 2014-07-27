#include "wenjian.h"
#include "ui_wenjian.h"
#include "global.h"
#include <QDate>
#include <QPalette>
#include <QProcess>
#include <QtDebug>

wenjian::wenjian(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::wenjian)
{
#ifdef ARM
    setWindowFlags(Qt::FramelessWindowHint);
#endif

    ui->setupUi(this);
    this->setWindowTitle(tr("文件"));

    m_process = new QProcess(this);
    connect(m_process, SIGNAL(finished(int)), this, SLOT(setFreeSpace1(int)));

    connect(ui->comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(onPkgChanged(int)));

    UpdateContent();
}

wenjian::~wenjian()
{
    delete ui;
}

void wenjian::onreturn()
{
    m_process->kill();
    this->close();
}

void wenjian::UpdateContent()
{
    QPalette pe;
    pe.setColor(QPalette::WindowText,Qt::blue);
    ui->cardspaceLabel->setPalette(pe);
    ui->ldateLabel->setPalette(pe);
    ui->updatenumLabel->setPalette(pe);
    ui->apkLabel->setPalette(pe);

    ui->comboBox->clear();
    m_pkgDB.getAll(m_pkgInfos);
    for (int i = 0; i < m_pkgInfos.size(); ++i)
    {
        ui->comboBox->addItem(QString::fromStdString(m_pkgInfos[i].pkgName));
    }

    setFreeSpace();
    setUpdatetime();
    setUpdatenum();
}

void wenjian::setFreeSpace()
{
    m_process->start("df -h");
}

void wenjian::setUpdatetime()
{
    ui->ldateLabel->setText(Global::s_updateTime);
}

void wenjian::setUpdatenum()
{
    int num = 0;
    m_apkDB.getRecordCount(num);
    ui->updatenumLabel->setText(QString().setNum(num));
}

void wenjian::setFreeSpace1(int)
{
    QProcess* pRes =( QProcess*)sender();
    QString strRes = pRes->readAll();
    double dFreeSpace = 0;
    QStringList strLstLine = strRes.split("\n", QString::SkipEmptyParts);
    for (int i = strLstLine.count()-1; i >= 0; i--)
    {
        QStringList strs = strLstLine[i].split(" ", QString::SkipEmptyParts);
        if (strs.count() < 6) continue;
        if (!strs[5].contains("/mnt/repos")) continue;

        QString strNum = strs[3];
        QString strUnit = strs[3].right(1);
        strNum.remove(strUnit);
        if(strUnit == "G"){
            dFreeSpace += strNum.toDouble();
        }else{
            if(strUnit == "M")
                dFreeSpace += strNum.toDouble()/1024;
            else
                dFreeSpace += strNum.toDouble()/(1024*1024);
        }
    }
    ui->cardspaceLabel->setText(QString::number(dFreeSpace));
}

void wenjian::onPkgChanged(int index)
{    
    int apkNum = m_pkgInfos[index].apkList.size();
    ui->apkLabel->setText(QString().setNum(apkNum));
}

