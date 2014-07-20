#ifndef _MBL_DB_H__
#define _MBL_DB_H__
#include"sqlDB.h"

class mblInfo
{
    public:
        string          mblID;  
        string          pkgID;

   mblInfo()
   {
   };

};


class mblDB :public sqlDB
{

    public:
        mblDB();
        ~mblDB();

        bool deleteRecord(const string& pkgID);
        bool set(const mblInfo& pkg);
        bool get(mblInfo & pkg);

};


#endif
