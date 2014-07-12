#ifndef _MBL_DB_H__
#define _MBL_DB_H__
#include"sqlDB.h"

class mblInfo
{
    public:
        int             mblID;  
        int             pkgID;

   mblInfo()
       :mblID(INVALID_ID),pkgID(INVALID_ID)
   {
   };

};


class mblDB :public sqlDB
{

    public:
        mblDB();
        ~mblDB();

        bool set(const mblInfo& pkg);
        bool get(mblInfo & pkg);

};


#endif
