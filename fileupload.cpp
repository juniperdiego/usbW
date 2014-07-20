#include "json/json.h"
#include "global.h"
#include "fileupload.h"
#include "dataupdate.h"
#include <QtDebug>

using QtJson::JsonObject;
using QtJson::JsonArray;

FileUpload::FileUpload(QObject *parent) :
    QObject(parent)
{
    this->m_nUpFaildRetryNum = 2;
    this->m_nUpFaildNum = 0;
    this->m_netManager = new QNetworkAccessManager(this);
}
FileUpload::~FileUpload()
{
}

void FileUpload::UpSingleFile(const QString& strFile)
{
    QByteArray BlockData;
    m_curFileInfo.setFile(strFile);
    QString FileID = m_curFileInfo.fileName();
    QFile Fd(strFile);
    Fd.open(QIODevice::ReadOnly | QIODevice::Text);
    while(!Fd.atEnd())
    {
        QByteArray OneLine = Fd.readLine(MAXLINELEN);
#if 0
        char * crystr = OneLine.data();
        for( int i=0; i<OneLine.size(); i++){
            crystr[i] = crystr[i] ^ 0x12;
        }
        QByteArray byte( crystr);
        OneLine = byte;
#endif
        for (int i = 0; i < OneLine.length(); ++i)
        {
            //OneLine[i] = OneLine[i] ^ 0x12;
        }

        BlockData.append(OneLine);
        BlockData.append("\n");
    }
    //BlockData.remove(BlockData.size()-1,1);
    //BlockData.insert(0,tr("{["));
    //BlockData.insert(BlockData.size(),tr("]}"));
    //qDebug()<<BlockData<<"\n";

    QString md5 = DataUpdate::getFileMd5(strFile); 
    UpOneBlock(BlockData, FileID, md5);
}
void FileUpload::UpOneBlock(const QByteArray& BlockData, const QString& fileBName, const QString& md5)
{
    qDebug()<<"UpOneBlock"<<BlockData;
    string urlStr = URL_UPLOAD;
    urlStr += "?file=";
    urlStr += qPrintable(fileBName);

    QNetworkRequest request(QUrl(urlStr.c_str()));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/octet-stream");

    m_netManager->post(request, BlockData);

    QEventLoop loop;
    QObject::connect(m_netManager,SIGNAL(finished(QNetworkReply*)), this, SLOT(UpFinishSingleFile(QNetworkReply*)));
    QObject::connect(m_netManager, SIGNAL(finished(QNetworkReply*)), &loop, SLOT(quit()));
    loop.exec();
    //UpFinishSingleFile();
}
void FileUpload::UpFinishSingleFile(QNetworkReply* Reply_Up)
{
    QByteArray replyByte = Reply_Up->readAll();
    QString replyStr = QString(replyByte);
    Reply_Up->deleteLater();
    qDebug()<<replyStr;
    bool ok;
    if (replyStr.isEmpty()){
        return;
    }
    JsonObject up_rsp_res = QtJson::parse(replyStr, ok).toMap();
    int status=up_rsp_res["version"].toInt();
   
    if (status == 0)
    {
        logInfo log;
        QString baseName = m_curFileInfo.baseName(); 
        log.date = baseName.toStdString();
        log.isUploaded = true;
        m_logDB.set(log);
        QFile::remove(m_curFileInfo.absoluteFilePath());
    }
    else if (status == 1)
    {
        m_nUpFaildNum++;
    }
#if 0
    QByteArray Res = Reply_Up->readAll();
    //Test
//    QByteArray Res("{\"status\":1,\"id\":2014062101}");
    QJson::Parser ResParser;
    bool bFlag;
    QVariantMap ResMap = ResParser.parse(Res,&bFlag).toMap();
    QString FopenedFilePath = LOG_PATH;
    FopenedFilePath += tr("/");
    FopenedFilePath += ResMap["id"].toString();
    FopenedFilePath +=tr(".csv");
    QFile Fd(FopenedFilePath);
    QString strFileDate = ResMap["id"].toString().left(8);
    if(bFlag && Fd.exists())
    {
        if(ResMap["status"].toInt() == 1)
        {
            Fd.close();
            Fd.remove();
            ResetFaildNum();
            //写数据库
            this->Log_Sql->log_read_incr(strFileDate.toStdString());
           // disconnect(m_netManager,SIGNAL(finished(QNetworkReply*)), this, SLOT(UpFinishSingleFile(QNetworkReply*)));
        }
        else if(ResMap["status"].toInt() == 0)
        {
            AddFaildNum();
            if(this->m_nUpFaildNum <= this->m_nUpFaildRetryNum)
            {
                UpSingleFile(this->strFile);
            }
            else
            {
                ResetFaildNum();
                Fd.close();
                //disconnect(m_netManager,SIGNAL(finished(QNetworkReply*)), this, SLOT(UpFinishSingleFile(QNetworkReply*)));
            }
        }
        else
        {
            if(Fd.exists())
                Fd.close();
            //disconnect(m_netManager,SIGNAL(finished(QNetworkReply*)), this, SLOT(UpFinishSingleFile(QNetworkReply*)));
            qDebug()<<"Error status\n";
        }
    }
    else
   {
        qDebug()<<"Error parser or File not exsist\n";
        //disconnect(m_netManager,SIGNAL(finished(QNetworkReply*)), this, SLOT(UpFinishSingleFile(QNetworkReply*)));
   }
    loop->quit();
#endif
}

int FileUpload::startUpload()
{
    m_nUpFaildNum = 0;
    //emit SetUpState(true);
    QStringList LogLst = GetAllFiles(LOG_PATH);
    if (LogLst.count() == 0) return -1;
    QString strLog;
    foreach(strLog, LogLst)
    {
        UpSingleFile(strLog);
    }

    //emit SetUpState(false);

    return m_nUpFaildNum;
}

QStringList FileUpload::GetAllFiles(QString strPath)
{
    char time[32];
    getDate(time, 0);
    string timeStr(time);

    QDir dir(strPath);
    QFileInfoList FileInfoLst;
    QStringList strFileLst;
    strFileLst.clear();
    if( !dir.exists() )
    {
        return strFileLst;
    }
    dir.setFilter(QDir::Files | QDir::NoSymLinks);
    dir.setSorting(QDir::Time|QDir::Reversed);
    FileInfoLst = dir.entryInfoList();
    int nFileCount = FileInfoLst.count();
    if (nFileCount <= 0)
    {
        return strFileLst;
    }
    for(int i = 0; i < nFileCount; i++)
    {
        QString baseName = FileInfoLst[i].baseName();
        if (!baseName.startsWith(time))
            strFileLst.append(FileInfoLst.at(i).absoluteFilePath());
    }
    return strFileLst;
}

#if 0
void FileUpload::mergeLogFile(const QStringList& fileList)
{
    QStringList bNameList;
    for (int i = 0; i < fileList.count(); ++i)
    {
        QFileInfo fileInfo(fileList[i]);
        QString baseName = fileInfo.baseName();
        if (!bNameList.contains(baseName))
            bNameList.append(baseName);
    }

    for (int i = 0; i < bNameList.count(); ++i)
    {
        QString dateName = bNameList.section("_", 1, 1);
        dateName += "*";
        QRegExp regExp(dateName, Qt::CaseSensitive, QRegExp::WildcardUnix)
        QStringList filterList = fileList.filter(bNameList
    }
}
#endif

