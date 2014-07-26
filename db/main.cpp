#include "devDB.h"
#include "pkgDB.h"
#include "apkDB.h"
#include "usbStatDB.h"
#include "mblStatDB.h"
#include "logDB.h"

using namespace std;




int main()
{
#if 0
    // 1  test devDB
    devDB  dev_db;

    string devVer;
    string pkgVer;
    string apkVer;
    string chanID;

    dev_db.get(DEV_VER, devVer);
    dev_db.get(PKG_VER, pkgVer);
    dev_db.get(APK_VER, apkVer);
    dev_db.get(CHAN_ID, chanID);

    cout <<"devVer\t" << devVer<<endl;
    cout <<"pkgVer\t" << pkgVer<<endl;
    cout <<"apkVer\t" << apkVer<<endl;
    cout <<"chanID\t" << chanID<<endl;

    dev_db.set(DEV_VER, "devvv");
    dev_db.set(PKG_VER, "pkgvv");
    dev_db.set(APK_VER, "apkvv");
    dev_db.set(CHAN_ID, "chanvv");

    dev_db.get(DEV_VER, devVer);
    dev_db.get(PKG_VER, pkgVer);
    dev_db.get(APK_VER, apkVer);
    dev_db.get(CHAN_ID, chanID);

    cout <<"devVer\t" << devVer<<endl;
    cout <<"pkgVer\t" << pkgVer<<endl;
    cout <<"apkVer\t" << apkVer<<endl;
    cout <<"chanID\t" << chanID<<endl;
    cout << endl;

    // 2  test pkgDB
#if 0
    class pkgInfo
    {
        public:
            int             pkgID;  
            string          pkgName;
            string          batchCode;
            vector<string>  apkList;
            int             apkSum;
            string          date;
    };
#endif
    devDB  dev_db2;
    pkgDB  pkg_db;
    pkgInfo pInfo;

    vector<string>  apkList;
    apkList.push_back("1.apk");
    apkList.push_back("2.apk");
    apkList.push_back("3.apk");
    apkList.push_back("4.apk");
    apkList.push_back("5.apk");
    apkList.push_back("6.apk");
    apkList.push_back("7.apk");

    pInfo.pkgID = "100";
    pInfo.pkgName = "name1";
    pInfo.batchCode = "batchcode1";
    pInfo.apkList  = apkList;
    pInfo.apkSum = apkList.size();
    pInfo.date = "20140707121212";

    bool suc = pkg_db.set(pInfo);
    if(suc == true)
        cout << "insert suc"<<endl;
    else
        cout << "insert fail"<<endl;



    int nrow = 0, ncolumn = 0;
    char **azResult; 
    char * zErrMsg;

    char sql[1024] = "SELECT * FROM packageTable";
    sqlite3_get_table( pkg_db.get_db() , sql , &azResult , &nrow , &ncolumn , &zErrMsg );

    int i = 0 ;
    printf( "row:%d column=%d \n" , nrow , ncolumn );
    printf( "\nThe result of querying is : \n" );

    for( i=0 ; i<( nrow + 1 ) * ncolumn ; i++ )
        printf( "azResult[%d] = %s\n", i , azResult[i] );






    pkg_db.get(pInfo);

    cout << "pInfo.pkgID\t" << pInfo.pkgID<<endl;
    cout << "pInfo.pkgName \t" << pInfo.pkgName<<endl;
    cout << "pInfo.batchCode\t" <<pInfo.batchCode <<endl;
    cout << "pInfo.apkSum  \t" << pInfo.apkSum <<endl;
    cout << "pInfo.date \t" << pInfo.date<<endl;

    for(size_t i = 0; i< pInfo.apkList.size(); i++)
    {
        cout << pInfo.apkList[i] << "\t";
    }
    cout << endl;

#if 1
    apkList.push_back("8.apk");
    pInfo.pkgID = "200";
    pInfo.pkgName = "name2";
    pInfo.batchCode = "batchcode2";
    pInfo.apkList  = apkList;
    pInfo.apkSum = apkList.size();
    pInfo.date = "20140707144488";

    pkg_db.set(pInfo);
    pkg_db.get(pInfo);
    cout << "pInfo.pkgID\t" << pInfo.pkgID<<endl;
    cout << "pInfo.pkgName \t" << pInfo.pkgName<<endl;
    cout << "pInfo.batchCode\t" <<pInfo.batchCode <<endl;
    cout << "pInfo.apkSum  \t" << pInfo.apkSum <<endl;
    cout << "pInfo.date \t" << pInfo.date<<endl;

    for(size_t i = 0; i< pInfo.apkList.size(); i++)
    {
        cout << pInfo.apkList[i] << "\t";
    }
    cout << endl;
#endif

    vector<pkgInfo> pkgVector;
    pkg_db.getAll(pkgVector);

    for(int i = 0; i< pkgVector.size(); i++)
    {
        cout << "===================" << endl;
        cout << "pInfo.pkgID\t" <<  pkgVector[i].pkgID<<endl;
        cout << "pInfo.pkgName \t" << pkgVector[i].pkgName<<endl;
        cout << "pInfo.batchCode\t" << pkgVector[i].batchCode <<endl;
        cout << "pInfo.apkSum  \t" << pkgVector[i].apkSum <<endl;
        cout << "pInfo.date \t" << pkgVector[i].date<<endl;
        cout << "===================" << endl;
    }

    
    // 3 test exist/delet/clear table
    bool rc = pkg_db.tableExist();
    cout <<"exist \t" << rc<< endl;

    sprintf(sql,"SELECT count(*) FROM sqlite_master WHERE type='table';");
    //sprintf(sql, "SELECT * FROM packageTable");
    sqlite3_get_table( pkg_db.get_db() , sql , &azResult , &nrow , &ncolumn , &zErrMsg );

    printf( "row:%d column=%d \n" , nrow , ncolumn );
    printf( "\nThe result of querying is : \n" );

    for( i=0 ; i<( nrow + 1 ) * ncolumn ; i++ )
        printf( "azResult[%d] = %s\n", i , azResult[i] );

    // clear
    pkg_db.clearTableItems();
    rc = pkg_db.tableExist();
    cout <<"after clear ====== exist \t" << rc<< endl;
    
    sqlite3_get_table( pkg_db.get_db() , sql , &azResult , &nrow , &ncolumn , &zErrMsg );

    printf( "row:%d column=%d \n" , nrow , ncolumn );
    printf( "\nThe result of querying is : \n" );

    for( i=0 ; i<( nrow + 1 ) * ncolumn ; i++ )
        printf( "azResult[%d] = %s\n", i , azResult[i] );

    // delete
    pkg_db.deleteTable();
    dev_db.deleteTable();
    rc = pkg_db.tableExist();
    cout <<"after delete ===== exist \t" << rc<< endl;

    sqlite3_get_table( pkg_db.get_db() , sql , &azResult , &nrow , &ncolumn , &zErrMsg );

    printf( "row:%d column=%d \n" , nrow , ncolumn );
    printf( "\nThe result of querying is : \n" );

    for( i=0 ; i<( nrow + 1 ) * ncolumn ; i++ )
        printf( "azResult[%d] = %s\n", i , azResult[i] );


    // apkDB

#if 0
class apkInfo {
    public:
        int         apkID;
        string      pkgName;
        int         counter;
        dspIcon     dIcon;
        autoRun     aRun;
        string      md5;

    apkInfo()
            :apkID(INVALID_ID),
            counter(0),
            dIcon(noDsp), 
            aRun(noRun) 
    {
    };
};
#endif
    apkDB  apk_db;
    apkInfo aInfo;

    apk_db.get(aInfo);
    print(aInfo);

    aInfo.apkID  = "2000";
    aInfo.pkgPath= "xxxpkdfd";
    aInfo.counter = 3454;
    aInfo.dIcon = true;
    aInfo.aRun = true;
    aInfo.md5 = "12345678901234567890123456789023";

    apk_db.set(aInfo);
    apk_db.get(aInfo);
    print(aInfo);

    aInfo.apkID  = "2003";
    aInfo.pkgPath = "xcvcvxxxpkdfd";
    aInfo.counter = 345455555;
    aInfo.dIcon = false;
    aInfo.aRun = false;
    aInfo.md5 = "1234xxxx678901234567890123456789023";

    apk_db.set(aInfo);

    aInfo.apkID  = "2004";
    aInfo.pkgPath = "xcvcvxxxpkdfd";
    aInfo.counter = 345455555;
    aInfo.dIcon = false;
    aInfo.aRun = false;
    aInfo.md5 = "1234xxxx678901234567890123456789023";

    apk_db.set(aInfo);
    apk_db.get(aInfo);
    
    print(aInfo);

    int count ;

    apk_db.getRecordCount(count);
    
    cout << "==================count\t" << count << endl;

#endif

    // 4 test usbStat
    usbStatDB usd;
    
    usbStatInfo usi;

    //usi.usbIdx =  5;  
    //usi.date = "20140726";
    //usi.count = 10;
    //usd.set(usi);

    usi.usbIdx =  5;  
    usi.date = "20140725";
    usi.count = 100;
    usd.set(usi);

    usi.usbIdx =  4;  
    usi.date = "20140726";
    usi.count = 200;
    usd.set(usi);
    vector<usbStatInfo> array;

    usd.get("20140726","20140726", array);
    for(size_t i = 0; i< array.size(); i++)
    {
        print(array[i]);
    }
    cout << endl;

    usd.get("20140725","20140726", array);
    for(size_t i = 0; i< array.size(); i++)
    {
        print(array[i]);
    }
    cout << endl;

    usd.increase(5);
    usd.increase(4);

    cout << "=========" << endl;
    usd.get("20140726","20140726", array);
    for(size_t i = 0; i< array.size(); i++)
    {
        print(array[i]);
    }


#if 0
    // 4 test mblStat
    mblStatDB msd;
    
    mblStatInfo msi;
    msi.mblPattern =  "Nokia";  
    msi.date = "20140725";
    msi.count = 10;
    msd.set(msi);


    //msi.mblPattern =  "Nokia";  
    //msi.date = "20140726";
    //msi.count = 0;
    //msd.set(msi);

    msi.mblPattern =  "MOto";  
    msi.date = "20140724";
    msi.count = 20;
    msd.set(msi);

    msi.mblPattern =  "Moto";  
    msi.date = "20140724";
    msi.count = 30;
    msd.set(msi);

    msi.mblPattern =  "MOTO";  
    msi.date = "20140725";
    msi.count = 40;
    msd.set(msi);

    msi.mblPattern =  "APPLE";  
    msi.date = "20140726";
    //msi.count = 50;
    msd.set(msi);

    msi.mblPattern =  "APPLE";  
    msi.date = "20140725";
    msi.count = 70;
    msd.set(msi);

    vector<mblStatInfo> m_array;

    msd.get("20140726","20140726", m_array);
    for(size_t i = 0; i< m_array.size(); i++)
    {
        print(m_array[i]);
    }
    
    cout << endl;

    msd.get("20140725","20140726", m_array);
    for(size_t i = 0; i< m_array.size(); i++)
    {
        print(m_array[i]);
    }
    cout << endl;


    msd.get("20140724","20140725", m_array);
    for(size_t i = 0; i< m_array.size(); i++)
    {
        print(m_array[i]);
    }
    cout << endl;

    msd.increase("APPLE");
    msd.increase("Nokia");
    cout << "============"<< endl;
    msd.get("20140726","20140726", m_array);
    for(size_t i = 0; i< m_array.size(); i++)
    {
        print(m_array[i]);
    }


    // 5 test mblStat
    logDB logdb;
    logInfo loginfo;
    vector<logInfo> logArray;

    loginfo.date = "2012-01-01";
    loginfo.isUploaded = true;
    logdb.set(loginfo);

    loginfo.date = "2012-01-08";
    loginfo.isUploaded = false;
    logdb.set(loginfo);

    loginfo.date = "2012-01-04";
    loginfo.isUploaded = true;
    logdb.set(loginfo);
    
    loginfo.date = "2012-01-02";
    loginfo.isUploaded = true;
    logdb.set(loginfo);
    

    logdb.get("2012-01-01","2012-01-03", logArray);
    for(size_t i = 0; i< logArray.size(); i++)
    {
        print(logArray[i]);
    }
    cout << endl;

    logdb.get("2012-01-01","2012-01-05", logArray);
    for(size_t i = 0; i< logArray.size(); i++)
    {
        print(logArray[i]);
    }
    cout << endl;

    logdb.get("2012-01-01","2012-01-08", logArray);
    for(size_t i = 0; i< logArray.size(); i++)
    {
        print(logArray[i]);
    }
    cout << endl;
#endif

    return 0;
}
