!contains(PROFILES,$$_FILE_){
PROFILES+=$$_FILE_

INCLUDEPATH += $$PWD
INCLUDEPATH += $$PWD/../SoftSynths/SoftSynthsWidgets/

SOURCES += $$PWD/qsynthswitch.cpp

HEADERS  += $$PWD/qsynthswitch.h

RESOURCES += $$PWD/synthswitchresources.qrc
}
