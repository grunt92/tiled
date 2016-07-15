#ifndef DUNGEON_H
#define DUNGEON_H

#include <QMap>

namespace tiled{

class ImageLayer;
class mapobject;
class layer;
class ObjectGroup;
class Tile;
class TileLayer;
class Tileset;

}

namespace Internal{
	
	class AbstractTool;
	class MapDocument;
	class MapObjectItem;
	class MapScene;
	class ObjectGroupItem;
	class ObjectSelectionItem;
}

class dungeon{
	
	public:
	dungeon();
	~dungeon();
	void generateDungeon();
	
};
#endif 
