#include <stdio.h>
2 #include <stdlib.h>
3 #include <iostream>
4 #include <time.h>
5 #include "sql_db.h"

int isExisted( void * para, int n_column, char ** column_value, char ** column_name ) 
{ 
        bool *isExisted_=(bool*)para; 
            *isExisted_= (**column_value) != '0'; 
                return 0; 
}

int SqlDB::tableExist(string tableName)
{
    bool bExist;
    char *zErrMsg = 0;
    int rc;

    char str[1024];
    sprintf(str, "SELECT count(*) FROM sqlite_master WHERE type='table' AND name='%s';", tableName.c_str());
    sqlite3_exec( db , str , isExisted , & bExist, &zErrMsg );
    return bExist;
}

bool SqlDB::insertToTable(string tableName, string key, int val)
{
    char* errMsg;
    sprintf(sql, "insert into %s (key, val)  values( \"%s\", %d );", tableName.c_str();, key.c_str, val);
    if(SQLITE_OK == sqlite3_exec(m_db, sql, NULL, NULL, &err_msg))
        return true;
    return false;
}

int SqlDB::sqlInit()
{
    const dbName = "zig.db";

    int rc;
    // 1. open the database
    rc = sqlite3_open(dbName, &m_db);
    if( rc )
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }
    
    // 2. create the devInfo obj
    m_devInfo.m_tabName = "devInfoTable";

    m_devInfo.m_devVerStr = "deviceVersion";
    m_devInfo.m_pkgVerStr = "packageVersion";
    m_devInfo.m_apkVerStr = "apkVersion";
    m_devInfo.m_chanIDStr = "channelID";


    //3 

    unsigned int    m_devVer;
    unsigned int    m_pkgVer;
    unsigned int    m_apkVer;
    unsigned int    m_chanId;

    char sql[1024];
    if(!tableExist(m_devInfo.m_tabName))
    {
        // creat the table
        sprintf(sql, "CREATE TABLE %s ( key varchar(128) PRIMARY KEY, val integer );", m_devInfo.m_tabName.c_str());
        sqlite3_exec(m_db, sql, NULL, NULL, &err_msg);

        m_devInfo.m_devVer = 0; 
        m_devInfo.m_pkgVer = 0;
        m_devInfo.m_apkVer = 0;
        m_devInfo.m_chanId = 0;

        insertToTable(m_devInfo.m_tabName, m_devInfo.m_devVerStr, m_devInfo.m_devVer);
        insertToTable(m_devInfo.m_tabName, m_devInfo.m_pkgVerStr, m_devInfo.m_pkgVer);
        insertToTable(m_devInfo.m_tabName, m_devInfo.m_apkVerStr, m_devInfo.m_apkVer);
        insertToTable(m_devInfo.m_tabName, m_devInfo.m_chanIDStr, m_devInfo.m_chanId);
    }
    else
    {
    }

    char sql[1024]="";
    sprintf(sql, "CREATE TABLE %s ( key varchar(128) PRIMARY KEY, value varchar(128));", mob_table.c_str());
    if(sqlite3_exec(mob_db, sql, NULL, NULL, &err_msg)!= SQLITE_OK){
    }else{
        sqlite3_exec(mob_db, sql, NULL, NULL, &err_msg);
    }

}


bool SqlDB::exist_in_db(sqlite3 *db, const string table, const string id ){
    char sql_query[128]={0};
    sprintf(sql_query,"select count(*) from %s where id='%s'", table.c_str(), id.c_str());

    sqlite3_stmt *pstmt;
    sqlite3_prepare(db, sql_query, strlen(sql_query), &pstmt, NULL);
    sqlite3_step(pstmt);

    int count=sqlite3_column_int(pstmt,0);
    sqlite3_finalize(pstmt);
    if(count > 0)
        return true;
    else
        return false;
}
