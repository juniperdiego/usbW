#ifndef GLOBAL_H
#define GLOBAL_H

#include <QtGui>
#include <QtNetwork>
#include <string>
#include <stdint.h>

//db
#include "db/devDB.h"
#include "db/pkgDB.h"
#include "db/apkDB.h"
#include "db/mblDB.h"
#include "db/usbStatDB.h"
#include "db/mblStatDB.h"
#include "db/logDB.h"

using namespace std;

#define COMMON_PKG_NAME "COMMON_PACKAGE"

#define ARM

#define MNT_PATH "/mnt/repos"
#define SER_LENGTH 15
#define FIFO "/tmp/usb_fifo"
#define MAX_APK_NUM (64/8)
#define DEVCOUNT 12
#define WEB_SITE "www.baidu.com"
#define APP_NAME "Zig"

//download
#ifdef ARM
#define URL_DEVVER "http://192.168.1.108:8080/nzyw/api/getDeviceVersion.do"
#define URL_APKLIBVER "http://192.168.1.108:8080/nzyw/api/getApkLibVersion.do"
#define URL_PKGLIBVER "http://192.168.1.108:8080/nzyw/api/getPkgLibVersion.do"
#else
#define URL_DEVVER "http://www.tymng.com:8080/nzyw/api/getDeviceVersion.do"
#define URL_APKLIBVER "http://www.tymng.com:8080/nzyw/api/getApkLibVersion.do"
#define URL_PKGLIBVER "http://www.tymng.com:8080/nzyw/api/getPkgLibVersion.do"
#endif
#define TMP_PATH  "/mnt/repos/.kuaijl/tmp"
#define APK_PATH  "/mnt/repos/.kuaijl/apks/"
#define UPDATE_FILE_NAME "/mnt/repos/.kuaijl/update.zip"
#define DB_PATH "/mnt/repos/.kuaijl/"

//update
#define URL_UPLOAD "http://192.168.1.105:8080/nzyw/api/processLog.do"
#define BLOCKSIZE 100
#define MAXLINELEN 512
#define LOG_PATH "/mnt/repos/.kuaijl/log/"
#define PERIOD (60*60*2)
#define PERIOD_SET_UNUPLOAD 30*60


typedef struct USB_STATE{
    int num;						 //usb ser
    int install_state;                 //usb state 0?????? 1????װ??2????װ???? 3????װ?ж?4????װ????ȫ
                                     //0:free  1:installing  2:install_complete  3:break off 4:install uncomplete
    char   model[64];                  //device mod
    char   ser[SER_LENGTH];          //device ser
    int apk_num;                  //apk install now
    int apk_total;                //apk total num
    int fail_total;                //apk fail total num
    int apk_install[MAX_APK_NUM];  //apk install state
}USB_State;



class Global
{
public:
    static void reboot();
    static void setSysTime(const QString& t);

public:
    static QString g_IP;                     //服务器IP
    static std::string g_DevID;         //Device ID
    static bool s_netState;             //网络状态
    static int g_UnUpNum;           //未上传文件数量
    static USB_State usb_state[DEVCOUNT];
    static bool s_needRestart;
    static QString s_updateTime;
};

#endif // GLOBAL_H
