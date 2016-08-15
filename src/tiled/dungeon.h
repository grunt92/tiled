#ifndef DUNGEON_H
#define DUNGEON_H

#include <QMap>
#include <QString>
#include "terraindock.h"
#include "mapdocument.h"
#include "mainwindow.h"

namespace Tiled{

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
        Empty		= ' ',
        Floor		= '.',
        Wall		= '#',
    };

    enum Direction
    {
        Up,
        Down,
        Left,
        Right,
        DirectionCount
    };
    dungeon (int width, int height);
    void generate(int maxFeatures);
    void print();

    private:
    char getTile(int x, int y) const;
    void setTile(int x, int y, char tile);
    bool createFeature();
    bool createFeature(int x, int y, Direction dir);
    bool makeRoom(int x, int y, Direction dir, bool firstRoom = false);
    bool makeCorridor(int x, int y, Direction dir);
    bool placeRect(const Rect& rect, char tile);
    bool placeObject(char tile);
    int _width, _height;
    std::vector<char> _tiles;
    std::vector<Rect> _rooms; // rooms for place stairs or monsters
    std::vector<Rect> _exits; // 4 sides of rooms or corridors

};
}
}
#endif 
