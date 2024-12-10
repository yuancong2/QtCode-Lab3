#include "idatabase.h"

void IDatabase::initDatabase()
{
    database = QSqlDatabase::addDatabase("QSQLITE");
    QString aFile = "../../Lab4.db";
    database.setDatabaseName(aFile);

    if (!database.open()) {
        qDebug() << "failed to open database";
    } else
        qDebug() << "open database is ok";
}

QString IDatabase::userLogin(QString userName, QString password)
{
    QSqlQuery query;
    query.prepare("select username,password from user where username = :USER");
    query.bindValue(":USER", userName);
    query.exec();

    if (query.first() && query.value("username").isValid()) {
        QString passwd = query.value("password").toString();
        if (passwd == password) {
            return "LoginOK";
        } else {
            return "wrongPassword";
        }

    } else {
        qDebug() << "no such user";
        return "LoginFailed";
    }
    query.first();

}

IDatabase::IDatabase(QObject *parent): QObject{parent}
{
    initDatabase();
}
