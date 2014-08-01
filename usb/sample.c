#include "usb_enum.h"

pthread_t ptid[3];

static void *install_apk(void * args)
{
    int num =(int) args;
    if(num == 0)
    {
        adb_install_cmd("1.apk", "f80113f02db7");
        printf("install\t1.apk @ f80113f02db7"); 


    }
    else if(num == 1)
    {
        adb_install_cmd("2.apk", "f80113f02db7");
        printf("install\t2.apk @ f80113f02db7"); 
    }
    else if(num == 2)
    {
        adb_install_cmd("3.apk", "f80113f02db7");
        printf("install\t3.apk @ f80113f02db7"); 
    }
    return NULL;

}

int main(int argc, char *argv[])
{
    int i, ret;
    
#if 0
     for (i = 0; i < 3; i ++) {
             ret = pthread_create(&ptid[i], NULL, install_apk, (void *)i);
             if (ret != 0) {
              printf("thread id: %d create failed.\n", i);
          } else {
                  printf("thread id: %d create success.\n", i);
              }
         }
    
     for (i = 0; i < 3; i ++) {
             pthread_join(ptid[i], NULL);
         }
#endif

#if 0
    register_usb_device_callback(add_callback, remove_callback);
    start_usb_device_monitor();
    //printf(" adb_push_cmd  = %d\n", adb_push_cmd("/home/xianfeng/usb_enum/net_link.txt", "/sd/net_link.txt","0123456789ABCDEF"));
    printf(" getprop(ro.build.product) = %s888\n", adb_getprop_cmd("ro.build.product","b2269745"));
    printf(" getmodel = %s888\n", adb_getprop_cmd("ro.product.model","b2269745"));
    printf(" getimei = %s888\n", adb_get_imei_cmd("b2269745"));

    printf(" getprop(ro.build.product) = [%s]&&&\n", adb_getprop_cmd("ro.build.product","040ABFQ6F36Z"));
    printf(" getmodel = [%s]&&&\n", adb_getprop_cmd("ro.product.model","040ABFQ6F36Z"));
    printf(" getimei = [%s]&&&\n", adb_get_imei_cmd("040ABFQ6F36Z"));

    //start com.android.browser/com.android.browser.BrowserActivity
    //printf("start app %d \n", adb_start_app_cmd("com.android.browser/com.android.browser.BrowserActivitya", "0123456789ABCDEF"));
    
#endif
    int j;
    for(j = 1; j < 2; j++)
    {
        //if(serialNumExistInPort(int idx, const char * serial))

        char cmd[1024];
        snprintf(cmd, sizeof(cmd), "%d.apk ",j);
        //if(serialNumExistInPort(5, "b2269745"))
        if(1)
        {
            printf("exist\n");
            adb_install_cmd(cmd, "b2269745");
        }
        else
            printf("not exist\n");
    }

    printf("xxxxxxxxa\nx");
    fflush(stdout);
    //printf(" getprop(ro.build.product) = [%s]\n", adb_getprop_cmd("ro.build.product","9a1fd61b"));
    //printf(" getmodel = [%s]n", adb_getprop_cmd("ro.product.model","9a1fd61b"));
    //printf(" getimei = [%s]n", adb_get_imei_cmd("9a1fd61b"));
    //adb_install_cmd("1.apk", "9a1fd61b");

    return 0;
}

