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
    QStringList GetAllFiles(QString strPath);
    int startUpload();

private:
    QNetworkAccessManager* m_netManager;
    QFileInfo m_curFileInfo;
    int m_nUpFaildRetryNum;
    int m_nUpFaildNum;
    logDB m_logDB;

private:
    void UpOneBlock(const QByteArray& BlockData, const QString& FileBName, const QString& md5);

signals:
    void SetUpState(bool bState);

public slots:
    void UpFinishSingleFile(QNetworkReply* Reply);
};

#endif // FILEUPLOAD_H
