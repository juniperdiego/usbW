#include "pkgDB.h"

pkgDB::pkgDB()
{

    // 1. should open the db, but the db is opened
    
    // 2. name the divec talbe 
    setTableName("packageTable");

    // 3. create the table 
    char sql[1024] ="";
    if(!tableExist())
    {
        char* errMsg;
        // creat the table
        sprintf(sql, "CREATE TABLE %s ( key varchar(128) PRIMARY KEY, pkgName varchar(128), batchCode varchar(32), apkList TEXT,  apkSum int,  date varchar(16));", getTableName().c_str());
        int rc =    sqlite3_exec(s_db, sql, NULL, NULL, &errMsg);
        if( rc ){   
            fprintf(stderr, "Can't create table %s: %s\n", getTableName().c_str(), errMsg);   
            sqlite3_close(s_db);   
            exit(1);
        }   
    }
}

pkgDB::~pkgDB()
{
}

bool pkgDB::set( const pkgInfo& pkg)
{
    if(pkg.pkgID.empty())
        return false;

    char sql[1024] ="";
    char* errMsg;

    string apkListStr;

    size_t size = pkg.apkList.size();
    for(size_t i = 0; i < size; i++)
    {
        apkListStr += pkg.apkList[i];
        //if(i != size -1)
            apkListStr += "|";
    }

    sprintf(sql, "insert or replace into %s\
            (key, pkgName, batchCode, apkList, apkSum, date)\
       values( \"%s\", \"%s\",   \"%s\",  \"%s\",   %d,    \"%s\");",
       getTableName().c_str(),
       pkg.pkgID.c_str(), 
       pkg.pkgName.c_str(),
       pkg.batchCode.c_str(),
       apkListStr.c_str(),
       pkg.apkSum,
       pkg.date.c_str()
       );

    if(SQLITE_OK == sqlite3_exec(s_db, sql, NULL, NULL, &errMsg))
        return true;
    return false;

}

#if 0
class pkgInfo
{
    public:
        string          pkgID;  
        string          pkgName;
        string          batchCode;
        vector<string>  apkList;
        int             apkSum;
        string          date;
};
#endif

bool pkgDB::get(pkgInfo & pkg)
{
    char sql[1024] = {0};
    sqlite3_stmt *stmt;
    int rc;

    sprintf(sql, "select pkgName, batchCode, apkList, apkSum, date from %s where key = '%s';", getTableName().c_str(), pkg.pkgID.c_str());
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
        pkg.pkgName = string( (const char*)sqlite3_column_text(stmt,0)); 
        pkg.batchCode = string( (const char*)sqlite3_column_text(stmt,1));
        str = string( (const char*)sqlite3_column_text(stmt,2));   
        pkg.apkSum = sqlite3_column_int(stmt,3);   
        pkg.date = string( (const char*)sqlite3_column_text(stmt,4));   
        //printf("%s\n",  (const char*)sqlite3_column_text(stmt,0));
    }   

    pkg.apkList.clear();   

    size_t start = 0; 
    size_t end = 0;

    for(size_t i = 0; i< str.size(); i++)
    {
        if(str[i] == '|')
        {
            end = i;
            string tmp =  str.substr(start, end-start);
            pkg.apkList.push_back(tmp);
            start = i+1;
        }
    }

    sqlite3_finalize(stmt);
    return true;
}
