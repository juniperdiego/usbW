#ifndef _PKG_DB_H__
#define _PKG_DB_H__
#include"sqlDB.h"

#include<vector>

class pkgInfo
{
    public:
        string          pkgID;  
        string          pkgName;
        string          batchCode;
        vector<string>  apkList;
        vector<bool>    autoRunList;
        vector<bool>    iconList;
        int             apkSum;
        string          date;

   pkgInfo()
       :apkSum(0)
   {
   };

};


class pkgDB :public sqlDB
{

    public:
        pkgDB();
        ~pkgDB();

        bool deleteRecord(const string& pkgID);
        bool set(const pkgInfo& pkg);
        bool get(pkgInfo & pkg);
        bool getAll(vector<pkgInfo> & pkgInfoList);


};


#endif
