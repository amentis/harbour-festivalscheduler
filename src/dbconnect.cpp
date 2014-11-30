#include "dbconnect.h"

DbConnect::DbConnect(QObject *parent) :
	QObject(parent) {
	QObject::connect(this, SIGNAL(festsChanged()), this, SLOT(updateFestsCache()));
	QObject::connect(this, SIGNAL(bandsChanged()), this, SLOT(updateBandsCache()));

	_currentFest = "";

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
	result = query.exec("CREATE TABLE IF NOT EXISTS bands(uid LONGVARCHAR UNIQUE, fest LONGVARCHAR,name TEXT, starts TEXT, lasts SMALLINT, scene TINYINT);");
	if (!db.isOpen()){
		qCritical() << lastError().text();
		return;
	}

	autoSelectFest();

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

void DbConnect::setFest(QString uid, QString name, QDate day, quint8 numberOfDays, QString place, quint64 numberOfScenes) {
	QSqlQuery query;
	QDateTime tmp;
	tmp.setDate(day);
	query.exec(QString("INSERT OR REPLACE INTO fests VALUES('%1', '%2'', '%3', '%4', '%5', '%6')")
					.arg(uid).arg(name).arg(tmp.currentMSecsSinceEpoch()).arg(numberOfDays).arg(place).arg(numberOfScenes));
	emit festsChanged();
	setcurrentFest(uid);
}

void DbConnect::removeFest(QString uid) {
	QSqlQuery query;
	query.exec(QString("DELETE FROM fests WHERE uid = %1").arg(uid));
	emit festsChanged();
	query.exec(QString("DELETE FROM bands WHERE fest = %1").arg(uid));

	autoSelectFest();

	emit bandsChanged();
}

QList<BandListItem*> DbConnect::listBands() {
	return bandsCache;
}

BandListItem DbConnect::getBand(QString uid) {
	for (int i = 0; i < bandsCache.length(); ++i) {
		if (bandsCache.at(i)->uid() == uid){
			return bandsCache.at(i);
		}
	}
}

void DbConnect::setBand(QString uid, QString fest,QString name, QTime starts, quint8 lasts, quint8 scene) {
	QSqlQuery query;
	QDateTime tmp;
	tmp.
			query.exec(QString("INSERT OR REPLACE INTO bands VALUES('%1', '%2', '%3', '%4', '%5', '%6')")
			   .arg(uid).arg(fest).arg(name).arg(starts.toString("hhmmsszzz")).arg(lasts).arg(scene));
	emit bandsChanged();
}

void DbConnect::setBand(QString uid, QString fest, QString name, QTime starts, QTime ends, quint8 scene){
	setBand(uid, fest, name, starts, starts.msecsTo(ends), scene);
}

void DbConnect::removeBand(QString uid) {
	QSqlQuery query;
	query.exec(QString("DELETE FROM bands WHERE uid = %1").arg(uid));
	emit bandsChanged();
}

bool DbConnect::empty() {
	return festsCache.isEmpty();
}

QString DbConnect::currentFest() {
	return _currentFest;
}

void DbConnect::setcurrentFest(QString uid) {
	if (uid != _currentFest){
		_currentFest = uid;
		emit currentFestChanged();
	}
}

void DbConnect::autoSelectFest() {
	if (festsCache.isEmpty())
		return;
	QDate soonestValue = QDate::setDate(2000,1,1);
	QString soonestName;
	for (int i = 0; i < festsCache; ++i) {
		if (festsCache.at(i)->day() == QDate::currentDate()){
			soonestName = festsCache.at(i)->uid();
			break;
		}
		if (festsCache.at(i)->day() < soonestValue) {
			if (soonestValue == 0) {
				soonestValue = festsCache.at(i)->day();
				soonestName = festsCache.at(i)->uid();
			} else {
				if (!tmp.date() < QDate::currentDate()){
					soonestValue = festsCache.at(i)->day();
					soonestName = festsCache.at(i)->uid();
				}
			}
		}
	}

	if (soonestValue.year() == 2000){
		soonestName = festsCache.last();
	}

	setcurrentFest(soonestName);
}

void DbConnect::updateFestsCache() {
	festsCache.clear();
	QSqlQuery query;
	query.exec("SELECT * FROM fests");
	while (query.next()){
		QDateTime tmp;
		tmp.setMSecsSinceEpoch(query.value("day").toUInt());
		festsCache.append(new FestivalListItem(query.value("uid").toString(),
											   query.value("name").toString(),
											   tmp.date(),
											   query.value("numberOfDays").toInt(),
											   query.value("place").toString(),
											   query.value("numberOfScenes").toInt()
											   ));
	}
}

void DbConnect::updateBandsCache() {
	bandsCache.clear();
	QSqlQuery query;
	query.exec(QString("SELECT * FROM bands WHERE fest = %1").arg(currentFest()));
	while (query.next()){
		QTime tmp;
		tmp = QTime::fromString(query.value("starts").toString(), "hhmmsszzz");
		bandsCache.append(new BandListItem(query.value("uid").toString(),
										   query.value("fest").toString(),
										   query.value("name").toString(),
										   tmp,
										   query.value("lasts").toUInt(),
										   query.value("scene").toUInt()
										   ));
	}
}
