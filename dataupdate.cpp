//#include "parser.h"
#include "json/json.h"
#include "dataupdate.h"

using QtJson::JsonObject;
using QtJson::JsonArray;

#define HAVE_QJSON

DataUpdate::DataUpdate(QObject *parent) :
    QObject(parent)
{
    m_netManager = new QNetworkAccessManager;

    this->m_bDevState = false;
    this->m_bApkState = false;
    this->m_bPkgState = false;
    sqlopt = new SqlOpt;
    sqlopt->sqlinit();
}
DataUpdate::~DataUpdate()
{
}
void DataUpdate::GetDeviceVer()
{
    string devVer;
    m_devDB.get(DEV_VER, devVer);
    cout<<"GetDeviceVer "<<devVer<<endl;
    QNetworkRequest request(QUrl(tr(URL_DEVVER)));
    QByteArray appArry("code=");
    appArry.append(QString::fromStdString(Global::g_DevID));
    appArry.append("&version=");
    //appArry.append(QString::fromStdString(devVer));
    appArry.append(QString::fromStdString("1.0"));
    m_netReply = m_netManager->post(request, appArry);
    QEventLoop loop;
    QObject::connect(m_netReply, SIGNAL(finished()), this, SLOT(DevFinish()));
    QObject::connect(m_netReply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
}

void DataUpdate::GetApkLibVer()
{
    string apkVer;
    m_devDB.get(APK_VER, apkVer);
    cout<<"GetApkLibVer "<<apkVer<<endl;
    QNetworkRequest request(QUrl(tr(URL_APKLIBVER)));
    QByteArray appArry("code=");
    appArry.append(QString::fromStdString(Global::g_DevID));
    appArry.append("&apkVersion=");
    appArry.append(QString::fromStdString(apkVer));
    m_netReply = m_netManager->post(request, appArry);
    QEventLoop loop;
    QObject::connect(m_netReply, SIGNAL(finished()), this, SLOT(ApkFinish()));
    QObject::connect(m_netReply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    qDebug()<<"update apk ok";
}

void DataUpdate::GetPkgLibVer()
{
    string apkVer, pkgVer;
    m_devDB.get(PKG_VER, apkVer);
    m_devDB.get(PKG_VER, pkgVer);
    cout<<"GetPkgLibVer "<<pkgVer<<apkVer<<endl;
    QNetworkRequest request(QUrl(tr(URL_PKGLIBVER)));
    QByteArray appArry("code=");
    appArry.append(QString::fromStdString(Global::g_DevID));
    appArry.append("&apkVersion=");
    appArry.append(QString::fromStdString(apkVer));
    appArry.append("&pkgVersion=");
    appArry.append(QString::fromStdString(pkgVer));
    m_netReply = m_netManager->post(request, appArry);
    //QEventLoop loop;
    QObject::connect(m_netReply, SIGNAL(finished()), this, SLOT(PkgFinish()));
    //QObject::connect(m_netReply, SIGNAL(finished()), &loop, SLOT(quit()));
    //loop.exec();
   
    qDebug()<<"update pkg ok";
}

void DataUpdate::DevFinish()
{
#ifdef HAVE_QJSON
    string org_cid;
    m_devDB.get(CHAN_ID, org_cid);
    QByteArray dev_rsp_byte = m_netReply->readAll();
    QString dev_rsp_str = QString(dev_rsp_byte);
    m_netReply->deleteLater();
    qDebug()<<dev_rsp_str;
    bool ok;
    //QJson::Parser parser;
    if (dev_rsp_str.size()==0){
        return;
    }
    //QVariantMap dev_rsp_res = parser.parse(dev_rsp_str.toUtf8(), &ok).toMap();
    JsonObject dev_rsp_res = QtJson::parse(dev_rsp_str, ok).toMap();
    string cid=dev_rsp_res["cid"].toString().toStdString();
    if ( cid != org_cid){
        m_devDB.set(APK_VER, "0");
        m_devDB.set(PKG_VER, "0");
        m_devDB.set(CHAN_ID, cid);
    }
    qint32  nDevVerState=dev_rsp_res["status"].toInt();
    if( nDevVerState == 0){
        m_bDevState = true;
        return;
    }else if(nDevVerState == 1){
        m_bDevState = false;
    }
    else{
        QString path=dev_rsp_res["path"].toString();
        QString dev_md5=dev_rsp_res["md5value"].toString();
        QString filename= SPIRIT_PATH;
        Download_File(path, filename);

        if (MD5_Check(filename, dev_md5))
        {
            m_bDevState = true;
            emit devFinish();
        }
    }
#endif
}

void DataUpdate::ApkFinish()
{
#ifdef HAVE_QJSON
    QByteArray apk_rsp_byte = m_netReply->readAll();
    QString apk_rsp_str = QString(apk_rsp_byte);
    //QString apk_rsp_str = "{\"apkList\":[{\"apkId\":12,\"md5value\":\"27645ca17ac1c269e67862fcc0f1d2e3\",\"packagePath\":\"com.mapbar.android.accompany\",\"path\":\"http://download.redis.io/releases/redis-2.8.12.tar.gz\",\"type\":0},{\"apkId\":3,\"md5value\":\"d94e494566cb9d0b12c0d70aaec4543f\",\"packagePath\":\"air.com.wuba.bangbang\",\"path\":\"http://download.redis.io/releases/redis-2.8.12.tar.gz\",\"type\":0},{\"apkId\":5,\"md5value\":\"27645ca17ac1c269e67862fcc0f1d2e3\",\"packagePath\":\"com.mapbar.android.accompany\",\"path\":\"http://download.redis.io/releases/redis-2.8.12.tar.gz\",\"type\":0},{\"apkId\":7,\"md5value\":\"27645ca17ac1c269e67862fcc0f1d2e3\",\"packagePath\":\"com.qihoo360pp.paycentre\",\"path\":\"http://download.redis.io/releases/redis-2.8.12.tar.gz\",\"type\":0},{\"apkId\":8,\"md5value\":\"27645ca17ac1c269e67862fcc0f1d2e3\",\"packagePath\":\"com.qihoo360.antilostwatch\",\"path\":\"http://download.redis.io/releases/redis-2.8.12.tar.gz\",\"type\":0}],\"status\":2,\"version\":\"1390999000\"}";
    qDebug()<<apk_rsp_str;
    bool ok;
    //QJson::Parser parser;
    bool  apk_flag = true;
    if (apk_rsp_str.size()==0){
        apk_flag = false;
        return;
    }
    //QVariantMap apk_rsp_res = parser.parse(apk_rsp_str.toUtf8(), &ok).toMap();
    JsonObject apk_rsp_res = QtJson::parse(apk_rsp_str, ok).toMap();
    QString apkVersion=apk_rsp_res["version"].toString();
    qint32  nApkVerState=apk_rsp_res["status"].toInt();

    if( nApkVerState==0){
        apk_flag = true;
        return;
    }else if(nApkVerState == 1 ){
        apk_flag = false;
        return;
    }else{
        //QVariantList apklist = apk_rsp_res["apkList"].toList();
        JsonArray apklist = apk_rsp_res["apkList"].toList();
        foreach( QVariant atom, apklist){
            //QVariantMap  apk_map = atom.toMap();
            JsonObject apk_map = atom.toMap();
            m_apkIdStr = apk_map["apkId"].toString();
            QString apk_file_name ;
            apk_file_name = TMP_PATH + m_apkIdStr;
            setApkFile(m_apkIdStr);
            m_preMd5 = apk_map["md5value"].toString();
            QString packagePath = apk_map["packagePath"].toString();
            sqlopt->apk_update_packagePath(m_apkIdStr.toStdString(), packagePath.toStdString());

             QString path = apk_map["path"].toString();
             string ApkPath = path.toStdString();
             if( ApkPath.size() > 0){

                QNetworkRequest Down_Reqrequest(QUrl(tr(ApkPath.c_str())));
                m_netReply = m_netManager->get(Down_Reqrequest);
                QEventLoop loop;
                QObject::connect(m_netManager, SIGNAL(finished(QNetworkReply*)),this, SLOT(ApkFileWrite(QNetworkReply*)));
                QObject::connect(m_netManager, SIGNAL(finished(QNetworkReply*)), &loop, SLOT(quit()));
                loop.exec();
             }else{  // path == NULL
                    apk_flag = false;
           }
            //QNetwork
        }
        if(  Apk_Update_finish == Apk_Update_finish){
              m_bApkState = true;
              //sqlopt->dev_update("apkversion", apkVersion.toStdString());
              m_devDB.set(APK_VER, apkVersion.toStdString());
              GetPkgLibVer();
         }else{
              m_bApkState= false;
        }
    }
    m_netReply->deleteLater();
#endif
}

void DataUpdate::quit()
{
    if (m_netReply)
        m_netReply->abort();
}

void DataUpdate::PkgFinish()
{
#ifdef HAVE_QJSON
    QByteArray pkg_rsp_byte = m_netReply->readAll();
    QString pkg_rsp_str = QString(pkg_rsp_byte);
//   QString pkg_rsp_str = "{\"commonPkg\":{\"apkList\":[{\"apkId\":7,\"counter\":0,\"icon\":0,\"run\":1,\"sort\":0},{\"apkId\":8,\"counter\":0,\"icon\":0,\"run\":0,\"sort\":1},{\"apkId\":5,\"counter\":0,\"icon\":0,\"run\":0,\"sort\":2},{\"apkId\":12,\"counter\":0,\"icon\":0,\"run\":0,\"sort\":3},{\"apkId\":3,\"counter\":0,\"icon\":0,\"run\":0,\"sort\":4}],\"batchCode\":\"TY2\",\"modelList\":[],\"name\":\"common_pkg#TY2\",\"packageId\":14,\"type\":0},\"pkgList\":[],\"pkgVersion\":\"1404229444159\",\"status\":2}";
    qDebug()<<pkg_rsp_str;
    bool ok;
    //QJson::Parser parser;
    bool  pkg_flag = true;
    if (pkg_rsp_str.size()==0){
        pkg_flag = false;
        return;
    }
    //QVariantMap pkg_rsp_res = parser.parse(pkg_rsp_str.toUtf8(), &ok).toMap();
    JsonObject pkg_rsp_res = QtJson::parse(pkg_rsp_str, ok).toMap();
    QString pkgVersion=pkg_rsp_res["pkgVersion"].toString();
    qint32  status=pkg_rsp_res["status"].toInt();
    if(  status == 0 ){
        pkg_flag = true;
        //
        return;
    }else if(status == 1 ){
        pkg_flag = false;
        return;
    }else{
        QString md5;
        QString apk_path;
        //QVariantList apkList;
        char  date[12];
        sqlopt->get_date(date, 12, 0);
        QString date_today = date;
        if( pkg_rsp_res["commonPkg"].isNull() ) {
        }else{
            //QVariantMap commpkg = pkg_rsp_res["commonPkg"].toMap();
            JsonObject commpkg = pkg_rsp_res["commonPkg"].toMap();
            QString common_id = "common";
            QString batchCode = commpkg["batchCode"].toString();
           // QString modeList = "";
            QString name = commpkg["name"].toString();
            QString packageId = commpkg["packageId"].toString();
            sqlopt->mob_update( common_id.toStdString(), packageId.toStdString());
            qint8 type = commpkg["type"].toInt();
      //      QList<APK_INFO> apk_ins_list;
            //QVariantList apkList = commpkg["apkList"].toList();
            JsonArray apkList = commpkg["apkList"].toList();
            int length=apkList.size();
            QString apk_sort;
            foreach (QVariant apkinfo, apkList) {
                //QVariantMap apk_info = apkinfo.toMap();
                JsonObject apk_info = apkinfo.toMap();
                QString apkid = apk_info["apkId"].toString();
                qint32 counter = apk_info["counter"].toInt();
                qint32 icon = apk_info["icon"].toInt();
                qint32 run = apk_info["run"].toInt();
                qint32 sort = apk_info["sort"].toInt();
                apk_sort += apkid;
                apk_sort += ",";
                sqlopt->apk_update(apkid.toStdString(), name.toStdString(), counter, icon, run);
            }

            apk_sort.chop(1);
            //           pkg_update( const string pkg_id, const string pkg_name, const string apk_list, const int apk_sum, const string date, const string batchCode);
            sqlopt->pkg_update( packageId.toStdString(), name.toStdString(), apk_sort.toStdString(), batchCode.toStdString(),length, date_today.toStdString());
            //sqlite3  dev common;
            //sqlite3  pkg
        }
         if( ! pkg_rsp_res["pkgList"].isNull() ) {

            QString atom_batchcode;
            QString atom_name;
            QString atom_id;
            QString atom_packageid;
            QString atom_apksort;
            qint32  atom_type;
            //QVariantList apk_list;
            JsonArray apk_list;
            //QVariantList mob_list;
            JsonArray mob_list;

            //QVariantList PkgList = pkg_rsp_res["pkgList"].toList();
            JsonArray PkgList = pkg_rsp_res["pkgList"].toList();

            foreach (QVariant atom_list, PkgList) {
                //QVariantMap Pkg_atom = atom_list.toMap();
                JsonObject Pkg_atom = atom_list.toMap();
                atom_batchcode = Pkg_atom["batchCode"].toString();
                atom_name = Pkg_atom["name"].toString();
                atom_type = Pkg_atom["type"].toInt();
                atom_id = Pkg_atom["packageId"].toString();
                apk_list = Pkg_atom["apkList"].toList();
                QString apksort;
                foreach( QVariant atom,  apk_list){
                    //QVariantMap apkinfo = atom.toMap();
                    JsonObject apkinfo = atom.toMap();
                    QString apkid = apkinfo["apkId"].toString();
                    qint32 counter = apkinfo["counter"].toInt();
                    qint32 icon = apkinfo["icon"].toInt();
                    qint32 run = apkinfo["run"].toInt();
                    qint32 sort = apkinfo["sort"].toInt();
                    sqlopt->apk_update(apkid.toStdString(), atom_name.toStdString(), counter, icon, run);

                    apksort += apkid;
                }
                apksort.chop(1);
                sqlopt->pkg_update(atom_id.toStdString(), atom_name.toStdString(), apksort.toStdString(), apk_list.size(), date_today.toStdString()   );
                mob_list = Pkg_atom["modelList"].toList();
                foreach( QVariant atom, mob_list){
                    QString mob = atom.toString();
                    sqlopt->mob_update(mob.toStdString(), atom_name.toStdString());
                    //insert
                }
            }
         }
     }
    m_bPkgState = true;
    sqlopt->dev_update("pkgversion", pkgVersion.toStdString());
    m_netReply->deleteLater();
#endif
}

void DataUpdate::updateData()
{
    GetApkLibVer();
    emit CloseUp();
}

void DataUpdate::Download_File(const QString& urlStr, const QString& fileName)
{
    if(QFile::exists(fileName))
    {
        QFile::remove(fileName);
    }

    m_dFile = new QFile(fileName);
    if( !m_dFile->open(QIODevice::WriteOnly))
    {
        m_dFile->close();
        m_dFile = 0;
    }

    m_netReply = m_netManager->get(QNetworkRequest(QUrl(urlStr)));
    setFilePath(fileName);

    QEventLoop loop;
    QObject::connect(m_netReply, SIGNAL(readyRead()),this,SLOT(DownloadRead()));
    QObject::connect(m_netReply, SIGNAL(finished()), this, SLOT(DownloadFinish()));
    QObject::connect(m_netReply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
}

void DataUpdate::DownloadRead()
{
    if(m_dFile){
        m_dFile->write(m_netReply->readAll());
    }
}
void DataUpdate::DownloadFinish()
{
    m_dFile->flush();
    m_dFile->close();
    m_netReply->deleteLater();
}

QString DataUpdate::getFilePath()
{
    return m_filePath;
}

void DataUpdate::setFilePath(const QString& filepath)
{
    m_filePath = filepath;
}

void DataUpdate::setApkFile(const QString& apkfile){
    m_apkFile = apkfile;
}

QString DataUpdate::getApkFile(){
    return m_apkFile;
}

bool DataUpdate::MD5_Check(QString strFilePath, QString md5){
    
    QFile file(strFilePath);
    if (!file.exists()) return false;
    else if (file.size() == 0) return false;

    QString md5_tmp = getFileMd5(strFilePath);
    qDebug()<< strFilePath << md5 << md5_tmp;
    QString md5_1 = md5_tmp.toLower();
    QString md5_2 = md5.toLower();
    if(md5_2 == md5_1){
        return true;
    }
    return false;
}

void DataUpdate::ApkFileWrite(QNetworkReply* Reply_apk){
    qDebug() << m_apkIdStr;
    //QString apk_id = QString::fromStdString(getApkFile());
    QString file_name;
    file_name = TMP_PATH + m_apkIdStr;
    QFile fd(file_name);

    mkdir(file_name);

    if(fd.open(QIODevice::WriteOnly)){
        fd.write(Reply_apk->readAll());               //////////budge////////
    }
    fd.flush();
    fd.close();
    if (MD5_Check( file_name , m_preMd5) ){
           //sqllite3  string apk_info = sql_opt.get_all();
           QString apk_final_path;
           QString pkg_id;
           int a, b;
           pkg_id = QString::fromStdString( sqlopt->apk_get_path( m_apkIdStr.toStdString(), &a, &b));
            apk_final_path = APK_PATH + pkg_id;

           apk_final_path +=  "/" + m_apkIdStr + ".apk";
           mk_filedir(apk_final_path);
           if (copyFileToPath(file_name, apk_final_path, true )){
               //sqlite3 change data;
               sqlopt->apk_update(m_apkIdStr.toStdString(), m_preMd5.toStdString());
               Apk_Update_finish += 1;
           }
     }else{
           QFile::remove(file_name);
     }
    m_netReply->deleteLater();
}

bool DataUpdate::copyFileToPath(QString sourceDir ,QString toDir, bool coverFileIfExist)
{
    toDir.replace("\\","/");
    if (sourceDir == toDir){
        return true;
    }
    if (!QFile::exists(sourceDir)){
        return false;
    }
    mkdir(toDir);
    if (QFile::exists(toDir)){
        if(coverFileIfExist){
            QFile::remove(toDir);
        }
    }//end if

    if(!QFile::copy(sourceDir, toDir))
    {
        return false;
    }
    return true;
}

int DataUpdate::GetDevState()
{
    return this->m_bDevState;
}
int DataUpdate::GetApkState()
{
    return this->m_bApkState;
}
int DataUpdate::GetPkgState()
{
   return  this->m_bPkgState;
}

QString DataUpdate::getFileMd5(QString filePath)
{
    QFile localFile(filePath);

    if (!localFile.open(QFile::ReadOnly))
    {
        qDebug() << "file open error.";
        return "";
    }

    QCryptographicHash ch(QCryptographicHash::Md5);

    quint64 totalBytes = 0;
    quint64 bytesWritten = 0;
    quint64 bytesToWrite = 0;
    quint64 loadSize = 1024 * 4;
    QByteArray buf;

    totalBytes = localFile.size();
    bytesToWrite = totalBytes;

    while (1)
    {
        if(bytesToWrite > 0)
        {
            buf = localFile.read(qMin(bytesToWrite, loadSize));
            ch.addData(buf);
            bytesWritten += buf.length();
            bytesToWrite -= buf.length();
            buf.resize(0);
        }
        else
        {
            break;
        }

        if(bytesWritten == totalBytes)
        {
            break;
        }
    }

    localFile.close();
    QByteArray md5 = ch.result();
    return md5.toHex();
}


void DataUpdate::mkdir(QString  path){
    static QDir tmp;
    QStringList  lpath = path.split("/", QString::SkipEmptyParts);
    lpath.removeLast();
    QString new_path;
    foreach( QString  atom, lpath){
        new_path += "/";
        new_path += atom;
        if( ! tmp.exists(new_path)){
            tmp.mkdir( new_path);
        }
    }
}

void DataUpdate::mk_filedir(QString  path){
    static QDir tmp;
    QStringList  lpath = path.split("/", QString::SkipEmptyParts);
    QString new_path;
    foreach( QString  atom, lpath){
        new_path += "/";
        new_path += atom;
        if( ! tmp.exists(new_path)){
            tmp.mkdir( new_path);
        }
    }
    tmp.rmdir(new_path);
}

