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

//#define ARM

#define MNT_PATH "/mnt/repos"
#define SER_LENGTH 15
#define FIFO "/tmp/usb_fifo"
#define MAX_APK_NUM (64/8)
#define USB_COUNT 12

//download
#ifdef ARM
#define URL_DEVVER "http://192.168.1.105:8080/nzyw/api/getDeviceVersion.do"
#define URL_APKLIBVER "http://192.168.1.105:8080/nzyw/api/getApkLibVersion.do"
#define URL_PKGLIBVER "http://192.168.1.105:8080/nzyw/api/getPkgLibVersion.do"
#else
#define URL_DEVVER "http://www.tymng.com:8080/nzyw/api/getDeviceVersion.do"
#define URL_APKLIBVER "http://www.tymng.com:8080/nzyw/api/getApkLibVersion.do"
#define URL_PKGLIBVER "http://www.tymng.com:8080/nzyw/api/getPkgLibVersion.do"
#endif
#define TMP_PATH  "/mnt/repos/.kuaijl/tmp"
#define APK_PATH  "/mnt/repos/.kuaijl/apks/"
#define UPDATE_FILE_NAME "/mnt/repos/.kuaijl/update.zip"

//update
#define URL_UPLOAD "http://192.168.1.105:8080/nzyw/api/processLog.do"
#define BLOCKSIZE 100
#define MAXLINELEN 512
#define LOG_PATH "/mnt/repos/.kuaijl/log/"
#define PERIOD (60*60*2)
#define PERIOD_SET_UNUPLOAD 30*60


typedef struct USB_STATE{
    int8_t num;						 //usb ser
    int8_t install_state;                 //usb state 0?????? 1????װ??2????װ???? 3????װ?ж?4????װ????ȫ
                                     //0:free  1:installing  2:install_complete  3:break off 4:install uncomplete
    char   model[64];                  //device mod
    char   ser[SER_LENGTH];          //device ser
    int8_t apk_num;                  //apk install now
    int8_t apk_total;                //apk total num
    int8_t apk_install[MAX_APK_NUM];  //apk install state
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
    static USB_State usb_state[USB_COUNT];
    static bool s_needRestart;
};

#endif // GLOBAL_H
