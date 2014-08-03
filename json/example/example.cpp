#include <QFile>
#include <QTextStream>
#include <QDebug>

#include "json.h"

using QtJson::JsonObject;
using QtJson::JsonArray;

QString readFile(const QString &filename) {
    QFile f(filename);
    if (!f.open(QFile::ReadOnly | QFile::Text)) {
        return QString();
    } else {
        QTextStream in(&f);
        return in.readAll();
    }
}

void printResult(const JsonObject &result) {
    qDebug() << "apkVersion:" << result["apkVersion"].toString();
    qDebug() << "status:" << result["status"].toInt();
    qDebug() << "apkList:";

    JsonArray apks = result["apkList"].toList();
    foreach(QVariant apk, apks) {
        JsonObject apkMap = apk.toMap();
        qDebug() << "apkId" << apkMap["apkId"].toInt();
        qDebug() << "md5value" << apkMap["md5value"].toString();
        qDebug() << "path" << apkMap["path"].toString();
        qDebug() << "type" << apkMap["type"].toString();
        qDebug() << "packagePath" << apkMap["packagePath"].toString();
        qDebug()<<"";
    }
}

void printJson(const JsonObject &result) {
    qDebug() << QtJson::serialize(result);
}

int main(int argc, char **argv) {
    QString json = readFile("apkLib.json");
    if (json.isEmpty()) {
        qFatal("Could not read JSON file!");
        return 1;
    }

    bool ok;
    JsonObject result = QtJson::parse(json, ok).toMap();
    if (!ok) {
        qFatal("An error occurred during parsing");
        return 1;
    }

    printResult(result);

#if 0
    // Add extra object to result which contains an array of keywords and a ratio.
    JsonArray keywords = JsonArray() << "json" << "qt" << "parser";
    JsonObject extra;
    extra["ratio"] = 3.35;
    extra["keywords"] = keywords;
    result["extra"] = extra;
#endif
    JsonArray infos;
    JsonObject info;
    info["content"] = "aaaaaaaaaaaaaaaaaa";
    info["id"] = "1111111";

    info["content"] = "bbbbbbbbbbbbbbb";
    info["id"] = "2222222";
    infos.append(info);

    printJson(result);

    return 0;
}
