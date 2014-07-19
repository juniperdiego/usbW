#ifndef _USB_STAT_DB_H__
#define _USB_STAT_DB_H__
#include"sqlDB.h"

class usbStatInfo
{
    public:
        int             usbIdx;  
        string          date;
        int             count;

   usbStatInfo()
       :usbIdx(INVALID_ID),count(0)
   {
   };

};


class usbStatDB :public sqlDB
{

    public:
        usbStatDB();
        ~usbStatDB();

        bool set(const usbStatInfo& usi);
        bool get(const string& date1, const string& date2, vector<usbStatInfo> & usiArray);
        bool increase(int usbIdx);

};

void print(const usbStatInfo& usi);
#endif
