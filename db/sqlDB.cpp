#include "sqlDB.h"
//#include "../global.h"
#define DB_PATH ""

sqlite3 * sqlDB::s_db = NULL;
unsigned int sqlDB::s_refCnt = 0;

int isExisted( void * para, int /*n_column*/, char ** column_value, char ** /*column_name*/ ) 
{ 
        bool *isExisted_=(bool*)para; 
            *isExisted_= (**column_value) != '0'; 
                return 0; 
}

sqlDB::sqlDB()
{
    s_refCnt ++;
    //cout << "Ctor" ;
    //cout << "s_refCnt \t" << s_refCnt<<endl;
    if(s_db == NULL)
    {
        const string dbName = string(DB_PATH) + "zig.db";

        // 1. open the database
        int rc;
        rc = sqlite3_open(dbName.c_str(), &s_db);
        if( rc )
        {
            fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(s_db));
            sqlite3_close(s_db);
            exit(1);
        }
    }
}

sqlDB::~sqlDB()
{
    s_refCnt --;
    //cout << "Destor" ;
    //cout << "s_refCnt \t" << s_refCnt<<endl;
#if 1
    if(s_refCnt == 0 && s_db != NULL)
    {
        sqlite3_close(s_db);
        s_db = NULL;
    }
#endif
}

bool sqlDB::tableExist()
{
    bool bExist;
    char *zErrMsg = 0;
    int rc;

    char str[1024];
    sprintf(str, "SELECT count(*) FROM sqlite_master WHERE type='table' AND name='%s';", m_tabName.c_str());
    rc = sqlite3_exec( s_db , str , isExisted , & bExist, &zErrMsg );
    if( rc )
    {
        fprintf(stderr, "function tableExist() : %s\n", sqlite3_errmsg(s_db));
        sqlite3_close(s_db);
        exit(1);
    }
    return bExist;
}

bool sqlDB::insertToTable(int key, string val)
{
    char sql[1024] ="";
    char* errMsg = NULL;
    sprintf(sql, "insert into %s (key, val)  values( %d, \"%s\" );", m_tabName.c_str(), key, val.c_str());
    if(SQLITE_OK == sqlite3_exec(s_db, sql, NULL, NULL, &errMsg))
        return true;
    return false;
}

int sqlDB::sqlInit()
{
    return true;
}


bool sqlDB::exist_in_db(sqlite3 *db, const string table, const string id ){
    char sql_query[1024]={0};
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


bool sqlDB::deleteTable()
{

    char sql[1024] ="";
    char* errMsg = NULL;
    sprintf(sql, "drop table %s;", m_tabName.c_str());
    if(SQLITE_OK != sqlite3_exec(s_db, sql, NULL, NULL, &errMsg))
        return false;
    sprintf(sql, "VACUUM;" );
    if(SQLITE_OK != sqlite3_exec(s_db, sql, NULL, NULL, &errMsg))
        return false;
    return true;
}



bool sqlDB::clearTableItems()
{
    char sql[1024] ="";
    char* errMsg = NULL;
    sprintf(sql, "DELETE FROM %s;", m_tabName.c_str());
    if(SQLITE_OK != sqlite3_exec(s_db, sql, NULL, NULL, &errMsg))
        return false;
    return true;
}

string sqlDB::getTableName()
{
    return m_tabName;
}

 void sqlDB::setTableName(const string& tabName)
{
    m_tabName =  tabName;
}


void getDate( char *date, long int diff)
{
    size_t dateLength = 12;
    time_t timep=time(0);
    timep -= diff;
    strftime( date, dateLength, "%Y%m%d", localtime(&timep));
}

