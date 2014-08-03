#ifndef _REPORT_DB_H__
#define _REPORT_DB_H__
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
       :
       portIdx(0),
       isUpload(false),
       id(0),
       count(0)
   {
   };

   reportInfo(const string& imeiIn, const string& modelIn,
           const string& chanIDIn, const string& macAddIn,
           const string& installDateIn, int portIdxIn,
           const string& batchCodeIn, bool isUploadIn = false)
   {
       imei = imeiIn;
       model = modelIn;
       chanID = chanIDIn;
       macAdd = macAddIn;
       installDate = installDateIn;
       portIdx = portIdxIn;
       batchCode = batchCodeIn;
       isUpload = isUploadIn;
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
       bool getID( reportInfo& report);
       bool setUpload(int id);

};

#endif
