#include "shangchuan.h"
#include "ui_shangchuan.h"

Shangchuan::Shangchuan(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Shangchuan)
{
#ifdef ARM
    setWindowFlags(Qt::FramelessWindowHint);
#endif

    ui->setupUi(this);

    LabUpdateState = new QLabel;
    LabUpdateState->setVisible(false);
    MvUpdate = new QMovie(":/images/updating.gif");
    LabUpdateState->setMovie(MvUpdate);
    ui->horizontalLayout->addWidget(LabUpdateState);

    //set the date display policy
    ui->FromDataEdt->setDate(QDate::currentDate());
    ui->ToDataEdt->setDate(QDate::currentDate());

    ui->ResTabWid->setHorizontalHeaderLabels(QStringList()<< tr("日期")<<tr("上传文件")<<tr("上传结果"));
    ui->ResTabWid->setColumnWidth(0,150);
    ui->ResTabWid->setColumnWidth(1,350);
    ui->ResTabWid->setColumnWidth(2,210);
    ui->ResTabWid->setRowCount(12);
    this->setWindowTitle(tr("上传"));
    this->setFixedSize(800,480);
}

Shangchuan::~Shangchuan()
{
    delete ui;
}

void Shangchuan::updateContents()
{
    //QStringList files = FileUpload::GetAllFiles(ENCYPT_LOG_PATH); 
    //QString text1 = tr("上传文件(%1)").arg(files.count());
    //ui->UpdateBtn->setText(text1);

    //vector<reportInfo> rpts;
    //m_rptDB.getUnuploadedData(rpts); 
    //QString text2 = tr("上传数据(%1)").arg(rpts.size());
    //ui->UpdateDataBtn->setText(text2);
}

void Shangchuan::Return()
{
    this->close();
}
void Shangchuan::Search()
{
    vector<logInfo> res;
    string dateFrom = ui->FromDataEdt->text().remove('-').toStdString();
    string dateTo = ui->ToDataEdt->text().remove('-').toStdString();
    m_logDB.get(dateFrom, dateTo, res);
    //cout<<dateFrom<<"\t"<<dateTo<<"\t"<<res.size()<<endl;
    for (int nRow = 0; nRow < res.size(); nRow++)
    {
        for( int nCol = 0; nCol < 3; nCol++)
        {
            QTableWidgetItem* newItem = NULL;
            switch(nCol)
            {
            case 0:
                newItem = new QTableWidgetItem(QString::fromStdString(res[nRow].date.c_str()));
                break;
             case 1:
                {
                    QString strTotal = QString("%1.csv").arg(res[nRow].date.c_str());
                    newItem = new QTableWidgetItem(strTotal);
                    break;
                }
             case 2:
                {
                    QString strDone = QString("%1").arg(res[nRow].isUploaded ? "已上传" : "未上传");
                    newItem = new QTableWidgetItem(strDone);
                    break;
                }
            }
           ui->ResTabWid->setItem(nRow,nCol,newItem);
          }
    }
    res.clear();
}
void Shangchuan::Upload()
{
    int num = FileUpload::getFileUpload()->startUploadFile();

    QString strState;
    if (num == -1)
        strState = "没有文件需要上传!\n";
    else if (num > 0)
        strState = tr("%1个文件上传失败!\n").arg(num);
    else
        strState = "文件上传成功!\n";

    QMessageBox::information(this, windowTitle(), strState);
}

void Shangchuan::UploadData()
{
    vector<reportInfo> rpts;
    m_rptDB.getUnuploadedData(rpts); 

    QList<QPair<QString, QString> > pairList;
    unsigned int cnt = 0;
    for (size_t i = 0; i < rpts.size(); ++i)
    {
        string content = rpts[i].imei + "|"\
                + rpts[i].model + "|"\
                + rpts[i].chanID + "|"\
                + rpts[i].macAdd + "|"\
                + rpts[i].batchCode + "|"\
                + rpts[i].installDate; 
        int id = rpts[i].id;
        if( cnt < 100 )
        {
            pairList.append(qMakePair(QString(content.c_str()), QString().setNum(id)));
            cnt ++;
        }
        else
        {
            FileUpload::getFileUpload()->Up100Block(pairList);
            pairList.clear();
            cnt = 0;
        }
    }
    if (pairList.count() > 0)
    {
        FileUpload::getFileUpload()->Up100Block(pairList);
    }
}

