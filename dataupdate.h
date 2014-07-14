#ifndef DATAUPDATE_H
#define DATAUPDATE_H

#include "global.h"
#include "sqlopt.h"

typedef struct APK_INFO{
    QString  apkId;
    qint32    counter;
    qint32   icon;
    qint32   run;
    qint32   sort;
    QString packagePath;
    QString md5;
}ApkInfo;

class DataUpdate : public QObject
{
    Q_OBJECT
public:
    explicit DataUpdate(QObject *parent = 0);
    ~DataUpdate();
    
public:
    void GetDeviceVer(); //0 无更新 1 成功  2失败
    void GetApkLibVer(); //0 无更新 1 成功  2失败 3 不完全
    void GetPkgLibVer(); //0 无更新 1 成功  2失败
    void updateData();

    void mkdir(QString  path);
    void mk_filedir(QString  path);
    QString getFilePath();
    void setApkFile(const QString& apkfile);
    QString getApkFile();
    void setAPKURL(string apkpath);
    string  getAPKURL();
    void setFilePath(const QString& fileName);
    bool copyFileToPath(QString sourceDir ,QString toDir, bool coverFileIfExist) ;
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
    SqlOpt *sqlopt;

    QFile* m_dFile;

    devDB m_devDB;
    devDB m_pkgDB;
    devDB m_apkDB;
    devDB m_mblDB;

    QString m_apkIdStr;
    QString m_filePath;
    QString m_preMd5;
    QString m_apkFile;

    int Apk_Update_finish;

    bool m_bDevState;
    bool m_bApkState;
    bool m_bPkgState;
};

#endif // DATAUPDATE_H
