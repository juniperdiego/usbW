#ifndef GLOBAL_H
#define GLOBAL_H

//@lgs
#include <QObject>
#include <QString>
#include <QtNetwork>
#include <QString>
#include <QByteArray>
#include <QCryptographicHash>
#include <QFile>
#include <QtDebug>
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

#define SER_LENGTH 15
#define FIFO "/tmp/usb_fifo"
#define MAX_APK_NUM (64/8)
#define USB_COUNT 12

//download
//#define URL_DEVVER "http://192.168.1.117:8080/nzyw/api/getDeviceVersion.do"
#define URL_DEVVER "http://www.tymng.com:8080/nzyw/api/getDeviceVersion.do"
#define URL_APKLIBVER "http://www.tymng.com:8080/nzyw/api/getApkLibVersion.do"
#define URL_PKGLIBVER "http://www.tymng.com:8080/nzyw/api/getPkgLibVersion.do"
#define  TMP_PATH  "/tmp/tmpapk"
#define  APK_PATH  "/mnt/repos/apk"
#define  SPIRIT_PATH "/tmp/kuaijl/update.zip"

//update
#define URL_UPLOAD "http://192.168.1.103:8080/nzyw/api/processLog.do"
#define BLOCKSIZE 100
#define MAXLINELEN 512
#define LOGPATH "/home/zb/work/log"
#define PERIOD (60*60*2)


typedef struct USB_STATE{
    int8_t num;						 //usb ser
    int8_t install_state;                 //usb state 0?????? 1????װ??2????װ???? 3????װ?ж?4????װ????ȫ
                                     //0:free  1:installing  2:install_complete  3:break off 4:install uncomplete
    char   mod[64];                  //device mod
    char   ser[SER_LENGTH];          //device ser
    int8_t apk_num;                  //apk install now
    int8_t apk_total;                //apk total num
    int8_t apk_install[MAX_APK_NUM];  //apk install state
}USB_State;



class Global
{
public:
    Global();
public:
    static QString g_IP;                     //服务器IP
    static std::string g_DevID;         //Device ID
    static bool g_NetState;             //网络状态
    static int g_UnUpNum;           //未上传文件数量
    static USB_State usb_state[USB_COUNT];
};

#endif // GLOBAL_H
