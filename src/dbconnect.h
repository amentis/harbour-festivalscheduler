#ifndef DBCONNECT_H
#define DBCONNECT_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>
#include <QList>
#include <QQmlEngine>
#include <QDateTime>
#include <QDate>
#include <QTime>

#include <QDebug>

#include "bandlistitem.h"
#include "festivallistitem.h"

class DbConnect : public QObject
{
	Q_OBJECT

	Q_PROPERTY(QString currentFest READ currentFest WRITE setcurrentFest NOTIFY currentFestChanged)
public:
	explicit DbConnect(QObject *parent = 0);
	~DbConnect();
	bool openDB();
	QSqlError lastError();
	Q_INVOKABLE QString getUniqueId();
	void initialize();
	Q_INVOKABLE QList<FestivalListItem*> listFests();
	Q_INVOKABLE FestivalListItem getFest(QString uid);
	Q_INVOKABLE void setFest(QString uid, QString name, QDate day, quint8 numberOfDays, QString place, quint64 numberOfScenes);
	Q_INVOKABLE void removeFest(QString uid);
	Q_INVOKABLE QList<BandListItem*> listBands();
	Q_INVOKABLE BandListItem getBand(QString uid);
	void setBand(QString uid, QString fest, QString name, QTime starts, quint8 lasts, quint8 scene);
	Q_INVOKABLE void setBand(QString uid, QString fest, QString name, QTime starts, QTime ends, quint8 scene);
	Q_INVOKABLE void removeBand(QString uid);
	Q_INVOKABLE bool empty();
	QString currentFest();
	void setcurrentFest(QString uid);

private:
	QSqlDatabase db;
	QList<FestivalListItem*> festsCache;
	QList<BandListItem*> bandsCache;
	QString _currentFest;
	void autoSelectFest();

signals:
	void festsChanged();
	void bandsChanged();
	void currentFestChanged();

private slots:
	void updateFestsCache();
	void updateBandsCache();

};

#endif // DBCONNECT_H
