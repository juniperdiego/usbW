#include "json/json.h"
#include "global.h"
#include "fileupload.h"
#include "dataupdate.h"
#include <QtDebug>

using QtJson::JsonObject;
using QtJson::JsonArray;

FileUpload* FileUpload::s_self = NULL;

FileUpload::FileUpload(QObject *parent) :
    QObject(parent)
{
    this->m_nUpFaildRetryNum = 2;
    this->m_nUpFaildNum = 0;
    this->m_netFileManager = new QNetworkAccessManager(this);
    this->m_netRealManager = new QNetworkAccessManager(this);
}

FileUpload::~FileUpload()
{
}

FileUpload* FileUpload::getFileUpload()
{
    if (s_self == NULL)
        s_self = new FileUpload;

    return s_self;
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
        for (int i = 0; i < OneLine.length(); ++i)
        {
            OneLine[i] = OneLine[i] ^ ENCYPT_BIT;
        }

        BlockData.append(OneLine);
    }

    QString md5 = DataUpdate::getFileMd5(strFile); 
    UpOneBlock(BlockData, FileID, md5);
}
void FileUpload::UpOneBlock(const QByteArray& BlockData, const QString& fileBName, const QString& md5)
{
    qDebug()<<"UpOneBlock"<<BlockData;
    string urlStr = URL_UPLOAD;
    urlStr += "?file=";
    urlStr += qPrintable(fileBName);
    urlStr += "&deviceCode=";
    urlStr += Global::g_DevID.c_str();

    QNetworkRequest request(QUrl(urlStr.c_str()));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/octet-stream");

    m_netFileManager->post(request, BlockData);

    QEventLoop loop;
    QObject::connect(m_netFileManager,SIGNAL(finished(QNetworkReply*)), this, SLOT(UpFinishFile(QNetworkReply*)));
    QObject::connect(m_netFileManager, SIGNAL(finished(QNetworkReply*)), &loop, SLOT(quit()));
    loop.exec();
}
void FileUpload::UpFinishFile(QNetworkReply* Reply_Up)
{
    QByteArray replyByte = Reply_Up->readAll();
    QString replyStr = QString(replyByte);
    Reply_Up->deleteLater();
    qDebug()<<"file reply"<<replyStr;
    bool ok;
    if (replyStr.isEmpty()){
        return;
    }
    JsonObject up_rsp_res = QtJson::parse(replyStr, ok).toMap();
    int status=up_rsp_res["status"].toInt();
   
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
}

void FileUpload::UpFinishData(QNetworkReply* Reply_Up)
{
    QByteArray replyByte = Reply_Up->readAll();
    QString replyStr = QString(replyByte);
    Reply_Up->deleteLater();
    qDebug()<<"real replay"<<replyStr;
    bool ok;
    if (replyStr.isEmpty()){
        return;
    }
    JsonObject up_rsp_res = QtJson::parse(replyStr, ok).toMap();
    int status=up_rsp_res["status"].toInt();
   
    if (status == 0)
    {
    }
    else if (status == 1)
    {
    }
}

int FileUpload::startUploadFile()
{
    m_nUpFaildNum = 0;
    QStringList LogLst = GetAllFiles(ENCYPT_LOG_PATH);
    if (LogLst.count() == 0) return -1;
    QString strLog;
    foreach(strLog, LogLst)
    {
        UpSingleFile(strLog);
    }

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

void FileUpload::UpRealBlock(const string& str, const string& fileBName)
{
    QByteArray BlockData(str.c_str());
    qDebug()<<"real time upload"<<BlockData;
    string urlStr = URL_UPLOAD;
    urlStr += "?file=";
    urlStr += fileBName.c_str();
    urlStr += "&deviceCode=";
    urlStr += Global::g_DevID.c_str();

    QNetworkRequest request(QUrl(urlStr.c_str()));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/octet-stream");

    m_netRealManager->post(request, BlockData);

    //QEventLoop loop;
    QObject::connect(m_netRealManager,SIGNAL(finished(QNetworkReply*)), this, SLOT(UpFinishData(QNetworkReply*)));
    //QObject::connect(m_netRealManager, SIGNAL(finished(QNetworkReply*)), &loop, SLOT(quit()));
    //loop.exec();
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

