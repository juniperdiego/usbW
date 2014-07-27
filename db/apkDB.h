#ifndef _APK_DB_H__
#define _APK_DB_H__
#include"sqlDB.h"


class apkInfo {
    public:
        string      apkID;
        string      pkgPath;
        string      md5;

    apkInfo()
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
        bool getRecordCount(int & count);

};


#endif
