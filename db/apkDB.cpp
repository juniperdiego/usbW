#include "apkDB.h"

apkDB::apkDB()
{

    // 1. should open the db, but the db is opened
    
    // 2. name the divec talbe 
    setTableName("apkTable");

    // 3. create the table 
    char sql[1024] ="";
    if(!tableExist())
    {
        char* errMsg;

        // creat the table
        sprintf(sql, "CREATE TABLE %s ( key integer PRIMARY KEY, pkgName varchar(128), counter int, dIcon int, aRun int, md5 varchar(32) );", getTableName().c_str());
        int rc =    sqlite3_exec(s_db, sql, NULL, NULL, &errMsg);
        if( rc ){   
            fprintf(stderr, "Can't create table %s: %s\n", getTableName().c_str(), errMsg);   
            sqlite3_close(s_db);   
            exit(1);
        }   
    }
}

apkDB::~apkDB()
{
}

bool apkDB::set( const apkInfo& apk)
{
    char sql[1024] ="";
    char* errMsg;
        sprintf(sql, "CREATE TABLE %s ( key integer PRIMARY KEY, pkgName varchar(128), counter int, dIcon int, aRun int, md5 varchar(32) );", getTableName().c_str());

    sprintf(sql, "insert or replace into %s\
            (key, pkgName, counter, dIcon, aRun, md5)\
       values( %d, \"%s\",   %d,    %d,   %d,  \"%s\");",
       getTableName().c_str(),
       apk.apkID, 
       apk.pkgName.c_str(),
       apk.counter,
       apk.dIcon,
       apk.aRun,
       apk.md5.c_str()
       );

    if(SQLITE_OK == sqlite3_exec(s_db, sql, NULL, NULL, &errMsg))
        return true;
    return false;

}

#if 0
class apkInfo {
    public:
        int         apkid;
        string      pkgname;
        int         counter;
        dspIcon     dIcon;
        autoRun     aRun;
        string      md5;

    apkInfo()
            :int(INVALID_ID),
            counter(0),
            dIcon(noDsp), 
            aRun(noRun) 
    {
    };
};
#endif

bool apkDB::get(apkInfo & apk)
{
    char sql[1024] = {0};
    sqlite3_stmt *stmt;
    int rc;

    sprintf(sql, "select pkgName, counter, dIcon, aRun, md5 from %s where key = '%d';", getTableName().c_str(), apk.apkID);
#if 0
    {
        int nrow = 0, ncolumn = 0;
        char **azResult; 
        char * zErrMsg;

        //sql = "SELECT * FROM SensorData ";
        sqlite3_get_table(s_db , sql , &azResult , &nrow , &ncolumn , &zErrMsg );

        int i = 0 ;
        printf( "row:%d column=%d \n" , nrow , ncolumn );
        printf( "\nThe result of querying is : \n" );

        for( i=0 ; i<( nrow + 1 ) * ncolumn ; i++ )
            printf( "azResult[%d] = %s\n", i , azResult[i] );

    }
#endif

    rc= sqlite3_prepare(s_db,sql, strlen(sql), &stmt,0);     
    if( rc ){   
        fprintf(stderr, "Can't open statement: %s\n", sqlite3_errmsg(s_db));   
        sqlite3_close(s_db);   
        return false;   
    }   

    string str;
    while(sqlite3_step(stmt)==SQLITE_ROW ) {   
        apk.pkgName = string( (const char*)sqlite3_column_text(stmt,0)); 
        apk.counter = sqlite3_column_int(stmt,1);
        apk.dIcon   =(dspIcon) sqlite3_column_int(stmt,2);
        apk.aRun    = (autoRun)sqlite3_column_int(stmt,3);
        apk.md5     = string( (const char*)sqlite3_column_text(stmt,4));   
        //printf("%s\n",  (const char*)sqlite3_column_text(stmt,0));
    }   

    sqlite3_finalize(stmt);
    return true;
}

void print(const apkInfo& apk)
{
    printf("%20s,%20s,%20s,%20s,%20s,%20s\n", 
            "apkId", "pkgName", "counter", "dIcon", "aRun", "md5");
    printf("%20d,%20s,%20d,%20d,%20d,%20s\n", 
            apk.apkID, apk.pkgName.c_str(), apk.counter, apk.dIcon, apk.aRun, apk.md5.c_str()
            );
}


