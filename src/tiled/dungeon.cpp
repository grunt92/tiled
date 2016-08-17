#include "dungeon.h"
#include <random>
#include <vector>
#include <iostream>
#include "terrainbrush.h"
#include "mainwindow.h"
#include "terrain.h"
#include "eraser.h"
using namespace  Tiled::Internal;
namespace Tiled
{
    std::random_device rd;
    std::mt19937 mt(rd());

    int randomInt(int exclusiveMax)
    {
        std::uniform_int_distribution<> dist(0, exclusiveMax - 1);
        return dist(mt);
    }

    int randomInt(int min, int max) // inclusive min/max
    {
        std::uniform_int_distribution<> dist(0, max - min);
        return dist(mt) + min;
    }

    bool randomBool(double probability = 0.5)
    {
        std::bernoulli_distribution dist(probability);
        return dist(mt);
    }
}

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
        Counter
    };
    dungeon::dungeon(int width, int height, MainWindow* mw, Tiled::Terrain* floor, Tiled::Terrain* wall)
        : _width(width)
        , _height(height)
        , mw(mw)
        , _tiles(width * height, Empty)
        , _rooms()
        , _exits()
        , floor(floor)
        , wall(wall)
    {
        tb = mw->getBrush();

    }

    void dungeon::generate(int maxFeatures)
    {
        // place the first room in the center
        if (!makeRoom(_width / 2, _height / 2, static_cast<Direction>(randomInt(4), true)))
        {
            std::cout << "Unable to place the first room.\n";
            return;
        }

        // we already placed 1 feature (the first room)
        for (int i = 1; i < maxFeatures; ++i)
        {
            if (!createFeature())
            {
                std::cout << "Unable to place more features (placed " << i << ").\n";
                break;
            }
        }

        for (int& tile : _tiles)
        {
            if (tile == Empty)
                tile = 0;
            else if (tile == Floor)
                tile = 1;
        }
    }


    int dungeon::getTile(int x, int y) const
    {
        if (x < 0 || y < 0 || x >= _width || y >= _height)
            return Empty;

        return _tiles[x + y * _width];
    }

    void dungeon::setTile(int x, int y, int tile)
    {
        _tiles[x + y * _width] = tile;
    }

    bool dungeon::createFeature()
    {
        for (int i = 0; i < 1000; ++i)
        {
            if (_exits.empty())
                break;

            // choose a random side of a random room or corridor
            int r = randomInt(_exits.size());
            int x = randomInt(_exits[r].x, _exits[r].x + _exits[r].width - 1);
            int y = randomInt(_exits[r].y, _exits[r].y + _exits[r].height - 1);

            // north, south, west, east
            for (int j = 0; j < DirectionCount; ++j)
            {
                if (createFeature(x, y, static_cast<Direction>(j)))
                {
                    _exits.erase(_exits.begin() + r);
                    return true;
                }
            }
        }

        return false;
    }

    bool dungeon::createFeature(int x, int y, Direction dir)
    {
        static const int roomChance = 50; // corridorChance = 100 - roomChance

        int dx = 0;
        int dy = 0;

        if (dir == Up)
            dy = 1;
        else if (dir == Down)
            dy = -1;
        else if (dir == Left)
            dx = 1;
        else if (dir == Right)
            dx = -1;

        if (getTile(x + dx, y + dy) != Floor && getTile(x + dx, y + dy) != Floor)
            return false;

        if (randomInt(100) < roomChance)
        {
            if (makeRoom(x, y, dir))
            {
                setTile(x, y, Floor);

                return true;
            }
        }

        return false;
    }

    bool dungeon::makeRoom(int x, int y, Direction dir, bool firstRoom)
    {
        static const int minRoomSize = 3;
        static const int maxRoomSize = 6;

        Rect room;
        room.width = randomInt(minRoomSize, maxRoomSize);
        room.height = randomInt(minRoomSize, maxRoomSize);

        if (dir == Up)
        {
            room.x = x - room.width / 2;
            room.y = y - room.height;
        }

        else if (dir == Down)
        {
            room.x = x - room.width / 2;
            room.y = y + 1;
        }

        else if (dir == Left)
        {
            room.x = x - room.width;
            room.y = y - room.height / 2;
        }

        else if (dir == Right)
        {
            room.x = x + 1;
            room.y = y - room.height / 2;
        }

        if (placeRect(room, Floor))
        {
            _rooms.emplace_back(room);

            if (dir != Down || firstRoom) // north side
                _exits.emplace_back(Rect{ room.x, room.y - 1, room.width, 1 });
            if (dir != Up || firstRoom) // south side
                _exits.emplace_back(Rect{ room.x, room.y + room.height, room.width, 1 });
            if (dir != Right || firstRoom) // west side
                _exits.emplace_back(Rect{ room.x - 1, room.y, 1, room.height });
            if (dir != Left || firstRoom) // east side
                _exits.emplace_back(Rect{ room.x + room.width, room.y, 1, room.height });

            return true;
        }

        return false;
    }



    bool dungeon::placeRect(const Rect& rect, int tile)
    {
        if (rect.x < 1 || rect.y < 1 || rect.x + rect.width > _width - 1 || rect.y + rect.height > _height - 1)
            return false;

        for (int y = rect.y; y < rect.y + rect.height; ++y)
            for (int x = rect.x; x < rect.x + rect.width; ++x)
            {
                if (getTile(x, y) != Empty)
                    return false; // the area already used
            }

        for (int y = rect.y - 1; y < rect.y + rect.height + 1; ++y)
            for (int x = rect.x - 1; x < rect.x + rect.width + 1; ++x)
            {
                if (x == rect.x - 1 || y == rect.y - 1 || x == rect.x + rect.width || y == rect.y + rect.height)
                    setTile(x, y, Wall);
                else
                    setTile(x, y, tile);
            }

        return true;
    }

    void dungeon::print()
    {
        for (float y = 0; y < _height; ++y){
            for(float x = 0; x <_width; ++x){
                if (getTile(x,y)==1)
                tb->drawByCoordinate(x,y,floor);
                else if(getTile(x,y)==2)
                tb->drawByCoordinate(x,y,wall);
            }
        }
    }





