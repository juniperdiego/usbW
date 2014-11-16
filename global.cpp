#include "global.h"

/*递归删除文件夹内容 
 ** 
 **dir :文件夹的名字,绝对路径和相对路径均可 
 ** 
 **返回值 :成功后返回true;否则返回false 
*/  
bool removeFileWithDir(const QString &dirName)
{  
    static QVector<QString> dirNames;  
    QDir dir;  
    QFileInfoList filst;  
    QFileInfoList::iterator curFi;  
    //初始化
    dirNames.clear();  
    if(dir.exists()){  
        dirNames<<dirName;  
    }  
    else{  
        return true;  
    }  
    //遍历各级文件夹，并将这些文件夹中的文件删除  
    for(int i=0;i<dirNames.size();++i)
    {  
        dir.setPath(dirNames[i]);  
        filst=dir.entryInfoList(QDir::Dirs|QDir::Files  
                |QDir::Readable|QDir::Writable  
                |QDir::Hidden|QDir::NoDotAndDotDot  
                ,QDir::Name);  
        if(filst.size()>0)
        {  
            curFi=filst.begin();  
            while(curFi!=filst.end())
            {  
                //遇到文件夹,则添加至文件夹列表dirs尾部  
                if(curFi->isDir())
                {  
                    dirNames.push_back(curFi->filePath());  
                }
                else if(curFi->isFile())
                {  
                    //遇到文件,则删除之  
                    if(!dir.remove(curFi->fileName()))
                    {  
                        //return false;  
                    }  
                }  
                curFi++;  
            }//end of while  
        }  
    }  

#if 0
    //删除文件夹 
    for(int i=dirNames.size()-1;i>=0;--i)
    {  
        if(!dir.rmdir(dirNames[i]))
        {  
            //return false;  
        }
    }
#endif

    return true;  
}  

QString Global::g_IP = 0;
std::string Global::g_DevID = "";
bool  Global::s_netState = false;
int Global::g_UnUpNum = 0;
USB_State Global::usb_state[DEVCOUNT] = {{0, 0, "", "", 0, 0, 0}};
bool  Global::s_needRestart = false;
QString Global::s_updateTime = "";

void Global::reboot()
{
    QProcess::execute("reboot");
}

void Global::setSysTime(const QString& t)
{
    if (t.isEmpty()) return;

    uint time = t.toUInt();
    QDateTime dateTime = QDateTime::fromTime_t(time);
    QString timeStr = dateTime.toString("yyyy.MM.dd-hh:mm:ss");
    QString cmd = QString("date -s %1").arg(timeStr);
    QProcess::execute(cmd);
    cmd = "hwclock -w";
    QProcess::execute(cmd);
}

string Global::encyptStr(const string& str)
{
    string result = str;
    for (size_t i = 0; i < str.length(); ++i)
    {
        result[i] = str[i] ^ ENCYPT_BIT;
    }

    return result;
}

void Global::clearApks()
{
    QStringList nameFilter;
    nameFilter.append("*.apk");
    QDir dir(APK_PATH);
    QStringList strFileLst;
    strFileLst.clear();
    if(dir.exists())
    {
        strFileLst = dir.entryList(nameFilter, QDir::Files | QDir::NoSymLinks);
        for(int i = 0; i < strFileLst.count(); i++)
        {
            QFile::remove(strFileLst[i]);
        }
    }
}

void Global::clearTmp()
{
    QStringList nameFilter;
    nameFilter.append("*.apk");
    QDir dir(TMP_PATH);
    QStringList strFileLst;
    strFileLst.clear();
    if(dir.exists())
    {
        strFileLst = dir.entryList(nameFilter, QDir::Files | QDir::NoSymLinks);
        for(int i = 0; i < strFileLst.count(); i++)
        {
            QFile::remove(strFileLst[i]);
        }
    }
}

void Global::clearDataAndReboot()
{
    removeFileWithDir(DB_PATH);    
    reboot();
}
