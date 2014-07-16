#ifndef _APK_DB_H__
#define _APK_DB_H__
#include"sqlDB.h"


class apkInfo {
    public:
        string      apkID;
        string      pkgPath;
        int         counter;
        bool        dIcon;
        bool        aRun;
        string      md5;

    apkInfo()
            :
            counter(0),
            dIcon(false), 
            aRun(false) 
    {
    };
};

void print(const apkInfo& apk);




class apkDB :public sqlDB
{

    public:
        apkDB();
        ~apkDB();

        bool set(const apkInfo& apk);
        bool get(apkInfo & apk);

};


#endif
