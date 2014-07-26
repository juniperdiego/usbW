#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <math.h>
#include <stdint.h>
#include "global.h"
#include "mainwindow.h"
#include "usb_enum.h"
#include "tongxin.h"
#include <sstream>
#include <errno.h>

using namespace std;

void add_callback(int num,  const char *serial){
#if 0
    printf("add callback %d %s.\n", num, serial);
#else
    printf("add callback %d %s.\n", num, serial);
    sleep(3);
    Global::usb_state[num].fail_total = 0;
	Global::usb_state[num].num = num;
	char *device_model = adb_getprop_cmd("ro.product.model", serial); //to do ????????????
	sprintf(Global::usb_state[num].model, "%s", device_model);
	sprintf(Global::usb_state[num].ser, "%s", serial);
	
	Global::usb_state[num].install_state=1;
	
	string apk_path;

    string pkg_id;
	string model = Global::usb_state[num].model;

    cout << "model\t" << model << endl;
    // 1 get pkg id from model
    mblDB mblDataBase;
    mblInfo mblIn;
    mblIn.mblID = model; 

    
    if(mblDataBase.get(mblIn))
        pkg_id = mblIn.pkgID;
    else
        pkg_id = COMMON_PKG_NAME;

    cout << "pkg_id\t" << pkg_id<< endl;

    // 2 get apks form pkg id
    pkgDB pkgDataBase;
    pkgInfo pkgIn;
    pkgIn.pkgID = pkg_id;

    pkgDataBase.get(pkgIn);

    // 3 install all apks
    apkDB apkDataBase;
    int pkgNum = pkgIn.apkList.size();
    Global::usb_state[num].apk_total = pkgNum;
    Global::usb_state[num].apk_num = 0;
    tongXin::getTongXin()->updateGui(num);

    for(int i =0; i < pkgNum; i++)
    {
        string apkPath = APK_PATH ;

        apkPath += pkgIn.apkList[i] + ".apk";
        if (!adb_install_cmd(apkPath.c_str(), serial)) 
            Global::usb_state[num].fail_total++;
        Global::usb_state[num].apk_num = i+1;
        //MainWindow::s_devArray[num]->DevWdgPrecess(&(Global::usb_state[num]));;
        tongXin::getTongXin()->updateGui(num);
        cout << "apk\t" << pkgIn.apkList[i]<< endl;

        apkInfo apkIn;
        apkIn.apkID = pkgIn.apkList[i];
        apkDataBase.get(apkIn);
        if(apkIn.aRun)
        {
            // start the app
            cout <<"pkgPath\t"<< apkIn.pkgPath << endl;
            adb_start_app_cmd( (char*) apkIn.pkgPath.c_str(), serial);
        }
    }
	Global::usb_state[num].install_state=2;
    //MainWindow::s_devArray[num]->DevWdgPrecess(&(Global::usb_state[num]));;
    tongXin::getTongXin()->updateGui(num);

    // 4 update statistic database
    mblStatDB mblStatDateBase;
    mblStatDateBase.increase(model);
    usbStatDB usbStatDateBase;
    usbStatDateBase.increase(num);


#if 1

    // 5 write log
    // format: 手机imei|手机ua|渠道id|加工设备编码|批次号|手机加工时间戳
    /*
       imei：手机imei
       ua：手机ua信息
       渠道id：加工设备传递给手机
       加工设备编码：加工设备传递给手机
       批次号：安装包的批次号，加工设备传递给手机
       手机加工时间：设备加工手机的时间戳
     */

     //imei
    char* pImei = adb_get_imei_cmd(serial);
    string ImeiStr;
    if(pImei != NULL)
        ImeiStr = pImei;
    delete(pImei);

    cout << "ImeiStr \t" << ImeiStr << endl;
    
    // 手机ua is model

    // channel id
    devDB devDataBase;
    string chanID;
    devDataBase.get(CHAN_ID, chanID);

    //加工设备编码 is Global::g_DevID

    //批次号 is pkgIn.batchCode;
    
    // 手机加工时间戳
    char time[32];
    getDate(time, 0);
    string timeStr(time);
    

    string msg = ImeiStr + "|"\
                + model + "|"\
                + chanID + "|"\
                + Global::g_DevID + "|"\
                + pkgIn.batchCode + "|"\
                + timeStr 
                + "\n";

    stringstream strStream;
    strStream << num ;
    string numStr = strStream.str();
                
    string fileName = LOG_PATH + timeStr /*+ "_" + numStr */ + ".csv";

    //int fd=open(fileName.c_str(), O_WRONLY|O_NONBLOCK,0);
    int fd=open(fileName.c_str(), O_WRONLY|O_APPEND|O_CREAT,0);
    if(fd == -1)
    {
        printf("errno.%02d is: %s/n", errno, strerror(errno));
        cout << "opening file("<<fileName <<") failed." << endl;
        return;
    }
    else
        cout << "opening file("<<fileName <<") suc." << endl;

    logDB logDB;
    logInfo log;
    log.date = timeStr;
    logDB.set(log);

    if(write(fd, msg.c_str(), msg.size()) == -1)
    {
        cout << "writing file("<<fileName <<") failed." << endl;
        return;
    }

    close(fd);
#endif
#endif
}

void remove_callback( int num){
#if 0
    printf("remove callback %d.\n", num);
#else
    printf("remove callback %d.\n", num);
	if( Global::usb_state[num].install_state == 1)
		Global::usb_state[num].install_state = 3;
	else
		Global::usb_state[num].install_state = 0;
    tongXin::getTongXin()->updateGui(num);
#endif
}

/*
void add_callback(int num, const char *serial)
{
    printf("Add USB num: %d, Serial: %s\n", num, serial);

    // Place Your CODE here. 
}

void remove_callback(int num)
{
    printf("Remove USB num: %d\n", num);
    // Place Your CODE here. 
}
*/

void call()
{
    static bool isInMonitor = false;
    if(isInMonitor == false)
        isInMonitor = true;
    else
        return;
    register_usb_device_callback(add_callback, remove_callback);
    start_usb_device_monitor();
//	char adb_pus_1[] = "/home/xianfeng/usb_enum/net_link.txt";
//	char adb_pus_2[] = "/sd/net_link.txt";
//	char adb_pus_3[] = "0123456789ABCDEF";
   // printf(" adb_push_cmd  = %d\n", adb_push_cmd( adb_pus_1, adb_pus_2, adb_pus_3));
   // printf(" getprop = %s\n", adb_getprop_cmd("ro.build.product","0123456789ABCDEF"));
//	char adb_install_1[] = "com.android.browser/com.android.browser.BrowserActivitya";
//	char adb_install_2[] = "0123456789ABCDEF";
  //  printf("%d\n", adb_install_cmd("/home/xianfeng/Downloads/a.apk","0123456789ABCDEF"));

    //start com.android.browser/com.android.browser.BrowserActivity
//	char activ_1[] = "com.android.browser/com.android.browser.BrowserActivitya";
//	char activ_2[] = "0123456789ABCDEF";
//    qDebug()<<"test for void call!\n";
    //printf("start app %d \n", adb_start_app_cmd( activ_1, activ_2));
    //return 0;
}

