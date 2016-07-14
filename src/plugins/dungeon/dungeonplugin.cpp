#include "dungeonplugin.h"

#include "gidmapper.h"
#include "map.h"
#include "mapobject.h"
#include "tile.h"
#include "tilelayer.h"
#include "tileset.h"
#include "objectgroup.h"

#include <QSaveFile>
#include <QFileInfo>
#include <QDir>
#include <QSettings>
#include <QStringList>
#include <QTextStream>

using namespace Tiled;
using namespace Dungeon;

DungeonPlugin::DungeonPlugin()
{
}


