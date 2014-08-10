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
    int startUploadFile(int& failNum, int& okNum);
    void uploadBlock(const QString& data, bool isLoop);
    void Up100Block(const QList<QPair<QString, QString> > pairList);

    static QStringList GetAllFiles(QString strPath);
    static QString mkUploadData(const QList<QPair<QString, QString> > pairList);

    static FileUpload* getFileUpload();

private:
    QNetworkAccessManager* m_netFileManager;
    QNetworkAccessManager* m_netRealManager;
    QFileInfo m_curFileInfo;
    int m_nUpFaildRetryNum;
    int m_nUpFaildNum;
    int m_nUpSuccessedNum;
    logDB m_logDB;
    reportDB m_rptDB;

    static FileUpload* s_self;

private:
    void UpOneBlock(const QByteArray& BlockData, const QString& FileBName, const QString& md5);

signals:
    void SetUpState(bool bState);

public slots:
    void UpFinishFile(QNetworkReply* Reply);

    void UpRealBlock(const QString& str, const QString& id);
    void UpFinishData(QNetworkReply* Reply);
};

#endif // FILEUPLOAD_H
