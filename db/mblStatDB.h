#ifndef _MBL_STAT_DB_H__
#define _MBL_STAT_DB_H__
#include"sqlDB.h"

class mblStatInfo
{
    public:
        string          mblPattern;  
        string          date;
        int             count;

   mblStatInfo()
       :count(0)
   {
   };

};


class mblStatDB :public sqlDB
{

    public:
        mblStatDB();
        ~mblStatDB();

        bool set(const mblStatInfo& msi);
        bool get(const string& date1, const string& date2, vector<mblStatInfo> & msiArray);

};

void print(const mblStatInfo& msi);
#endif
