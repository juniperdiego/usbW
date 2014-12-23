#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

bool adb_uninstall_cmd(const char *pkgName, const char *serial)
{
    bool succ = false;
    FILE *fp;
    char str[1024] = {0};
    char cmd[1024] = {0};
    fflush(stdout);

    snprintf(cmd, sizeof(cmd), "adb -s %s uninstall  %s", serial, pkgName);

    if ((fp = popen(cmd, "r")) == NULL) {
        printf("execCmd popen failed, errno: %i", errno);
        exit(100);
    }

    // Obtain and display each line of output from the executed command
    while (fgets(str, sizeof(str), fp) != NULL) {
        printf("------%s\n",str );
        if ((strlen(str) > 1) && (str[strlen(str) - 1] == '\n')) {
            str[strlen(str) - 1] = '\0';
        }

        if (! strncmp(str, "Failure", 7)) {
            printf("uninstall app error\n");
            succ = false;
        }else if (!strncmp(str, "Success", 7)){
            printf("uninstall app success\n");
            succ = true;
        }
    }

    pclose(fp);

    return succ;
}

bool adb_install_cmd(const char *apk_name, const char *serial)
{
    bool succ = false;
    FILE *fp;
    char str[1024] = {0};
    char cmd[1024] ={0};
    fflush(stdout);

    snprintf(cmd, sizeof(cmd), "adb -s %s install -r %s", serial, apk_name);

    printf("aaaaa\n" );
    fflush(stdout);
    if ((fp = popen(cmd, "r")) == NULL) {
        printf("execCmd popen failed, errno: %i", errno);
        exit(100);
    }
    printf("bbbbb\n" );
    fflush(stdout);

    // Obtain and display each line of output from the executed command
    while (fgets(str, sizeof(str), fp) != NULL) {
        printf("------%s",str );
        if ((strlen(str) > 1) && (str[strlen(str) - 1] == '\n')) {
            str[strlen(str) - 1] = '\0';
        }

        if (! strncmp(str, "Failure", 7)) {
            printf("install app error\n");
            succ = false;
        }else if (!strncmp(str, "Success", 7)){
            printf("install app success\n");
            succ = true;
        }
    }
    printf("cccccc\n" );
    fflush(stdout);

    pclose(fp);
    printf("dddddd\n" );
    fflush(stdout);

    // always return true, sicnc when the app is a system-level,
    // we may can't install it sucessfully, which will lead to stop installing other apps.
    succ = true;
    return succ;
}
/*
**printf(" getprop = %s\n", adb_getprop_cmd("ro.build.product","0123456789ABCDEF"));


* get  model
**printf(" getprop = %s\n", adb_getprop_cmd("ro.product.model","0123456789ABCDEF"));
*/

char * adb_getprop_cmd(const char *prop, const char *serial) {
    FILE *fp;
    char *result = malloc(sizeof(char) * 1024);
    memset(result, 0,1024 );
    char str[1024] = {0};
    char cmd[1024] = {0};
    snprintf(cmd, sizeof(cmd), "adb -s %s shell getprop %s", serial, prop);
    printf("getprop cmd = %s\n", cmd);
    fflush(stdout);
    if ((fp = popen(cmd, "r")) == NULL) {
        printf("execCmd popen failed, errno: %i", errno);
        exit(100);
    }

    while (fgets(str, /*sizeof(str)*/1024, fp) != NULL) {
        if ((strlen(str) > 1) && 
                (str[strlen(str) - 1] == '\n') ) 
        {
            if(strlen(str) > 2 && str[strlen(str) - 2] == 13)
                str[strlen(str) - 2] = '\0';
            else
                str[strlen(str) - 1] = '\0';
        }
    }

    pclose(fp);
    strcpy(result, str);
    return (char *)result;
}


char * adb_get_imei_cmd( const char *serial) {
    FILE *fp;
    char *result = malloc(sizeof(char) * 1024);
    memset(result, 0 ,1024);
    char str[1024];
    char cmd[1024];
    bool findImei = false;

    memset(cmd, 0, 1024);
    snprintf(cmd, sizeof(cmd), "adb -s %s shell dumpsys iphonesubinfo", serial);
    printf("getprop cmd = %s\n", cmd);
    fflush(stdout);
    if ((fp = popen(cmd, "r")) == NULL) {
        printf("execCmd popen failed, errno: %i", errno);
        exit(100);
    }

    printf("aaaaaa\n");
    fflush(stdout);

    while (fgets(str, sizeof(str), fp) != NULL) {
        if ((strlen(str) > 1) && (str[strlen(str) - 1] == '\n')) 
        {
            if(strlen(str) > 2 && str[strlen(str) - 2] == 13)
                str[strlen(str) - 2] = '\0';
            else
                str[strlen(str) - 1] = '\0';

            // check if this string begin with "Device ID"
            char * devPos = strstr(str, "Device ID");
            if(devPos != NULL) // found
            {
                findImei = true;
                break;
            }
        }
    }
    pclose(fp);

    printf("bbbbbb %d\n", findImei);
    fflush(stdout);

    if(findImei == false) // not found
    {
        result[0] = '\0';
        return (char *)result;
    }

    // handle this kind of string
    //"Device ID = 352956061737216"
    char* p = str;
    char* start = NULL;

    printf("ccccccc %s\n", str);
    fflush(stdout);

    while(p != '\0')
    {
        if(*p == '=' && *(p+1) != '\0' && *(p+2) != '\0')
        {
            start = p+2;
            break;
        }
        p++;
    }

    printf("ddddddd %s\n", start);
    fflush(stdout);

    strcpy(result, start);

    printf("eeeeee %s\n", result);
    fflush(stdout);

    return (char *)result;
}

bool adb_push_cmd(char *src, const char *dest, const char *serial)
{
    char cmd[1024];
    memset(cmd, 0, 1024);
    snprintf(cmd, sizeof(cmd), "adb -s %s push %s %s", serial, src, dest);
    return system(cmd) == 0;
}

/*
* adb -s 0123456789ABCDEF shell am start -n com.android.browser/com.android.browser.BrowserActivity
*/
bool adb_start_app_cmd(char *pkgPath, const char *serial)
{
    char cmd[1024];
    memset(cmd, 0, 1024);
    snprintf(cmd, sizeof(cmd), "adb -s %s shell am start -n %s", serial, pkgPath);
    return system(cmd) == 0;
}

bool adb_send_msg_app_cmd(const char *serial, int count, int total, int portNum)
{

    char cmd[1024];
    memset(cmd, 0, 1024);
    snprintf(cmd, sizeof(cmd), "adb -s %s shell am broadcast -a com.chris.progressmonitor.PERCENT_MONITOR --ei count %d --ei total %d --ei portNum %d", serial, count, total, portNum);
    return system(cmd) == 0;
}

bool adb_send_msg_shortcut_app_cmd(const char *serial, const char* str)
{

    char cmd[1024];
    memset(cmd, 0, 1024);
    snprintf(cmd, sizeof(cmd), "adb -s %s shell am broadcast -a com.chris.progressmonitor.SHORT_CUT --es pkgList \"%s\"", serial, str);
    return system(cmd) == 0;
}

