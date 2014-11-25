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

CONFIG += sailfishapp

SOURCES += src/harbour-festivalscheduler.cpp

OTHER_FILES += qml/harbour-festivalscheduler.qml \
    qml/cover/CoverPage.qml \
    qml/pages/FirstPage.qml \
    rpm/harbour-festivalscheduler.changes.in \
    rpm/harbour-festivalscheduler.spec \
    rpm/harbour-festivalscheduler.yaml \
    harbour-festivalscheduler.desktop

