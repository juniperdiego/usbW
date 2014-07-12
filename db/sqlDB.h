#ifndef _SQL_DB_H__
#define _SQL_DB_H__

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include<sqlite3.h>
#include<string>
#include<string.h>
#include <time.h>
#include <vector>

using namespace std;
const int INVALID_ID = -1;

class sqlDB
{
    public:
        int sqlInit();
        sqlite3 * get_db() {return s_db;};
        sqlDB();
        ~sqlDB();

        string getTableName();
        void   setTableName(const string& tabName);

        bool clearTableItems();
        bool deleteTable();// delete the table, cautious to use
        bool tableExist();
        bool insertToTable(int key, string val);
        bool exist_in_db(sqlite3 *db, const string table, const string id );

    private:

#if 0
        void get_unix_time(char time_str[]);
        void get_date( char date[], int date_length, long int diff);
        string db_get( sqlite3 *db,string table, const string id);
        int db_update( sqlite3 *db, string table, const string id, int opt, const string value);

        string dev_get( const string device_id);
        int dev_update( const string device_id,  const string value);
        bool dev_exist( const string id);
        string dev_get_storeid();
        string dev_get_dev();
        string dev_get_apk();
        string dev_get_pkg();
        string dev_get_cid();

        string mob_get( const string mob_id);
        int mob_update( const string mob_id, const string value);
        bool mob_exist( const string id);
        string mob_get_pkgid(const string mob_id );

        string pkg_get( const string pkg_id);
        string pkg_get_apk_list( const string pkg_id);
        string pkg_get_batchCode( const string pkg_id);
        int pkg_update( const string pkg, const string pkg_name, const string value);
        int pkg_update( const string pkg_id, const string pkg_name, const string apk_list, const int apk_sum, const string date);
        int pkg_update( const string pkg_id, const string pkg_name, const string apk_list, const string batchCode, const int apk_sum, const string date);


        string apk_get( const string apk_id);
        int apk_get_all( const string apk_id, ApkData *res);
        int apk_update(const string apkid, const string pkgname, const int counter, const int icon, const int run ,const string md5);
        int apk_update( const string apk_id, const string pkgname, const int counter, const int icon, const int run);
        int apk_update(const string apk_id, const string md5);
        int apk_update_packagePath(const string apk_id, const string packagePath);
        string apk_get_path( const string apk_id, int *conuter , int *icon);
        string apk_get_packagePath(const string apk_id);

        bool exist_in_db(sqlite3 *db, const string table, const string id );
        void sqlclose();
#endif
    protected:
        static sqlite3     *s_db;
        static unsigned int s_refCnt;
        

    private:
        string      m_tabName;
#if 0
        sqlite3 *dev_db;
        sqlite3 *mob_db;
        sqlite3 *pkg_db;
        sqlite3 *apk_db;
        string  dev_table;
        string  mob_table;
        string  pkg_table;
        string  apk_table;
        char  *err_msg;
#endif
};

//int print_record(void *params, int n_column, char **column_value, char **column_name);
#endif
