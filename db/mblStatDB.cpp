#include "mblStatDB.h"

mblStatDB::mblStatDB()
{

    // 1. should open the db, but the db is opened
    
    // 2. name the divec talbe 
    setTableName("mobileStatisticTable");

    // 3. create the table 
    char sql[1024] ="";
    if(!tableExist())
    {
        char* errMsg;
        // creat the table

        sprintf(sql, "CREATE TABLE %s (mblPattern varchar(32), date varchar(32), count integer, PRIMARY KEY (mblPattern, date));", getTableName().c_str());
        int rc =    sqlite3_exec(s_db, sql, NULL, NULL, &errMsg);
        if( rc ){   
            fprintf(stderr, "Can't create table %s: %s\n", getTableName().c_str(), errMsg);   
            sqlite3_close(s_db);   
            exit(1);
        }   
    }
}

mblStatDB::~mblStatDB()
{
}

bool mblStatDB::set( const mblStatInfo& mblStat)
{
    char sql[1024] ="";
    char* errMsg;

    sprintf(sql, "insert or replace into %s\
            (mblPattern, date, count)\
       values(\"%s\" ,\"%s\", %d);",
       getTableName().c_str(),
       mblStat.mblPattern.c_str(), 
       mblStat.date.c_str(), 
       mblStat.count 
       );

    if(SQLITE_OK == sqlite3_exec(s_db, sql, NULL, NULL, &errMsg))
        return true;

    printf("Insert or replace failed in table %s: %s\n", getTableName().c_str(), errMsg);
    return false;

}

bool mblStatDB::get(const string& date1, const string& date2, vector<mblStatInfo> & msiArray)
{
    char sql[1024] = {0};
    sqlite3_stmt *stmt;
    int rc;

    msiArray.clear();

    sprintf(sql, "select * from %s where date >= '%s' and date <= '%s';",
        getTableName().c_str(), date1.c_str(), date2.c_str());
#if 0
    {
        int nrow = 0, ncolumn = 0;
        char **azResult; 
        char * zErrMsg;

        char* s = "SELECT * FROM mblStatisticTable";
        sqlite3_get_table(s_db , s , &azResult , &nrow , &ncolumn , &zErrMsg );

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
        mblStatInfo msi;

        msi.mblPattern= string( (const char*)sqlite3_column_text(stmt,0));   
        msi.date    = string( (const char*)sqlite3_column_text(stmt,1));   
        msi.count   = sqlite3_column_int(stmt,2);   

        msiArray.push_back(msi);
    }   

    sqlite3_finalize(stmt);
    return true;
}



void print(const mblStatInfo& msi)
{

    printf("%20s,%20s,%20s\n", 
            "mblIdex", "date", "counter");
    printf("%20s,%20s,%20d\n", 
            msi.mblPattern.c_str(), msi.date.c_str(), msi.count
            );
}
