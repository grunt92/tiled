#ifndef DUNGEONPLUGIN_H
#define DUNGEONPLUGIN_H

#include "dungeon_global.h"

#include "mapformat.h"

#include <QObject>
#include <QMap>

namespace Dungeon {

class DUNGEONSHARED_EXPORT DungeonPlugin : public Tiled::MapFormat
{
    Q_OBJECT
    Q_INTERFACES(Tiled::MapFormat)
    Q_PLUGIN_METADATA(IID "org.mapeditor.MapFormat" FILE "plugin.json")

public:
    DungeonPlugin();
};

} // namespace Dungeon

#endif // DUNGEONPLUGIN_H