#include "usbStatDB.h"

usbStatDB::usbStatDB()
{

    // 1. should open the db, but the db is opened
    
    // 2. name the divec talbe 
    setTableName("usbStatisticTable");

    // 3. create the table 
    char sql[1024] ="";
    if(!tableExist())
    {
        char* errMsg;
        // creat the table

//	sprintf(sql, "create table %s ( id varchar(128), date varchar(32), cnt int, primary key(id, date))", getTableName().c_str());
        sprintf(sql, "CREATE TABLE %s (usbIndex integer, date varchar(32), count integer, PRIMARY KEY (usbIndex, date));", getTableName().c_str());
        int rc =    sqlite3_exec(s_db, sql, NULL, NULL, &errMsg);
        if( rc ){   
            fprintf(stderr, "Can't create table %s: %s\n", getTableName().c_str(), errMsg);   
            sqlite3_close(s_db);   
            exit(1);
        }   
    }
}

usbStatDB::~usbStatDB()
{
}

bool usbStatDB::set( const usbStatInfo& usbStat)
{
    char sql[1024] ="";
    char* errMsg;

    sprintf(sql, "insert or replace into %s\
            (usbIndex, date, count)\
       values( %d,\"%s\", %d);",
       getTableName().c_str(),
       usbStat.usbIdx, 
       usbStat.date.c_str(), 
       usbStat.count 
       );

    if(SQLITE_OK == sqlite3_exec(s_db, sql, NULL, NULL, &errMsg))
        return true;

    printf("Insert or replace failed in table %s: %s\n", getTableName().c_str(), errMsg);
    return false;

}

bool usbStatDB::get(const string& date1, const string& date2, vector<usbStatInfo> & usiArray)
{
    char sql[1024] = {0};
    sqlite3_stmt *stmt;
    int rc;

    usiArray.clear();

    sprintf(sql, "select * from %s where date >= '%s' and date <= '%s';",
        getTableName().c_str(), date1.c_str(), date2.c_str());
#if 1
    {
        int nrow = 0, ncolumn = 0;
        char **azResult; 
        char * zErrMsg;

        char s[] = "SELECT * FROM usbStatisticTable";
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
        usbStatInfo usi;

        usi.usbIdx  = sqlite3_column_int(stmt,0);   
        usi.date    = string( (const char*)sqlite3_column_text(stmt,1));   
        usi.count   = sqlite3_column_int(stmt,2);   

        usiArray.push_back(usi);
    }   

    sqlite3_finalize(stmt);
    return true;
}


bool usbStatDB::increase(int usbIdx)
{
    char  sql[512];
    string date;
    char today[12];
    getDate( today, 0);
    
    // check if database have this record
    // if not exist, initialize count = 0
    vector<usbStatInfo>  usiArray;
    get(today, today, usiArray);
    if(usiArray.empty())
    {
        usbStatInfo usbStatIn;
        usbStatIn.usbIdx = usbIdx; 
        usbStatIn.date = today;
        usbStatIn.count = 0;
        set(usbStatIn);
    }

    sprintf(sql, "update %s set count = count +1 where id='%d' and date='%s';", 
        getTableName().c_str(), usbIdx, date.c_str());

    char* errMsg;
    int rc =    sqlite3_exec(s_db, sql, NULL, NULL, &errMsg);
    if( rc ){   
        fprintf(stderr, "Can't update usbStateDB in table %s: %s\n", getTableName().c_str(), errMsg);   
        sqlite3_close(s_db);   
        exit(1);
    }   
    return true;
}


void print(const usbStatInfo& usi)
{

    printf("%20s,%20s,%20s\n", 
            "usbIdex", "date", "counter");
    printf("%20d,%20s,%20d\n", 
            usi.usbIdx, usi.date.c_str(), usi.count
            );
}
