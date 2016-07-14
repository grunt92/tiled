#ifndef DUNGEON_GLOBAL_H
#define DUNGEON_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(DUNGEON_LIBRARY)
#  define DUNGEONSHARED_EXPORT Q_DECL_EXPORT
#else
#  define DUNGEONSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // DUNGEON_GLOBAL_H
