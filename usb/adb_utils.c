#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

bool adb_install_cmd(const char *apk_name, const char *serial)
{
    bool succ = false;
    FILE *fp;
    char str[1024];
    char cmd[1024];
    fflush(stdout);

    snprintf(cmd, sizeof(cmd), "adb -s %s install -r %s", serial, apk_name);

    if ((fp = popen(cmd, "r")) == NULL) {
        printf("execCmd popen failed, errno: %i", errno);
        exit(100);
    }

    // Obtain and display each line of output from the executed command
    while (fgets(str, sizeof(str), fp) != NULL) {
//        printf("%s",str );
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

    pclose(fp);

    return succ;
}
/*
**printf(" getprop = %s\n", adb_getprop_cmd("ro.build.product","0123456789ABCDEF"));


* get  model
**printf(" getprop = %s\n", adb_getprop_cmd("ro.product.model","0123456789ABCDEF"));
*/

char * adb_getprop_cmd(const char *prop, const char *serial) {
    FILE *fp;
    char *str = malloc(sizeof(char) * 1024);
    //char str[1024];
    char cmd[1024];
    snprintf(cmd, sizeof(cmd), "adb -s %s shell getprop %s", serial, prop);
    printf("getprop cmd = %s\n", cmd);
    fflush(stdout);
    if ((fp = popen(cmd, "r")) == NULL) {
        printf("execCmd popen failed, errno: %i", errno);
        exit(100);
    }

    while (fgets(str, /*sizeof(str)*/1024, fp) != NULL) {
        if ((strlen(str) > 1) && (str[strlen(str) - 1] == '\n')) {
            str[strlen(str) - 1] = '\0';
        }
    }
    pclose(fp);
    return (char *)str;
}


char * adb_get_imei_cmd( const char *serial) {
    FILE *fp;
    char *result = malloc(sizeof(char) * 1024);
    char str[1024];
    char cmd[1024];
    snprintf(cmd, sizeof(cmd), "adb -s %s shell dumpsys iphonesubinfo", serial);
    printf("getprop cmd = %s\n", cmd);
    fflush(stdout);
    if ((fp = popen(cmd, "r")) == NULL) {
        printf("execCmd popen failed, errno: %i", errno);
        exit(100);
    }

    while (fgets(str, sizeof(str), fp) != NULL) {
        if ((strlen(str) > 1) && (str[strlen(str) - 1] == '\n')) {
            str[strlen(str) - 1] = '\0';
        }
    }
    pclose(fp);

    // handle this kind of string
    //"Device ID = 352956061737216"
    char* p = str;
    char* start = NULL;
    while(p != '\0')
    {
        if(*p == '=' && *(p+1) != '\0' && *(p+2) != '\0')
        {
            start = p+2;
            break;
        }
        p++;
    }

    strcpy(result, start);

    return (char *)result;
}

bool adb_push_cmd(char *src, const char *dest, const char *serial)
{
    char cmd[1024];
    snprintf(cmd, sizeof(cmd), "adb -s %s push %s %s", serial, src, dest);
    return system(cmd) == 0;
}

/*
* adb -s 0123456789ABCDEF shell am start -n com.android.browser/com.android.browser.BrowserActivity
*/
bool adb_start_app_cmd(char *packge_name, const char *serial)
{
    char cmd[1024];
    snprintf(cmd, sizeof(cmd), "adb -s %s shell am start -n %s", serial, packge_name);
    return system(cmd) == 0;
}
