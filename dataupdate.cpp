//#include "parser.h"
#include "json/json.h"
#include "dataupdate.h"
#include <algorithm>

using QtJson::JsonObject;
using QtJson::JsonArray;

#define HAVE_QJSON

class apkSortInfo {
    public:
        string      apkID;
        bool        dIcon;
        bool        aRun;

    apkSortInfo()
            :
            dIcon(false), 
            aRun(false) 
    {
    };
};



bool cmp(const pair<apkSortInfo, int>& t1, const pair<apkSortInfo, int>& t2) {
    return t1.second < t2.second;
}

DataUpdate::DataUpdate(QObject *parent) :
    QObject(parent)
{
    m_netManager = new QNetworkAccessManager;

    m_devState = 1;
    m_apkState = 1;
    m_pkgState = 1;
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
    appArry.append(QString::fromStdString(devVer));
    //appArry.append(QString::fromStdString("0.9"));
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
    Apk_Update_finish = 0;
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
    m_devDB.get(APK_VER, apkVer);
    m_devDB.get(PKG_VER, pkgVer);
    cout<<"GetPkgLibVer ["<<pkgVer<<"] "<<apkVer<<endl;
    QNetworkRequest request(QUrl(tr(URL_PKGLIBVER)));
    QByteArray appArry("code=");
    appArry.append(QString::fromStdString(Global::g_DevID));
    appArry.append("&apkVersion=");
    appArry.append(QString::fromStdString(apkVer));
    appArry.append("&pkgVersion=");
    appArry.append(QString::fromStdString(pkgVer));
    m_netReply = m_netManager->post(request, appArry);
    QEventLoop loop;
    QObject::connect(m_netReply, SIGNAL(finished()), this, SLOT(PkgFinish()));
    QObject::connect(m_netReply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

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
    if (dev_rsp_str.isEmpty()){
        m_devState = 4;
        return;
    }
    //QVariantMap dev_rsp_res = parser.parse(dev_rsp_str.toUtf8(), &ok).toMap();
    JsonObject dev_rsp_res = QtJson::parse(dev_rsp_str, ok).toMap();
    Global::setSysTime(dev_rsp_res["date"].toString());
    string version=dev_rsp_res["version"].toString().toStdString();
    string cid=dev_rsp_res["cid"].toString().toStdString();

    if ( cid != org_cid){
        m_devDB.set(APK_VER, "0");
        m_devDB.set(PKG_VER, "0");
        //clear items of pkg and apk table
        m_pkgDB.clearTableItems();
        m_apkDB.clearTableItems();
        m_mblDB.clearTableItems();
        m_devDB.set(CHAN_ID, cid);
        // todo, rm all apk
        Global::clearApks();
    }
    int  nDevVerState=dev_rsp_res["status"].toInt();
    if( nDevVerState == 2){
        m_devState = 2;
        return;
    }else if(nDevVerState == 1){
        m_devState = 1;
        return;
    }
    else{
        QString path=dev_rsp_res["path"].toString();
        QString dev_md5=dev_rsp_res["md5value"].toString();
        QString filename= UPDATE_FILE_NAME;
        Download_File(path, filename);

        if (MD5_Check(filename, dev_md5))
        {
            m_devState = 0;
            Global::s_needRestart = true;
            m_devDB.set(DEV_VER, version);
        }
    }
    //emit devFinish();
#endif
}

void DataUpdate::ApkFinish()
{
#ifdef HAVE_QJSON
    QByteArray apk_rsp_byte = m_netReply->readAll();
    QString apk_rsp_str = QString(apk_rsp_byte);
    m_netReply->deleteLater();
    qDebug()<<apk_rsp_str;
    bool ok;
    //QJson::Parser parser;
    if (apk_rsp_str.isEmpty()){
        m_apkState = 4;
        return;
    }
    //QVariantMap apk_rsp_res = parser.parse(apk_rsp_str.toUtf8(), &ok).toMap();
    JsonObject apk_rsp_res = QtJson::parse(apk_rsp_str, ok).toMap();
    QString apkVersion=apk_rsp_res["version"].toString();
    m_devDB.set(APK_VER, apkVersion.toStdString());
    int  nApkVerState=apk_rsp_res["status"].toInt();

    if( nApkVerState == 2){
        m_apkState = 2;
        GetPkgLibVer();
        return;
    }else if(nApkVerState == 1 ){
        m_apkState = 1;
        return;
    }else{
        Apk_Update_finish = 0;
        apkInfo apkIn;
        //QVariantList apklist = apk_rsp_res["apkList"].toList();
        JsonArray apklist = apk_rsp_res["apkList"].toList();
        int apkNum = apklist.size();
        emit progress(0, apkNum);
        foreach( QVariant atom, apklist){
            //QVariantMap  apk_map = atom.toMap();
            JsonObject apk_map = atom.toMap();
            m_apkIdStr = apk_map["apkId"].toString();
            apkIn.apkID = m_apkIdStr.toStdString();
            QString apk_file_name ;
            apk_file_name = TMP_PATH + m_apkIdStr;
            m_preMd5 = apk_map["md5value"].toString();
            apkIn.md5 = apk_map["md5value"].toString().toStdString();
            //QString packagePath = apk_map["packagePath"].toString();
            apkIn.pkgPath = apk_map["packagePath"].toString().toStdString();
            //sqlopt->apk_update_packagePath(m_apkIdStr.toStdString(), packagePath.toStdString());

            QString path = apk_map["path"].toString();
            string ApkPath = path.toStdString();
            int apkOkNum = Apk_Update_finish;
            if(!ApkPath.empty()){
                QNetworkRequest Down_Reqrequest(QUrl(tr(ApkPath.c_str())));
                m_netManager->get(Down_Reqrequest);
                QEventLoop loop;
                QObject::connect(m_netManager, SIGNAL(finished(QNetworkReply*)),this, SLOT(ApkFileWrite(QNetworkReply*)));
                QObject::connect(m_netManager, SIGNAL(finished(QNetworkReply*)), &loop, SLOT(quit()));
                loop.exec();
            }else{  // path == NULL
                m_apkState = 4;
                return;
            }
            if ((apkOkNum+1) == Apk_Update_finish)
            {
                m_apkDB.set(apkIn);
                emit progress(Apk_Update_finish, apkNum);
            }
            else
            {
                m_apkState = 3;
                QObject::disconnect(m_netManager, SIGNAL(finished(QNetworkReply*)),this, SLOT(ApkFileWrite(QNetworkReply*)));
                return;
            }
        }
        QObject::disconnect(m_netManager, SIGNAL(finished(QNetworkReply*)),this, SLOT(ApkFileWrite(QNetworkReply*)));
        if(apkNum == Apk_Update_finish){
            m_apkState = 0;
            GetPkgLibVer();
        }else{
            m_apkState = 3;
            m_pkgState = 3;
        }
    }
#endif
}

void DataUpdate::quit()
{
    if (m_netReply)
        m_netReply->abort();
    m_netReply->deleteLater();
}

void DataUpdate::PkgFinish()
{
#ifdef HAVE_QJSON
    QByteArray pkg_rsp_byte = m_netReply->readAll();
    QString pkg_rsp_str = QString(pkg_rsp_byte);
    m_netReply->deleteLater();
    qDebug()<<"pkg reply = "<<pkg_rsp_str;
    bool ok;
    //QJson::Parser parser;
    if (pkg_rsp_str.isEmpty()){
        m_pkgState = 4;
        return;
    }
    //QVariantMap pkg_rsp_res = parser.parse(pkg_rsp_str.toUtf8(), &ok).toMap();
    JsonObject pkg_rsp_res = QtJson::parse(pkg_rsp_str, ok).toMap();
    QString pkgVersion=pkg_rsp_res["version"].toString();
    cout << "set PKG_VER\t[" << pkgVersion.toStdString() <<"]" << endl;
    m_devDB.set(PKG_VER, pkgVersion.toStdString());
    int  status=pkg_rsp_res["status"].toInt();
    if(  status == 2 ){
        m_pkgState = 2;
        return;
    }else if(status == 1 ){
        m_pkgState = 1;
        return;
    }else{
        QString md5;
        QString apk_path;
        //QVariantList apkList;
        char  date[12];
        getDate(date,  0);
        QString date_today = date;
        if(!pkg_rsp_res["commonPkg"].isNull() ) {
            pkgInfo pkgIn;
            //QVariantMap commpkg = pkg_rsp_res["commonPkg"].toMap();
            JsonObject commpkg = pkg_rsp_res["commonPkg"].toMap();
            
            if( !commpkg["packageId"].toString().isEmpty() ) 
            {
                pkgIn.pkgID = COMMON_PKG_NAME;
                pkgIn.batchCode = commpkg["batchCode"].toString().toStdString();
                pkgIn.pkgName = COMMON_PKG_NAME;


                JsonArray apkList = commpkg["apkList"].toList();
                int length=apkList.size();
                pkgIn.apkSum = length;
                pkgIn.date = date;

                //int type = commpkg["type"].toInt();
                vector<pair<apkSortInfo, int> > sortVector;
                foreach (QVariant apkinfo, apkList) {
                    JsonObject apk_info = apkinfo.toMap();

                    apkSortInfo apkIn;
                    apkIn.apkID = apk_info["apkId"].toString().toStdString();

                    if(apk_info["icon"].toInt() == 0)
                        apkIn.dIcon = false;
                    else
                        apkIn.dIcon = true;
                    if(apk_info["run"].toInt() == 0)
                        apkIn.aRun = false;
                    else
                        apkIn.aRun = true;

                    int sort = apk_info["sort"].toInt();

                    sortVector.push_back(pair<apkSortInfo,int>(apkIn, sort));
                }

                sort(sortVector.begin(), sortVector.end(), cmp);

                pkgIn.apkList.clear();
                for(size_t i= 0; i < sortVector.size(); i++)
                {
                    pkgIn.apkList.push_back(sortVector[i].first.apkID);
                }

                pkgIn.autoRunList.clear();
                for(size_t i= 0; i < sortVector.size(); i++)
                {
                    pkgIn.autoRunList.push_back(sortVector[i].first.aRun);
                }

                m_pkgDB.set(pkgIn);
            }
        }
        if(!pkg_rsp_res["pkgList"].isNull()) {

            QString atom_batchcode;
            QString atom_name;
            QString atom_id;
            QString atom_packageid;
            QString atom_apksort;
            //QVariantList apk_list;
            JsonArray apk_list;
            //QVariantList mob_list;
            JsonArray mob_list;

            //QVariantList PkgList = pkg_rsp_res["pkgList"].toList();
            JsonArray PkgList = pkg_rsp_res["pkgList"].toList();

            foreach (QVariant atom_list, PkgList) {
                pkgInfo pkgIn;
                //QVariantMap Pkg_atom = atom_list.toMap();
                JsonObject Pkg_atom = atom_list.toMap();

                pkgIn.pkgID = Pkg_atom["packageId"].toString().toStdString();
                pkgIn.pkgName = Pkg_atom["name"].toString().toStdString();
                pkgIn.batchCode = Pkg_atom["batchCode"].toString().toStdString();
                int type = Pkg_atom["type"].toInt();

                if(type == 2)//dlete the package
                {
                    m_pkgDB.deleteRecord(pkgIn.pkgID);
                    m_mblDB.deleteRecord(pkgIn.pkgID);
                    continue;
                }

                apk_list = Pkg_atom["apkList"].toList();
                vector<pair<apkSortInfo, int> > sortVector;
                foreach( QVariant atom,  apk_list){
                    apkSortInfo apkIn;
                    JsonObject apkMap= atom.toMap();

                    apkIn.apkID = apkMap["apkId"].toString().toStdString();

                    if(apkMap["icon"].toInt() == 0)
                        apkIn.dIcon = false;
                    else
                        apkIn.dIcon = true;
                    if(apkMap["run"].toInt() == 0)
                        apkIn.aRun = false;
                    else
                        apkIn.aRun = true;

                    int sort = apkMap["sort"].toInt();

                    sortVector.push_back(pair<apkSortInfo,int>(apkIn, sort));
                }

                sort(sortVector.begin(), sortVector.end(), cmp);

                pkgIn.apkList.clear();
                for(size_t i= 0; i < sortVector.size(); i++)
                {
                    pkgIn.apkList.push_back(sortVector[i].first.apkID);
                }

                pkgIn.autoRunList.clear();
                for(size_t i= 0; i < sortVector.size(); i++)
                {
                    pkgIn.autoRunList.push_back(sortVector[i].first.aRun);
                }

                pkgIn.apkSum = sortVector.size();
                pkgIn.date = date;

                m_pkgDB.set(pkgIn);

                //update mblDB
                mob_list = Pkg_atom["modelList"].toList();
                foreach( QVariant atom, mob_list){
                    QString mob = atom.toString();

                    mblInfo mblIn;
                    mblIn.mblID = mob.toStdString();
                    mblIn.pkgID = pkgIn.pkgID;
                    m_mblDB.set(mblIn);
                }
            }
        }
    }
    m_pkgState = 0;
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
    QString file_name = TMP_PATH;
    file_name += "/" + m_apkIdStr;
    QFile fd(file_name);
    if(fd.open(QIODevice::WriteOnly)){
        fd.write(Reply_apk->readAll());               //////////budge////////
    }
    fd.flush();
    fd.close();
    Reply_apk->deleteLater();
    if (MD5_Check( file_name , m_preMd5) ){
        QString apk_final_path = APK_PATH;
        apk_final_path +=  "/" + m_apkIdStr + ".apk";
        if (copyFile(file_name, apk_final_path, true)){
            Apk_Update_finish++;
        }
    }else{
        QFile::remove(file_name);
    }
}

bool DataUpdate::copyFile(const QString& sourceFile, const QString& toFile, bool isOverwrite)
{
    if (isOverwrite && QFile::exists(toFile))
        QFile::remove(toFile);

    if(!QFile::copy(sourceFile, toFile))
    {
        return false;
    }
    return true;
}

int DataUpdate::GetDevState()
{
    return m_devState;
}
int DataUpdate::GetApkState()
{
    return m_apkState;
}
int DataUpdate::GetPkgState()
{
    return  m_pkgState;
}

QString DataUpdate::getFileMd5(QString filePath)
{
    QFile localFile(filePath);

    if (!localFile.open(QFile::ReadOnly))
    {
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

