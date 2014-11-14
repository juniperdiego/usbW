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
#include "db/reportDB.h"

using namespace std;

#define COMMON_PKG_NAME "COMMON_PACKAGE"

#define ARM

#define SER_LENGTH 15
#define FIFO "/tmp/usb_fifo"
#define MAX_APK_NUM (64/8)
#define DEVCOUNT 12
#define WEB_SITE "www.baidu.com"
#define APP_NAME "Zig"
#define NET_NAME "eth0"
#define ENCYPT_BIT 0x12
#define PROG_NAME "progMonitor.apk"

//download
#if 0
#define URL_DEVVER "http://192.168.1.104:8080/nzyw/api/getDeviceVersion.do"
#define URL_APKLIBVER "http://192.168.1.104:8080/nzyw/api/getApkLibVersion.do"
#define URL_PKGLIBVER "http://192.168.1.104:8080/nzyw/api/getPkgLibVersion.do"
#define URL_UPLOAD "http://192.168.1.104:8080/nzyw/api/processLog.do"
#define URL_UPLOAD_DATA "http://192.168.1.104:8080/nzyw/api/processData.do"
#else
#define URL_DEVVER "http://api.dfstock4g.com/nzyw/api/getDeviceVersion.do"
#define URL_APKLIBVER "http://api.dfstock4g.com/nzyw/api/getApkLibVersion.do"
#define URL_PKGLIBVER "http://api.dfstock4g.com/nzyw/api/getPkgLibVersion.do"
#define URL_UPLOAD "http://api.dfstock4g.com/nzyw/api/processLog.do"
#define URL_UPLOAD_DATA "http://api.dfstock4g.com/nzyw/api/processData.do"
#endif

#define MNT_PATH "/data"
#define EXE_PATH "/usr/local/bin"
#define DB_PATH "/data/kuaijl/"
#define TMP_PATH  "/data/kuaijl/tmp/"
#define APK_PATH  "/data/kuaijl/apks/"
#define UPDATE_FILE_NAME "/data/kuaijl/update.zip"
#define LOG_FILE_NAME "/data/kuaijl/zig.log"
#define LOG_FILE_SIZE 1024*1024*10

//update
#define BLOCKSIZE 100
#define MAXLINELEN 512
#define LOG_PATH "/data/kuaijl/log/"
#define ENCYPT_LOG_PATH "/data/kuaijl/encypt_log/"
#define PERIOD (60*60*2)
#define PERIOD_SET_UNUPLOAD 30*60


typedef struct USB_STATE{
    int num;						 //usb ser
    int install_state;               //0:free  1:installing  2:install_complete  3:break off 4:install uncomplete 5:readying
    char   model[64];                  //device mod
    char   ser[SER_LENGTH];          //device ser
    int apk_num;                  //apk install now
    int apk_total;                //apk total num
    int fail_total;                //apk fail total num
}USB_State;



class Global
{
public:
    static void reboot();
    static void setSysTime(const QString& t);
    static string encyptStr(const string& str);
    static void clearApks();
    static void clearTmp();

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
