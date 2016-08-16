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
    dungeon (int width, int height, MainWindow* mw, Terrain* floor, Terrain* wall);
    void generate(int maxFeatures);
    void print();

    private:
    int getTile(int x, int y) const;
    void setTile(int x, int y, int tile);
    bool createFeature();
    bool createFeature(int x, int y, Direction dir);
    bool makeRoom(int x, int y, Direction dir, bool firstRoom = false);
    bool makeCorridor(int x, int y, Direction dir);
    bool placeRect(const Rect& rect, int tile);
    bool placeObject(int tile);
    int _width, _height;
    std::vector<int> _tiles;
    std::vector<Rect> _rooms; // rooms for place stairs or monsters
    std::vector<Rect> _exits; // 4 sides of rooms or corridors
    MainWindow* mw;
    TerrainBrush* tb;
    Terrain* floor, *wall;

};
}
}
#endif 
