#ifndef DATAUPDATE_H
#define DATAUPDATE_H

#include "global.h"

//0 成功有更新 1 失败  2成功无更新 3下载不完全 4服务器出错

class DataUpdate : public QObject
{
    Q_OBJECT
public:
    explicit DataUpdate(QObject *parent = 0);
    ~DataUpdate();
    
public:
    void GetDeviceVer(); 
    void GetApkLibVer(); 
    void GetPkgLibVer(); 
    void updateData();

    bool copyFile(const QString& sourceFile, const QString& toFile, bool isOverwrite) ;
    QString getFileMd5(QString filepath);

    void Download_File(const QString& url, const QString& fileName);
    bool MD5_Check(QString strFilePath, QString md5);

    int GetDevState();
    int GetApkState();
    int GetPkgState();

signals:
    void CloseUp();
    void devFinish();

public slots:
   void DevFinish();
   void ApkFinish();
   void PkgFinish();
   void DownloadRead();
   void DownloadFinish();
   void quit();

   void ApkFileWrite(QNetworkReply*);

private:
    QNetworkAccessManager* m_netManager;
    QNetworkReply* m_netReply;
    QFile* m_dFile;

    devDB m_devDB;
    pkgDB m_pkgDB;
    apkDB m_apkDB;
    mblDB m_mblDB;

    QString m_apkIdStr;
    QString m_filePath;
    QString m_preMd5;
    QString m_apkFile;

    int Apk_Update_finish;

    int m_devState;
    int m_apkState;
    int m_pkgState;
};

#endif // DATAUPDATE_H
