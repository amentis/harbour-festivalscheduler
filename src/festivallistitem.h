#ifndef FESTIVALLISTITEM_H
#define FESTIVALLISTITEM_H

#include <QObject>
#include <QString>
#include <QDate>
#include <QDateTime>

class FestivalListItem : public QObject
{
	Q_OBJECT

	Q_PROPERTY(QString uid READ uid WRITE setuid NOTIFY uidChanged)
	Q_PROPERTY(QString name READ name WRITE setname NOTIFY nameChanged)
	Q_PROPERTY(QDate day READ day WRITE setday NOTIFY dayChanged)
	Q_PROPERTY(quint8 numberOfDays READ numberOfDays WRITE setnumberOfDays NOTIFY numberOfDaysChanged)
	Q_PROPERTY(QString place READ place WRITE setplace NOTIFY placeChanged)
	Q_PROPERTY(quint8 numberOfScenes READ numberOfScenes WRITE setnumberOfScenes NOTIFY numberOfScenesChanged)

public:
	explicit FestivalListItem(QObject *parent = 0);
	FestivalListItem(QString uid, QString name, QDate day, quint8 numberOfDays, QString place, quint8 numberOfScenes, QObject *parent = 0);
	~FestivalListItem();
	QString uid();
	void setuid(QString newUid);

	QString name();
	void setname(QString newName);

	QDate day();
	void setday(QDate newDay);

	quint8 numberOfDays();
	void setnumberOfDays(quint8& newNumberOfDays);

	QString place();
	void setplace(QString newPlace);

	quint8 numberOfScenes();
	void setnumberOfScenes(quint8& newNumberOfScenes);

private:
	QString* _uid;
	QString* _name;
	QDate* _day;
	quint8 _numberOfDays;
	QString* _place;
	quint8 _numberOfScenes;

signals:
	void uidChanged();
	void nameChanged();
	void dayChanged();
	void numberOfDaysChanged();
	void placeChanged();
	void numberOfScenesChanged();
	void dayAsDateChanged();
public slots:

};

#endif // FESTIVALLISTITEM_H
