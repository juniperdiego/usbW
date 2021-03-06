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

bool reportDB::getID( reportInfo& report)
{
    char sql[1024] ="";
    char* errMsg;
    int isUpload ;
    sqlite3_stmt *stmt;

    if(report.isUpload)
        isUpload = 1;
    else
        isUpload = 2; // not upload


    sprintf(sql, "SELECT id FROM '%s' where imei = '%s' and installDate = '%s';",
        getTableName().c_str(), report.imei.c_str(), report.installDate.c_str());


    int rc= sqlite3_prepare(s_db,sql, strlen(sql), &stmt,0);     
    if( rc ){   
        fprintf(stderr, "Can't open statement: %s\n", sqlite3_errmsg(s_db));   
        sqlite3_close(s_db);   
        return false;   
    }   

    while(sqlite3_step(stmt)==SQLITE_ROW ) {   
        report.id = sqlite3_column_int(stmt,0 );
    }   

    sqlite3_finalize(stmt);


    return false;

}
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


    sprintf(sql, "SELECT imei,installDate FROM '%s' where imei = '%s' and installDate = '%s';",
        getTableName().c_str(), report.imei.c_str(), report.installDate.c_str());


    int rc= sqlite3_prepare(s_db,sql, strlen(sql), &stmt,0);     
    if( rc ){   
        fprintf(stderr, "Can't open statement: %s\n", sqlite3_errmsg(s_db));   
        sqlite3_close(s_db);   
        return false;   
    }   

    //if exist, return directly
    while(sqlite3_step(stmt)==SQLITE_ROW ) {   
        //cout << "exist" << endl;
        sqlite3_finalize(stmt);
        return true;
    }   

    //cout << " not exist" << endl;
    sqlite3_finalize(stmt);

    sprintf(sql, "insert or replace into %s \
            (imei, installDate, model, chanID, macAdd, portIdx, batchCode, isUpload ) \
       values(\"%s\" ,\"%s\",   \"%s\",\"%s\", \"%s\",  %d,     \"%s\",     %d    );",
       getTableName().c_str(),
       report.imei.c_str(), 
       report.installDate.c_str(), 
       report.model.c_str(), 
       report.chanID.c_str(), 
       report.macAdd.c_str(), 
       report.portIdx, 
       report.batchCode.c_str(), 
       isUpload
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
       report.isUpload = false;
       report.id= sqlite3_column_int(stmt,8 );
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

    sprintf(sql, "select installDate, model, count(*) from %s where installDate >= '%s' and installDate <= '%s' GROUP BY installDate, model order by installDate, model ;",
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

    sprintf(sql, "select installDate, portIdx, count(*) from %s where installDate >= '%s' and installDate <= '%s' GROUP BY installDate, portIdx order by installDate, portIdx;",
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
        //cout << "coutn ::\t" <<sqlite3_column_int(stmt,2) <<endl;
        report.count   = sqlite3_column_int(stmt,2);   

        reportVector.push_back(report);
    }   

    sqlite3_finalize(stmt);
    return true;
}


bool reportDB::setUpload(int id)
{
    char sql[1024] = {0};
    sqlite3_stmt *stmt;
    int rc;


    sprintf(sql, "update %s set isUpload = 1 where id = %d ;",
        getTableName().c_str(), id);
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
    }   

    sqlite3_finalize(stmt);
    return true;
}

#if 1
void print(const vector<reportInfo>& vector)
{

    printf("%10s,%10s,%10s,%10s,%10s,%10s,%10s,%10s,%10s,%10s\n", 
            "mblIdex", "installdate", "model", "chanID","macAdd", "portIdx", "batchCode","isUpload", "id","count");
    for(size_t i = 0; i< vector.size(); i++)
    {
        reportInfo rIn = vector[i];
        printf("%10s,%10s,%10s,%10s,%10s,%10d,%10s,%10d,%10d %10d\n", 
                rIn.imei.c_str(),
                rIn.installDate.c_str(),
                rIn.model.c_str(),
                rIn.chanID.c_str(),
                rIn.macAdd.c_str(),
                rIn.portIdx,
                rIn.batchCode.c_str(),
                rIn.isUpload,
                rIn.id,
                rIn.count
              );
    }
}
#endif
