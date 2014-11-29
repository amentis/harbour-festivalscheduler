#ifndef BANDLISTITEM_H
#define BANDLISTITEM_H

#include <QObject>
#include <QString>

class BandListItem : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString uid READ uid WRITE setuid NOTIFY uidChanged)
    Q_PROPERTY(QString fest READ fest WRITE setfest NOTIFY festChanged)
    Q_PROPERTY(quint64 starts READ starts WRITE setstarts NOTIFY startsChanged)
    Q_PROPERTY(quint8 lasts READ lasts WRITE setlasts NOTIFY lastsChanged)
    Q_PROPERTY(quint8 scene READ scene WRITE setscene NOTIFY sceneChanged)

private:
    QString* _uid;
    QString* _fest;
    quint64 _starts;
    quint8 _lasts;
    quint8 _scene;
public:
    explicit BandListItem(QObject *parent = 0);
    BandListItem(QString uid, QString fest, quint64& starts, quint8& lasts, quint8& scene, QObject *parent = 0);
    ~BandListItem();
    QString uid();
    void setuid(QString uid);
    QString fest();
    void setfest(QString fest);
    quint64 starts();
    void setstarts(quint64& starts);
    quint8 lasts();
    void setlasts(quint8& lasts);
    quint8 scene();
    void setscene(quint8& scene);

signals:
    uidChanged();
    festChanged();
    startsChanged();
    lastsChanged();
    sceneChanged();
public slots:

};

#endif // BANDLISTITEM_H
