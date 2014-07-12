#ifndef _DEV_DB_H__
#define _DEV_DB_H__
#include"sqlDB.h"

//database key
enum devDBKey {DEV_VER = 1, PKG_VER, APK_VER, CHAN_ID} ;   

class devDB :public sqlDB
{

    public:
        devDB();
        ~devDB();

        bool set(devDBKey key, const string& value);
        bool get(devDBKey key, string& value);

    private:

        //database value
        string      m_devVer;
        string      m_pkgVer;
        string      m_apkVer;
        string      m_chanId;
};


#endif
