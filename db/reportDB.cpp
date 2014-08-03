#include "reportDB.h"

#if 0
{
    public:
        string          imei;  
        string          installDate;
        string          ua;
        string          chanID;
        string          macAdd;
        int             portIdx; 
        string          batchCode;
        bool            isUpload;

   reportInfo()
       :isUpload(2)
   {
   };

};

class reportDB :public sqlDB
{

    public:
        reportDB();
        ~reportDB();

        bool set(const reportInfo& rInfo);
        bool get(reportInfo& rInfo);
};

#endif



reportDB::reportDB()
{

    // 1. should open the db, but the db is opened
    
    // 2. name the divec talbe 
    setTableName("reportTable");

    // 3. create the table 
    char sql[1024] ="";
    if(!tableExist())
    {
        char* errMsg;
        // creat the table

        sprintf(sql, "CREATE TABLE %s (imei varchar(32), installDate varchar(32), model varchar(64),\
                        chanID varchar(64), macAdd varchar(32), portIdx integer, batchCode varchar(128),\
                        isUpload integer, ID INTEGER PRIMARY KEY AUTOINCREMENT, \
                        UNIQUE (imei, installDate));", getTableName().c_str());
        int rc =    sqlite3_exec(s_db, sql, NULL, NULL, &errMsg);
        if( rc ){   
            fprintf(stderr, "Can't create table %s: %s\n", getTableName().c_str(), errMsg);   
            sqlite3_close(s_db);   
            exit(1);
        }   

    }
}


reportDB::~reportDB()
{
}
        string          imei;  
        string          installDate;
        string          model;
        string          chanID;
        string          macAdd;
        int             portIdx; 
        string          batchCode;
        bool            isUpload;

bool reportDB::set( const reportInfo& report)
{
    char sql[1024] ="";
    char* errMsg;
    int isUpload ;
    sqlite3_stmt *stmt;

    if(report.isUpload)
        isUpload = 1;
    else
        isUpload = 2; // not upload


    sprintf(sql, "SELECT count(*) FROM '%s' where imei = '%s' and installDate = '%s';",
        getTableName().c_str(), report.imei.c_str(), report.installDate.c_str());


    int rc= sqlite3_prepare(s_db,sql, strlen(sql), &stmt,0);     
    if( rc ){   
        fprintf(stderr, "Can't open statement: %s\n", sqlite3_errmsg(s_db));   
        sqlite3_close(s_db);   
        return false;   
    }   

    //if exist, return directly
    while(sqlite3_step(stmt)==SQLITE_ROW ) {   
        sqlite3_finalize(stmt);
        return true;
    }   
    sqlite3_finalize(stmt);

    sprintf(sql, "insert or replace into %s \
            (imei, installDate, model, chanID, macAdd, portIdx, batchCode, isUpload, id) \
       values(\"%s\" ,\"%s\",   \"%s\",\"%s\",`\"%s\",  %d,     \"%s\",     %d,     %d);",
       getTableName().c_str(),
       report.imei.c_str(), 
       report.installDate.c_str(), 
       report.model.c_str(), 
       report.chanID.c_str(), 
       report.macAdd.c_str(), 
       report.portIdx, 
       report.batchCode.c_str(), 
       isUpload,
       report.id 
       );

    if(SQLITE_OK == sqlite3_exec(s_db, sql, NULL, NULL, &errMsg))
        return true;

    printf("Insert or replace failed in table %s: %s\n", getTableName().c_str(), errMsg);
    return false;

}

bool reportDB::getUnuploadedData(vector<reportInfo>& reportVector)
{
    char sql[1024] = {0};
    sqlite3_stmt *stmt;
    int rc;

    sprintf(sql, "select * from %s where isUpload = 2;", 
            getTableName().c_str());
#if 0
    {
        int nrow = 0, ncolumn = 0;
        char **azResult; 
        char * zErrMsg;

        char s[] = "SELECT * FROM mobileStatisticTable";
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

    while(sqlite3_step(stmt)==SQLITE_ROW ) {   
        reportInfo report;
       report.imei = string( (const char*)sqlite3_column_text(stmt,0));
       report.installDate = string( (const char*)sqlite3_column_text(stmt,1)); 
       report.model = string( (const char*)sqlite3_column_text(stmt,2)); 
       report.chanID = string( (const char*)sqlite3_column_text(stmt,3)); 
       report.macAdd = string( (const char*)sqlite3_column_text(stmt,4));
       report.portIdx = sqlite3_column_int(stmt,5 );
       report.batchCode = string( (const char*)sqlite3_column_text(stmt,6));
       isUpload = false;
       reportVector.push_back(report);
    }   

    sqlite3_finalize(stmt);
    return true;
}

bool reportDB::getModel(const string& date1, const string& date2, vector<reportInfo> & reportVector)
{
    char sql[1024] = {0};
    sqlite3_stmt *stmt;
    int rc;

    reportVector.clear();

    sprintf(sql, "select installDate, model, count(*) from %s where date >= '%s' and date <= '%s' GROUP BY installDate, model order by installDate, model ;",
        getTableName().c_str(), date1.c_str(), date2.c_str());
#if 0
    {
        int nrow = 0, ncolumn = 0;
        char **azResult; 
        char * zErrMsg;

        char s[] = "SELECT * FROM mobileStatisticTable";
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

    while(sqlite3_step(stmt)==SQLITE_ROW ) {   
        reportInfo report;

        report.installDate = string( (const char*)sqlite3_column_text(stmt,0));   
        report.model = string( (const char*)sqlite3_column_text(stmt,1));   
        report.count   = sqlite3_column_int(stmt,2);   

        reportVector.push_back(report);
    }   

    sqlite3_finalize(stmt);
    return true;
}


bool reportDB::getUsb(const string& date1, const string& date2, vector<reportInfo> & reportVector)
{
    char sql[1024] = {0};
    sqlite3_stmt *stmt;
    int rc;

    reportVector.clear();

    sprintf(sql, "select installDate, portIdx, count(*) from %s where date >= '%s' and date <= '%s' GROUP BY installDate, portIdx order by installDate, portIdx;",
        getTableName().c_str(), date1.c_str(), date2.c_str());
#if 0
    {
        int nrow = 0, ncolumn = 0;
        char **azResult; 
        char * zErrMsg;

        char s[] = "SELECT * FROM mobileStatisticTable";
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

    while(sqlite3_step(stmt)==SQLITE_ROW ) {   
        reportInfo report;

        report.installDate = string( (const char*)sqlite3_column_text(stmt,0));   
        report.portIdx = sqlite3_column_int(stmt,1);
        report.count   = sqlite3_column_int(stmt,2);   

        reportVector.push_back(report);
    }   

    sqlite3_finalize(stmt);
    return true;
}


#if 0
void print(const reportInfo& msi)
{

    printf("%20s,%20s,%20s\n", 
            "mblIdex", "date", "counter");
    printf("%20s,%20s,%20d\n", 
            msi.mblPattern.c_str(), msi.date.c_str(), msi.count
            );
}
#endif
