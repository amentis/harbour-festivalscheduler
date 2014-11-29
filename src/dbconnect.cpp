#include "dbconnect.h"

DbConnect::DbConnect(QObject *parent) :
    QObject(parent) {
    QObject::connect(this, SIGNAL(festsChanged()), this, SLOT(updateFestsCache()));
    QObject::connect(this, SIGNAL(bandsChanged()), this, SLOT(updateBandsCache()));

    openDB();
    initialize();
}

DbConnect::~DbConnect() {
    db.close();
    festsCache.clear();
    bandsCache.clear();
}

bool DbConnect::openDB() {
    QString path(QQmlEngine::offlineStoragePath());
    path.append("festivalscheduler.sqlite");
    db.setDatabaseName(path);
    return db.open();
}

QSqlError DbConnect::lastError() {
    return db.lastError();
}

QString DbConnect::getUniqueId() {
    QDateTime date;
    return date.toString("yyyyMMddHHmmsszzz");
}

void DbConnect::initialize() {
    if (!db.isOpen()){
        qCritical() << lastError().text();
        return;
    }
    QSqlQuery query;
    bool result;
    result = query.exec("CREATE TABLE IF NOT EXISTS fests(uid LONGVARCHAR UNIQUE, name TEXT, day UNSIGNED BIG INT, numberOfDays TINYINT, place TEXT, numberOfScenes TINYINT)");
    if (!db.isOpen()){
        qCritical() << lastError().text();
        return;
    }
    emit festsChanged();
    result = query.exec("CREATE TABLE IF NOT EXISTS bands(uid LONGVARCHAR UNIQUE, fest LONGVARCHAR, starts UNSIGNED BIG INT, lasts SMALLINT, scene TINYINT);");
    if (!db.isOpen()){
        qCritical() << lastError().text();
        return;
    }
    emit bandsChanged();
}

QList<FestivalListItem*> DbConnect::listFests() {
    return festsCache;
}

FestivalListItem DbConnect::getFest(QString uid) {
    for (int i = 0; i < festsCache.length(); ++i) {
        if (festsCache.at(i)->uid() == uid)
            return festsCache.at(i);
    }
}

void DbConnect::setFest(QString uid, QString name, quint64 day, quint8 numberOfDays, QString place, quint64 numberOfScenes) {
    QSqlQuery query;
    query.exec(QString("INSERT OR REPLACE INTO fests VALUES('%1', '%2'', '%3', '%4', '%5', '%6')")
                    .arg(uid).arg(name).arg(day).arg(numberOfDays).arg(place).arg(numberOfScenes));
    emit festsChanged();
}

void DbConnect::removeFest(QString uid) {
    QSqlQuery query;
    query.exec(QString("DELETE FROM fests WHERE uid = %1").arg(uid));
    emit festsChanged();
    query.exec(QString("DELETE FROM bands WHERE fest = %1").arg(uid));
    emit bandsChanged();
}

QList<BandListItem*> DbConnect::listBands() {
    return bandsChanged();
}

BandListItem DbConnect::getBand(QString uid) {
    for (int i = 0; i < bandsCache.length(); ++i) {
        if (bandsCache.at(i)->uid() == uid){
            return bandsCache.at(i);
        }
    }
}

void DbConnect::setBand(QString uid, QString fest, quint64 starts, quint8 lasts, quint8 scene) {
    QSqlQuery query;
    query.exec(QString("INSERT OR REPLACE INTO bands VALUES('%1', '%2', '%3', '%4', '%5')")
               .arg(uid).arg(fest).arg(starts).arg(lasts).arg(scene));
    emit bandsChanged();
}

void DbConnect::removeBand(QString uid) {
    QSqlQuery query;
    query.exec(QString("DELETE FROM bands WHERE uid = %1").arg(uid));
    emit bandsChanged();
}

bool DbConnect::empty() {
    return festsCache.isEmpty();
}

void DbConnect::updateFestsCache() {
    festsCache.clear();
    QSqlQuery query;
    query.exec("SELECT * FROM fests");
    while (query.next()){
        festsCache.append(new FestivalListItem(query.value("uid").toString(),
                                               query.value("name").toString(),
                                               query.value("day").toUInt(),
                                               query.value("numberOfDays").toInt(),
                                               query.value("place").toString(),
                                               query.value("numberOfScenes").toInt()
                                               ));
    }
}

void DbConnect::updateBandsCache() {
    bandsCache.clear();
    QSqlQuery query;
    query.exec("SELECT * FROM bands");
    while (query.next()){
        bandsCache.append(new BandListItem(query.value("uid").toString(),
                                           query.value("fest").toString(),
                                           query.value("starts").toUInt(),
                                           query.value("lasts").toUInt(),
                                           query.value("scene").toUInt()
                                           ));
    }
}
