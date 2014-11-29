#include "bandlistitem.h"

BandListItem::BandListItem(QObject *parent) :
    QObject(parent){
    _uid = new QString();
    _fest = new QString();
    _starts = 0;
    _lasts = 0;
    _scene = 0;
}

BandListItem::BandListItem(QString uid, QString fest, quint64& starts, quint8& lasts, quint8& scene, QObject* parent) :
    QObject(parent) {
    _uid = uid;
    _fest = fest;
    _starts = starts;
    _lasts = lasts;
    _scene = scene;
}

BandListItem::~BandListItem(){
    delete _uid;
    delete _fest;
}

QString BandListItem::uid() {
    return _uid;
}

void BandListItem::setuid(QString uid) {
    if (uid != _uid){
        _uid = uid;
        emit uidChanged();
    }
}

QString BandListItem::fest() {
    return _fest;

}

void BandListItem::setfest(QString fest) {
    if (fest != _fest){
        _fest = fest;
        emit festChanged();
    }
}

quint64 BandListItem::starts() {
    return _starts;
}

void BandListItem::setstarts(quint64& starts) {
    if (starts != _starts){
        _starts = starts;
        emit startsChanged();
    }
}

quint8 BandListItem::lasts() {
    return _lasts;
}

void BandListItem::setlasts(quint8& lasts) {
    if (lasts != _lasts){
        _lasts = lasts;
        emit lastsChanged();
    }
}

quint8 BandListItem::scene() {
    return _scene;
}

void BandListItem::setscene(quint8& scene) {
    if (scene != _scene){
        _scene = scene;
        emit sceneChanged();
    }
}
