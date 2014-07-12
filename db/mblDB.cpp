#include "mblDB.h"

mblDB::mblDB()
{

    // 1. should open the db, but the db is opened
    
    // 2. name the divec talbe 
    setTableName("mobileTable");

    // 3. create the table 
    char sql[1024] ="";
    if(!tableExist())
    {
        char* errMsg;
        // creat the table
        sprintf(sql, "CREATE TABLE %s ( key integer PRIMARY KEY, pkgID int);", getTableName().c_str());
        int rc =    sqlite3_exec(s_db, sql, NULL, NULL, &errMsg);
        if( rc ){   
            fprintf(stderr, "Can't create table %s: %s\n", getTableName().c_str(), errMsg);   
            sqlite3_close(s_db);   
            exit(1);
        }   
    }
}

mblDB::~mblDB()
{
}

bool mblDB::set( const mblInfo& mbl)
{
    char sql[1024] ="";
    char* errMsg;

    sprintf(sql, "insert or replace into %s\
            (key, pkgID)\
       values( %d, %d);",
       getTableName().c_str(),
       mbl.mblID, 
       mbl.pkgID 
       );

    if(SQLITE_OK == sqlite3_exec(s_db, sql, NULL, NULL, &errMsg))
        return true;
    return false;

}

bool mblDB::get(mblInfo & mbl)
{
    char sql[1024] = {0};
    sqlite3_stmt *stmt;
    int rc;

    sprintf(sql, "select pkgID from %s where key = '%d';", getTableName().c_str(), mbl.mblID);
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
        mbl.pkgID = sqlite3_column_int(stmt,3);   
        //printf("%s\n",  (const char*)sqlite3_column_text(stmt,0));
    }   

    sqlite3_finalize(stmt);
    return true;
}
