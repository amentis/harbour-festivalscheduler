#include "bandlistitem.h"

BandListItem::BandListItem(QObject *parent) :
	QObject(parent){
	_uid = new QString();
	_fest = new QString();
	_name = new QString();
	_starts = 0;
	_lasts = 0;
	_scene = 0;
}

BandListItem::BandListItem(QString uid, QString fest, QString name, QTime* starts, quint8& lasts, quint8& scene, QObject* parent) :
	QObject(parent) {
	_uid = uid;
	_fest = fest;
	_name = name;
	_starts = starts;
	_lasts = lasts;
	_scene = scene;
}

BandListItem::~BandListItem(){
	delete _uid;
	delete _fest;
	delete _name;
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

QString BandListItem::name() {
	return _name;
}

void BandListItem::setname(QString name) {
	_name = name;
}

QTime BandListItem::starts() {
	return _starts;
}

void BandListItem::setstarts(QTime starts) {
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

QTime BandListItem::ends() {
	QTime tmp = _starts;
	tmp.addMSecs(_lasts);
	return tmp;
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
