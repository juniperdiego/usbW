#include "upstate.h"
#include "ui_upstate.h"

UpState::UpState(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UpState)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("更新状态"));

    bDevState = false;
    bPkgState = false;
    bApkState = false;
}
void UpState::SetState(bool bDevStateIn, bool bPkgStateIn, bool bApkStateIn)
{
    bDevState = bDevStateIn;
    bPkgState = bPkgStateIn;
    bApkState = bApkStateIn;

    QString strState;
    if (bDevState)
        strState += "软件版本更新成功!\n";
    else
        strState += "软件版本更新失败!\n";
    if(bPkgState)
        strState += "安装包数据库更新成功!\n";
    else
        strState += "安装包数据库更新失败\n";
    if(bApkState)
        strState += "安装包更新成功\n";
    else
        strState += "安装包更新失败\n";
    ui->StateLab->setText(strState);
}
void UpState::OnConfirm()
{
    if (bDevState && bPkgState && bApkState)
        accept();
    else
        reject();
}
UpState::~UpState()
{
    delete ui;
}

