#include "festivallistitem.h"

FestivalListItem::FestivalListItem(QObject *parent) :
	QObject(parent){
	_uid = new QString();
	_name = new QString();
	_day = 0;
	_numberOfDays = 1;
	_place = new QString();
	_numberOfScenes = 1;
}

FestivalListItem::FestivalListItem(QString uid, QString name, quint64& day, quint8& numberOfDays, QString place, quint64& numberOfScenes, QObject *parent) :
	QObject(parent){
	_uid = uid;
	_name = name;
	_day = day;
	_numberOfDays = numberOfDays;
	_place = place;
	_numberOfScenes = numberOfScenes;
}

FestivalListItem::~FestivalListItem(){
	delete _uid;
	delete _name;
	delete _place;
}

QString FestivalListItem::uid(){
	return _uid;
}

void FestivalListItem::setuid(QString newUid){
	if (newUid != _uid){
		_uid = newUid;
		emit uidChanged();
	}
}

QString FestivalListItem::name(){
	return _name;
}

void FestivalListItem::setname(QString newName){
	if (newName != _name){
		_name = newName;
		emit nameChanged();
	}
}

QDate FestivalListItem::day(){
	return _day;
}

void FestivalListItem::setday(quint64 &newDay){
	if (newDay != _day){
		_day = newDay;
		emit dayChanged();
	}
}

quint8 FestivalListItem::numberOfDays(){
	return _numberOfDays;
}

void FestivalListItem::setnumberOfDays(quint8 &newNumberOfDays){
	if (newNumberOfDays != _numberOfDays){
		_numberOfDays = newNumberOfDays;
		emit numberOfDaysChanged();
	}
}

QString FestivalListItem::place(){
	return _place;
}

void FestivalListItem::setplace(QString newPlace){
	if (newPlace != _place){
		_place = newPlace;
		emit placeChanged();
	}
}

quint8 FestivalListItem::numberOfScenes(){
	return numberOfScenes();
}

void FestivalListItem::setnumberOfScenes(quint8 &newNumberOfScenes){
	if (newNumberOfScenes != _numberOfScenes){
		_numberOfScenes = newNumberOfScenes;
		emit numberOfScenesChanged();
	}
}
