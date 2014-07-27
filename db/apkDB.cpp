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
        sprintf(sql, "CREATE TABLE %s ( key varchar(128) PRIMARY KEY, pkgPath varchar(128),  md5 varchar(32) );", getTableName().c_str());
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
    if(apk.apkID.empty())
        return false;
    char sql[1024] ="";
    char* errMsg;
        sprintf(sql, "CREATE TABLE %s ( key integer PRIMARY KEY, pkgPath varchar(128),  md5 varchar(32) );", getTableName().c_str());

    sprintf(sql, "insert or replace into %s\
            (key, pkgPath, md5)\
       values( %s, \"%s\",  \"%s\");",
       getTableName().c_str(),
       apk.apkID.c_str(), 
       apk.pkgPath.c_str(),
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
        string      pkgPath;
        string      md5;

    apkInfo()
    {
    };
};
#endif

bool apkDB::get(apkInfo & apk)
{
    char sql[1024] = {0};
    sqlite3_stmt *stmt;
    int rc;

    sprintf(sql, "select pkgPath, md5 from %s where key = '%s';", getTableName().c_str(), apk.apkID.c_str());
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
        apk.pkgPath = string( (const char*)sqlite3_column_text(stmt,0)); 
        apk.md5     = string( (const char*)sqlite3_column_text(stmt,1));   
        //printf("%s\n",  (const char*)sqlite3_column_text(stmt,0));
    }   

    sqlite3_finalize(stmt);
    return true;
}

void print(const apkInfo& apk)
{
    printf("%20s,%20s,%20s\n", 
            "apkId", "pkgPath", "md5");
    printf("%20s,%20s,%20s\n", 
            apk.apkID.c_str(), apk.pkgPath.c_str(), apk.md5.c_str()
            );
}


bool apkDB::getRecordCount(int & count)
{
    char sql[1024] = {0};
    sqlite3_stmt *stmt;
    int rc;
    count = 0;

    sprintf(sql, "SELECT count(key) FROM '%s';", getTableName().c_str());
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
        count = sqlite3_column_int(stmt,0);
        printf("%d\n",  count);
    }   

    sqlite3_finalize(stmt);
    return true;
}

