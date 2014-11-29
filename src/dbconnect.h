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

#include <QDebug>

#include "bandlistitem.h"
#include "festivallistitem.h"

class DbConnect : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool empty READ empty)
public:
    explicit DbConnect(QObject *parent = 0);
    ~DbConnect();
    bool openDB();
    QSqlError lastError();
    QString getUniqueId();
    void initialize();
    QList<FestivalListItem*> listFests();
    FestivalListItem getFest(QString uid);
    void setFest(QString uid, QString name, quint64 day, quint8 numberOfDays, QString place, quint64 numberOfScenes);
    void removeFest(QString uid);
    QList<BandListItem*> listBands();
    BandListItem getBand(QString uid);
    void setBand(QString uid, QString fest, quint64 starts, quint8 lasts, quint8 scene);
    void removeBand(QString uid);
    bool empty();

private:
    QSqlDatabase db;
    QList<FestivalListItem*> festsCache;
    QList<BandListItem*> bandsCache;

signals:
    void festsChanged();
    void bandsChanged();

private slots:
    void updateFestsCache();
    void updateBandsCache();

};

#endif // DBCONNECT_H
