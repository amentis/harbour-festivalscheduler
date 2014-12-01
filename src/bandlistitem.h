#ifndef BANDLISTITEM_H
#define BANDLISTITEM_H

#include <QObject>
#include <QString>
#include <QDate>
#include <QDateTime>
#include <QTime>

class BandListItem : public QObject
{
	Q_OBJECT

	Q_PROPERTY(QString uid READ uid WRITE setuid NOTIFY uidChanged)
	Q_PROPERTY(QString fest READ fest WRITE setfest NOTIFY festChanged)
	Q_PROPERTY(QString name READ name WRITE setname NOTIFY nameChanged)
	Q_PROPERTY(QTime starts READ starts WRITE setstarts NOTIFY startsChanged)
	Q_PROPERTY(quint8 lasts READ lasts WRITE setlasts NOTIFY lastsChanged)
	Q_PROPERTY(quint8 scene READ scene WRITE setscene NOTIFY sceneChanged)
	Q_PROPERTY(QTime ends READ ends)

private:
	QString* _uid;
	QString* _fest;
	QString* _name;
	QTime* _starts;
	quint8 _lasts;
	quint8 _scene;
public:
	explicit BandListItem(QObject *parent = 0);
	BandListItem(QString uid, QString fest, QString name, QTime starts, quint8 lasts, quint8 scene, QObject *parent = 0);
	~BandListItem();
	QString uid();
	void setuid(QString uid);
	QString fest();
	void setfest(QString fest);
	QString name();
	void setname(QString name);
	QTime starts();
	void setstarts(QTime starts);
	quint8 lasts();
	void setlasts(quint8& lasts);
	QTime ends();
	quint8 scene();
	void setscene(quint8& scene);

signals:
	void uidChanged();
	void festChanged();
	void nameChanged();
	void startsChanged();
	void lastsChanged();
	void sceneChanged();
public slots:

};

#endif // BANDLISTITEM_H
