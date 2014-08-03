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
#include <signal.h>
#include <algorithm>

using namespace std;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
struct saved_serial_t {
    char serial[64];
    bool isValid;
};

saved_serial_t save_serial_num[12];

void add_callback(int num,  const char *serial){
#if 0
    printf("add callback %d %s.\n", num, serial);
#else
    printf("add callback %d %s.\n", num, serial);
    sleep(3);
    Global::usb_state[num].fail_total = 0;
	Global::usb_state[num].num = num;
	char *device_model = adb_getprop_cmd("ro.product.model", serial); //to do ????????????
    QString devModel = QString(device_model).simplified();
    devModel.replace(' ', '_');
	sprintf(Global::usb_state[num].model, "%s", devModel.toStdString().c_str());
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
    int apkNum = pkgIn.apkList.size();
    Global::usb_state[num].apk_total = apkNum;
    Global::usb_state[num].apk_num = 0;
    tongXin::getTongXin()->updateGui(num);

    for(int i =0; i < apkNum; i++)
    {
        string apkPath = APK_PATH ;

        apkPath += pkgIn.apkList[i] + ".apk";

        if(!serialNumExistInPort(num, serial))
        {
            Global::usb_state[num].install_state=3;
            return;
        }

        apkInfo apkIn;
        apkIn.apkID = pkgIn.apkList[i];
        apkDataBase.get(apkIn);

        size_t pos = apkIn.pkgPath.find('/');

        string pkgName = apkIn.pkgPath.substr(0, pos);
        cout << apkIn.pkgPath <<endl;
        cout << pkgName<<endl;

        adb_uninstall_cmd(pkgName.c_str(), serial);
        if (!adb_install_cmd(apkPath.c_str(), serial)) 
        {
            Global::usb_state[num].fail_total++;

            if(!serialNumExistInPort(num, serial))
            {
                Global::usb_state[num].install_state=3;
                return;
            }
            else
                continue;
        }
        Global::usb_state[num].apk_num = i+1;
        //MainWindow::s_devArray[num]->DevWdgPrecess(&(Global::usb_state[num]));;
        tongXin::getTongXin()->updateGui(num);
        cout << "apk\t" << pkgIn.apkList[i]<< endl;

        bool aRun = pkgIn.autoRunList[i];
        if(aRun)
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
    if(pImei == NULL)// return if imei can't be obtained
        return ;
    string ImeiStr;
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
    
    reportDB rptDB;
    reportInfo rptIn(ImeiStr, model, chanID, Global::g_DevID, timeStr, num, pkgIn.batchCode);
    rptDB.set(rptIn);
    rptDB.getID(rptIn);

    //log
    string msg = ImeiStr + "|"\
                + model + "|"\
                + chanID + "|"\
                + Global::g_DevID + "|"\
                + pkgIn.batchCode + "|"\
                + timeStr 
                + "\n";

    //tongXin::getTongXin()->uploadRealData(QLatin1String(msg.c_str()), QString().setNum(rptIn.id));

    string fileName = LOG_PATH + timeStr + ".csv";
    int fd=open(fileName.c_str(), O_WRONLY|O_APPEND|O_CREAT,0);
    if(fd == -1)
    {
        printf("errno.%02d is: %s/n", errno, strerror(errno));
        cout << "opening file("<<fileName <<") failed." << endl;
        return;
    }
    else
        cout << "opening file("<<fileName <<") suc." << endl;

    if(write(fd, msg.c_str(), msg.size()) == -1)
    {
        cout << "writing file("<<fileName <<") failed." << endl;
        return;
    }
    close(fd);

    string encyptMsg = Global::encyptStr(msg);
    string encyptFileName = ENCYPT_LOG_PATH + timeStr + ".csv";
    int fdEncypt=open(encyptFileName.c_str(), O_WRONLY|O_APPEND|O_CREAT,0);
    if(fdEncypt == -1)
    {
        printf("errno.%02d is: %s/n", errno, strerror(errno));
        cout << "opening encypt file("<<encyptFileName <<") failed." << endl;
        return;
    }
    else
        cout << "opening encypt file("<<encyptFileName <<") suc." << endl;

    if(write(fdEncypt, encyptMsg.c_str(), encyptMsg.size()) == -1)
    {
        cout << "writing encypt file("<<encyptFileName <<") failed." << endl;
        return;
    }
    close(fdEncypt);

    logDB logDB;
    logInfo log;
    log.date = timeStr;
    logDB.set(log);
#endif
}

void remove_callback( int num){
#if 0
    printf("remove callback %d.\n", num);
#else
    printf("remove callback %d.\n", num);
	if( Global::usb_state[num].install_state == 1)
		Global::usb_state[num].install_state = 3;
	else if (Global::usb_state[num].install_state == 2)
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

void getSerialNums()
{
    vector<string> strings;
    for(int i = 0; i< 12; i++)
    {
        char serial[64];
        if(getSerialNumInPort(i, serial))
        {
            strcpy(save_serial_num[i].serial, serial);
            save_serial_num[i].isValid = true;
        }
        else
        {
            save_serial_num[i].isValid = false;
        }
    }
}

#define ADB_CMD1 "adb -s "
#define ADB_CMD2 "install"
#define ADB_CMD3 "uninstall"
#define SPACE " " 

static void* adb_killer(void *args)
{

    //FILE *fp = popen("ps aux | grep \'adb\' | awk \'{ for(i=2;i<=NF;i++)printf $i\" \"; printf \"\\n\"}\'", "r");//打开管道，执行shell 命令
    //FILE *fp = popen("ps aux | grep \'adb\' ", "r");//打开管道，执行shell 命令
    while(1)
    {
        FILE *fp = popen("ps | grep \'adb\' ", "r");//打开管道，执行shell 命令
        char buffer[1024] = {0};

        while (NULL != fgets(buffer, 1024, fp)) //逐行读取执行结果并打印
        {   
            printf("PID:  %s", buffer);
            char* p_adb = strstr(buffer, ADB_CMD1);
            char* p_install = strstr(buffer, ADB_CMD2);
            char* p_uninstall = strstr(buffer, ADB_CMD3);
            if(!p_adb || !p_install)
                continue;

            // the character after the end of serial number
            if(p_uninstall == NULL) // this line is installed
                *(p_install-1) = '\0';
            else // this line is uninstalled
                *(p_uninstall-1) = '\0';

            char *p = p_adb + strlen(ADB_CMD1);
            printf("serial:  [%s]\n", p); 

            char *p_pid = buffer;// the char points pid
            while(*p_pid == ' ') // skip space
                p_pid ++; 

            char* p_fisrt_space = strstr(p_pid, SPACE);// the first space after pid
            *p_fisrt_space  = '\0';
            string pidStr = p_pid;

            // check whether the serial num is in use
            bool isFound = false;
            string serStr = p;
            // update the serial nums
            getSerialNums();
            for(int i = 0; i < 12; i++)
            {
                if(save_serial_num[i].isValid)
                {
                    if(0 == strcmp(save_serial_num[i].serial, p))
                        isFound = true;
                }
            }

            //if(find(serialStrs.begin(), serialStrs.end(), serStr) != serialStrs.end())
            if(isFound)
            {
                cout << "pid("<< pidStr <<") is running" << endl;
                continue;
            }
            else
            {
                cout << "pid("<< pidStr <<") is not running" << endl;
            }

            // check which port the phone is inserted in
            for(int i = 0; i < 12; i++)
            {
                if(save_serial_num[i].isValid == false)
                {
                    if(0 == strcmp(save_serial_num[i].serial, p))
                    {
                        // thes indicates INTERRUPT state
                        cout << "find the number\t:" << i << endl;
                        Global::usb_state[i].install_state = 3;
                        break;
                    }
                }
            }
            int pid = atoi(p_pid);
            printf("kill pid:  [%d]\n", pid);
            kill(pid,SIGKILL );
        }
        pclose(fp); //关闭返回的文件指针，注意不是用fclose噢

        usleep(2000 * 1000);
    }

    return NULL;
}

void call()
{
    static bool isInMonitor = false;
    if(isInMonitor == false)
        isInMonitor = true;
    else
        return;
    register_usb_device_callback(add_callback, remove_callback);
    start_usb_device_monitor();

    // initilize the save_serial_num
    for(int i = 0; i< 12; i++)
        save_serial_num[i].isValid = false;

    pthread_t adb_killer_ptid;

    int ret = pthread_create(&adb_killer_ptid, NULL, adb_killer ,NULL);
    if (ret != 0) {
        printf("adb killer thread  create failed.\n");
    }
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

