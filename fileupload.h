#ifndef FILEUPLOAD_H
#define FILEUPLOAD_H

#include <QObject>
#include <QtNetwork>
#include "global.h"

class FileUpload : public QObject
{
    Q_OBJECT
public:
    explicit FileUpload(QObject *parent = 0);
    ~FileUpload();

    void  UpSingleFile(const QString& strFile);
    static QStringList GetAllFiles(QString strPath);
    int startUploadFile();

    void UpRealBlock(const string& str, const string& fileBName);

    static FileUpload* getFileUpload();

private:
    QNetworkAccessManager* m_netFileManager;
    QNetworkAccessManager* m_netRealManager;
    QFileInfo m_curFileInfo;
    int m_nUpFaildRetryNum;
    int m_nUpFaildNum;
    logDB m_logDB;

    static FileUpload* s_self;

private:
    void UpOneBlock(const QByteArray& BlockData, const QString& FileBName, const QString& md5);

signals:
    void SetUpState(bool bState);

public slots:
    void UpFinishFile(QNetworkReply* Reply);
    void UpFinishData(QNetworkReply* Reply);
};

#endif // FILEUPLOAD_H
