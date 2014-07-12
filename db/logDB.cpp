#include "logDB.h"

logDB::logDB()
{

    // 1. should open the db, but the db is opened
    
    // 2. name the divec talbe 
    setTableName("logTable");

    // 3. create the table 
    char sql[1024] ="";
    if(!tableExist())
    {
        char* errMsg;
        // creat the table

        sprintf(sql, "CREATE TABLE %s (date varchar(32) PRIMARY KEY, isUploaded integer);", getTableName().c_str());
        int rc =    sqlite3_exec(s_db, sql, NULL, NULL, &errMsg);
        if( rc ){   
            fprintf(stderr, "Can't create table %s: %s\n", getTableName().c_str(), errMsg);   
            sqlite3_close(s_db);   
            exit(1);
        }   
    }
}

logDB::~logDB()
{
}

bool logDB::set( const logInfo& log)
{
    char sql[1024] ="";
    char* errMsg;

    sprintf(sql, "insert or replace into %s\
            (date, isUploaded)\
       values(\"%s\" , %d);",
       getTableName().c_str(),
       log.date.c_str(), 
       log.isUploaded ? 1 : -1
       );

    if(SQLITE_OK == sqlite3_exec(s_db, sql, NULL, NULL, &errMsg))
        return true;

    printf("Insert or replace failed in table %s: %s\n", getTableName().c_str(), errMsg);
    return false;

}

bool logDB::get(const string& date1, const string& date2, vector<logInfo> & logArray)
{
    char sql[1024] = {0};
    sqlite3_stmt *stmt;
    int rc;

    logArray.clear();

    sprintf(sql, "select * from %s where date >= '%s' and date <= '%s';",
        getTableName().c_str(), date1.c_str(), date2.c_str());
#if 1
    {
        int nrow = 0, ncolumn = 0;
        char **azResult; 
        char * zErrMsg;

        char s[] = "SELECT * FROM logTable";
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
        logInfo logI;

        logI.date    = string( (const char*)sqlite3_column_text(stmt,0));   
        logI.isUploaded = sqlite3_column_int(stmt,1) == 1 ? true : false;   

        logArray.push_back(logI);
    }   

    sqlite3_finalize(stmt);
    return true;
}



void print(const logInfo& log)
{

    printf("%20s,%20s\n", 
             "date", "is uploaded");
    printf("%20s,%20d\n", 
            log.date.c_str(), log.isUploaded
            );
}
