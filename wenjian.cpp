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
    //this->showMaximized();
    this->setWindowTitle(tr("文件"));
#if 0
   // this->setFixedSize(640,500);
    ui->comboBox->addItem("1222");
    ui->comboBox->addItem("3333");
    //connect(ui->comboBox,SIGNAL(activated(QString)),this,SLOT(OnChangeContent(QString)));
    ui->label->setVisible(false);
    ui->comboBox->setVisible(false);
    QProcess* pDf = new QProcess;
    connect(pDf, SIGNAL(finished(int)), this, SLOT(SetFreeSpace(int)));
    //pDf->start(tr("df"),QStringList()<<"-h");
    pDf->start("df -h");
#endif

    m_process = new QProcess(this);
    connect(m_process, SIGNAL(finished(int)), this, SLOT(setFreeSpace1(int)));

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
    int num = 19;

    ui->updatenumLabel->setText(QString().setNum(num));
}

void wenjian::setFreeSpace1(int)
{
    QProcess* pRes =( QProcess*)sender();
    QString strRes = pRes->readAll();
    qDebug()<<strRes;
#if 0
    QStringList strLstLine = strRes.split("\n");
    qDebug()<<strLstLine;
    QStringList strLstMnt;
    strLstMnt = strLstLine.filter("run");/////////////@
    qDebug()<<strLstMnt;
    QList<QString> strLstOneSpace;
    double dFreeSpace = 0;
    for(int i = 0; i<strLstMnt.size(); i++)
    {
        strLstOneSpace.append(strLstMnt[i].simplified());
        qDebug()<<strLstOneSpace[i];
        QString strTmp = strLstMnt[i].simplified();
        QStringList strLstOneSplit = strTmp.split(" ");
        QString strNum = strLstOneSplit[3].left(strLstOneSplit[3].size()-1);
        QString strUnit = strLstOneSplit[3].right(1);
        if(strUnit == "G"){
              dFreeSpace += strNum.toDouble();
         }else{
               if(strUnit == "M")
                   dFreeSpace += strNum.toDouble()/1024;
               else
                    dFreeSpace += strNum.toDouble()/(1024*1024);
          }
    }
    QString strFreeSpace = QString::number(dFreeSpace, 'f', 4);
    ui->cardspaceLabel->setText(strFreeSpace);
#endif
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
    qDebug()<<index;
}

