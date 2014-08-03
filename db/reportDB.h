#ifndef _MBL_STAT_DB_H__
#define _MBL_STAT_DB_H__
#include"sqlDB.h"


#if 0
       imei：手机imei
       ua：手机ua信息
       渠道id：加工设备传递给手机
       加工设备编码：加工设备传递给手机
       批次号：安装包的批次号，加工设备传递给手机
       手机加工时间：设备加工手机的时间戳
#endif

class reportInfo
{
    public:
        string          imei;  
        string          model;
        string          chanID;
        string          macAdd;
        string          installDate;
        int             portIdx; 
        string          batchCode;
        bool            isUpload;
        unsigned int    id;
        //
        int             count;

   reportInfo()
       :isUpload(2)
   {
   };

};


class reportDB :public sqlDB
{

    public:
        reportDB();
        ~reportDB();

        bool set( const reportInfo& report);
        bool getUnuploadedData(vector<reportInfo>& reportVector);
       bool getModel(const string& date1, const string& date2, vector<reportInfo> & reportVector);
       bool getUsb(const string& date1, const string& date2, vector<reportInfo> & reportVector);
};

#endif
