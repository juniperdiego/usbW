#ifndef _APK_DB_H__
#define _APK_DB_H__
#include"sqlDB.h"


enum autoRun { RUN= 1, NO_RUN}; 
enum dspIcon { DISPLAY= 7, NO_DSP}; 

class apkInfo {
    public:
        int         apkID;
        string      pkgName;
        int         counter;
        dspIcon     dIcon;
        autoRun     aRun;
        string      md5;

    apkInfo()
            :apkID(INVALID_ID),
            counter(0),
            dIcon(NO_DSP), 
            aRun(NO_RUN) 
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
