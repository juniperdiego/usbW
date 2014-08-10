#include "json/json.h"
#include "global.h"
#include "fileupload.h"
#include "dataupdate.h"
#include "tongxin.h"
#include <QtDebug>

using QtJson::JsonObject;
using QtJson::JsonArray;

FileUpload* FileUpload::s_self = NULL;

FileUpload::FileUpload(QObject *parent) :
    QObject(parent)
{
    this->m_nUpFaildRetryNum = 2;
    this->m_nUpFaildNum = 0;
    this->m_nUpSuccessedNum = 0;
    this->m_netFileManager = new QNetworkAccessManager(this);
    this->m_netRealManager = new QNetworkAccessManager(this);

    connect(tongXin::getTongXin(), SIGNAL(uploadData(const QString&, const QString&)), 
            this, SLOT(UpRealBlock(const QString&, const QString&)));
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
#if 0
        for (int i = 0; i < OneLine.length(); ++i)
        {
            OneLine[i] = OneLine[i] ^ ENCYPT_BIT;
        }
#endif

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
        m_nUpSuccessedNum++;
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
        JsonArray datalist = up_rsp_res["dataList"].toList();
        int id;
        bool active;
        foreach( QVariant atom, datalist)
        {
            JsonObject data_map = atom.toMap();
            active = data_map["active"].toBool();
            if (active)
            {
                id = data_map["id"].toInt();
                m_rptDB.setUpload(id);
            }
        }

    }
    else if (status == 1)
    {
    }
}

int FileUpload::startUploadFile(int& failNum, int& okNum)
{
    m_nUpFaildNum = 0;
    m_nUpSuccessedNum = 0;
    if (!Global::s_netState) return -2;
    QStringList LogLst = GetAllFiles(ENCYPT_LOG_PATH);
    if (LogLst.count() == 0) return -1;
    QString strLog;
    foreach(strLog, LogLst)
    {
        UpSingleFile(strLog);
    }

    failNum = m_nUpFaildNum;
    okNum = m_nUpSuccessedNum;

    return 0;
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

void FileUpload::UpRealBlock(const QString& str, const QString& id)
{
    QList<QPair<QString, QString> > pairList;
    pairList.append(qMakePair(str, id));
    QString data = mkUploadData(pairList);

    uploadBlock(data, false);
#if 0
    QByteArray BlockData = data.toLatin1();
    qDebug()<<"real time upload"<<BlockData;
    string urlStr = URL_UPLOAD_DATA;
    QByteArray appArry("data=");
    appArry.append(BlockData);

    QNetworkRequest request(QUrl(urlStr.c_str()));

    m_netRealManager->post(request, appArry);

    //QEventLoop loop;
    QObject::connect(m_netRealManager,SIGNAL(finished(QNetworkReply*)), this, SLOT(UpFinishData(QNetworkReply*)));
    //QObject::connect(m_netRealManager, SIGNAL(finished(QNetworkReply*)), &loop, SLOT(quit()));
    //loop.exec();
#endif
}

void FileUpload::Up100Block(const QList<QPair<QString, QString> > pairList)
{
    QString data = mkUploadData(pairList);

    uploadBlock(data, false);
}

void FileUpload::uploadBlock(const QString& data, bool isLoop)
{
    QByteArray BlockData = data.toLatin1();
    qDebug()<<"real time upload"<<BlockData;
    string urlStr = URL_UPLOAD_DATA;
    QByteArray appArry("data=");
    appArry.append(BlockData);

    QNetworkRequest request(QUrl(urlStr.c_str()));

    m_netRealManager->post(request, appArry);

    QObject::connect(m_netRealManager,SIGNAL(finished(QNetworkReply*)), this, SLOT(UpFinishData(QNetworkReply*)));
    if (isLoop)
    {
        QEventLoop loop;
        QObject::connect(m_netRealManager, SIGNAL(finished(QNetworkReply*)), &loop, SLOT(quit()));
        loop.exec();
    }
}

QString FileUpload::mkUploadData(const QList<QPair<QString, QString> > pairList)
{
    JsonArray datas;
    JsonObject data;
    for (int i = 0; i < pairList.count(); ++i)
    {
        //string content = Global::encyptStr(pairList[i].first.trimmed().toStdString());
        //data["content"] = QLatin1String(content.c_str());
        data["content"] = pairList[i].first.trimmed();
        data["id"] = pairList[i].second.trimmed();
        datas.append(data);
    }

    return QtJson::serialize(datas);
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

