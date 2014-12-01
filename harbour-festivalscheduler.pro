# NOTICE:
#
# Application name defined in TARGET has a corresponding QML filename.
# If name defined in TARGET is changed, the following needs to be done
# to match new name:
#   - corresponding QML filename must be changed
#   - desktop icon filename must be changed
#   - desktop filename must be changed
#   - icon definition filename in desktop file must be changed
#   - translation filenames have to be changed

# The name of your application
TARGET = harbour-festivalscheduler

CONFIG += sailfishapp sql

SOURCES += src/harbour-festivalscheduler.cpp \
    src/festivallistitem.cpp \
    src/bandlistitem.cpp \
    src/dbconnect.cpp

OTHER_FILES += qml/harbour-festivalscheduler.qml \
    qml/cover/CoverPage.qml \
    rpm/harbour-festivalscheduler.changes.in \
    rpm/harbour-festivalscheduler.spec \
    rpm/harbour-festivalscheduler.yaml \
    harbour-festivalscheduler.desktop \
    qml/pages/Home.qml \
    qml/pages/SelectFest.qml \
    qml/pages/EditFest.qml \
    qml/pages/AddFest.qml \
    qml/pages/AddBand.qml

HEADERS += \
    src/festivallistitem.h \
    src/bandlistitem.h \
    src/dbconnect.h

QT += sql
