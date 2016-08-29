#ifndef DUNGEON_H
#define DUNGEON_H

#include <QMap>
#include <QString>
#include "terraindock.h"
#include "mapdocument.h"
#include "mainwindow.h"
#include "terrainbrush.h"
#include "tileset.h"
#include "terrain.h"

namespace Tiled{
class Terrain;

namespace Internal{
	

class dungeon{

	public:

    struct Rect
    {
        int x, y;
        int width, height;
    };
    enum Tile
    {
        Empty		= 0,
        Floor		= 1,
        Wall		= 2,
    };

    enum Direction
    {
        Up,
        Down,
        Left,
        Right,
        DirectionCount
    };
    dungeon (int width, int height, MainWindow* mw, Terrain* floor, Terrain* wall, bool buildCave = false, bool corridors = false, int probability = 100, bool corridorsAreRooms = false, bool fill=false);
    void generate(int maxFeatures);
    void buildDungeon();


    private:
    int getTile(int x, int y) const;
    void setTile(int x, int y, int tile);
    void transformToCave();
    bool createRoom();
    bool createRoom(int x, int y, Direction dir);
    bool makeRoom(int x, int y, Direction dir, bool firstRoom = false);
    bool makeCorridor(int x, int y, Direction dir, bool firstRoom = false);
    bool placeRoom(const Rect& rect, int tile);
    bool placeObject(int tile);
    bool buildCave, corridors, corridorsAreRooms, fill;
    int width, height, probability;
    std::vector<int> tiles;
    std::vector<Rect> rooms;
    std::vector<Rect> exits;
    MainWindow* mw;
    TerrainBrush* tb;
    Terrain* floor, *wall;

};
}
}
#endif 
