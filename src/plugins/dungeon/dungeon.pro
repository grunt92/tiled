include(../plugin.pri)

DEFINES += DUNGEON_LIBRARY

HEADERS += \
    dungeon_global.h \
    dungeonplugin.h

SOURCES += \
    dungeonplugin.cpp

OTHER_FILES = plugin.json