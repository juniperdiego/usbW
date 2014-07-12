#ifndef _LOG_DB_H__
#define _LOG_DB_H__
#include"sqlDB.h"

class logInfo
{
    public:
        string          date;
        bool            isUploaded;

   logInfo()
       :isUploaded(false)
   {
   };

};


class logDB :public sqlDB
{

    public:
        logDB();
        ~logDB();

        bool set(const logInfo& msi);
        bool get(const string& date1, const string& date2, vector<logInfo> & liArray);

};

void print(const logInfo& msi);
#endif
