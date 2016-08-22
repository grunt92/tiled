#include "dungeon.h"
#include <random>
#include <vector>
#include "terrainbrush.h"
#include "mainwindow.h"
#include "terrain.h"
#include <iostream>
using namespace  Tiled::Internal;
namespace
{
//Die folgenden Funktionen werden benötigt um zufällige Zahlen bzw. einen zufälligen Boolean zu erzeugen.
    std::random_device rd;
    std::mt19937 mt(rd());

    int randomInt(int exclusiveMax)
    {
        std::uniform_int_distribution<> dist(0, exclusiveMax - 1);
        return dist(mt);
    }

    int randomInt(int min, int max)
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

//Praktisch gesehen nichts weiter als ein Rechteck mit Position und Größe
struct Room
{
    int x, y;
    int width, height;
};

//Eine Kurze Auflistung der Bausteine, der Einfachheit halber auf "Nicht", "Boden" und "Wand" beschränkt
 enum Tile
    {
        Empty		= 0,
        Floor		= 1,
        Wall		= 2,
    };
//Auflistung zur Navigation innerhalb des Dungeons
    enum Direction
    {
        Up,
        Down,
        Left,
        Right,
        Counter
    };
//Construktor der Klasse
    dungeon::dungeon(int width, int height, MainWindow* mw, Tiled::Terrain* floor, Tiled::Terrain* wall, bool buildCave, bool corridors, int probability, bool corridorsAreRooms)
        : width(width)
        , height(height)
        , mw(mw)
        , tiles(width * height, Empty)
        , exits()
        , floor(floor)
        , wall(wall)
        , buildCave(buildCave)
        , corridors(corridors)
        , probability(probability)
        , corridorsAreRooms(corridorsAreRooms)

    {
        tb = mw->getBrush();

    }
//Eigentliche Generierung des Dungeons, zuerst wird ein Raum angelegt, sollte dies nicht möglich sein wird das Programm abgebrochen,
//anschließend werden so viele Räume erstellt wie vom Nutzer angegeben, oder bis kein Platz mehr existiert um neue Räume anzulegen.
//Zum Schluss wird über die Tiles iterriert um diesen den entsprechenden Wert zuzuweisen.
    void dungeon::generate(int maxRooms)
    {
        if (corridors)
        {
        if (randomInt(100) < probability)
        {
            if (!makeRoom(width / 2, height / 2, static_cast<Direction>(randomInt(4), true)))
            {
                return;
            }
        }
        else
        {
            if (!makeCorridor(width / 2, height / 2, static_cast<Direction>(randomInt(4), true)))
            {
                return;
            }
         }
        }
        else{
        if (!makeRoom(width / 2, height / 2, static_cast<Direction>(randomInt(4), true)))
        {
            return;
        }
        }
       while(rooms.size()< maxRooms)
        {
            if (!createRoom())
            {
                break;
            }
        }

        for (int& tile : tiles)
        {
            if (tile == Empty)
                tile = 0;
            else if (tile == Floor)
                tile = 1;
        }
    }

//Getter-Funktion für die einzelnen Tiles
    int dungeon::getTile(int x, int y) const
    {
        if (x < 0 || y < 0 || x >= width || y >= height)
            return Empty;

        return tiles[x + y * width];
    }
//Setter-Funktion für die einzelnen Tiles
    void dungeon::setTile(int x, int y, int tile)
    {
        if(x>=0&&x<=width&&y>=0&&y<=height)
        tiles[x + y * width] = tile;
    }

//Iterriert über eine Schleife, hierbei könnte es sich auch um eine Endlosschleife handeln, es wurde eine For-Schleife benutzt
//Um garantieren zu können, dass das Programm auch anhält.
//Zunächst wird überprüft, ob es noch Stellen gibt, an denen ein weiterer Raum an das Dungeon angefügt werden kann, anschließend wird
//eine dieser Stellen zufällig ausgewählt, anschließend wird an der entsprechenden Stelle zufallswerte gewählt, die in der anschließenden
//Schleife dazu dienen neue Räume zu erschaffen, nachdem der Ausgang genutzt wurde wird er aus der Liste der verbliebenen Ausgänge gelöscht.
    bool dungeon::createRoom()
    {
        for (int i = 0; i < 999; ++i)
        {
            if (exits.empty())
                return false;
            int r = randomInt(exits.size());
            int x = randomInt(exits[r].x, exits[r].x + exits[r].width - 1);
            int y = randomInt(exits[r].y, exits[r].y + exits[r].height - 1);
            for (int j = 0; j < Counter; ++j)
            {
                if (createRoom(x, y, static_cast<Direction>(j)))
                {
                    exits.erase(exits.begin() + r);
                    return true;
                }
            }
        }

        return false;
    }

//Die Funktion bekommt eine Position und eine Richtung angegeben, diese werden mit Ausnahme des ersten Raums von der Funktion createRoom() übergeben.
//Durch die übergebene Richtung wird ermittelt, ob sich an der anzubindenden Stelle auch Boden befindet, befindet sich an besagter Stelle eine Wand
//oder nichts, wird ein false zurückgegeben, anschließend wird optional bestimmt, ob der folgende Raum ein Raum oder nur ein Korridor ist, anschließend
//wird die entsprechende Funktion aufgerufen und das Verbindungsstück zwischen den beiden "Räumen" durch ein Bodenstück ersetzt.
    bool dungeon::createRoom(int x, int y, Direction dir)
    {

        int dx = 0;
        int dy = 0;
        switch (dir){
        case Up:
            dy = 1;
            break;
        case Down:
            dy = -1;
            break;
        case Left:
            dx = 1;
            break;
        case Right:
            dx = -1;
            break;
            }
        if (getTile(x + dx, y + dy) != Floor)
            return false;
        if(corridors){
        if (randomInt(100) < probability)
        {
            if (makeRoom(x, y, dir))
            {
                setTile(x, y, Floor);

                return true;
            }
        }
        else{
            if (makeCorridor(x, y, dir))
            {
                setTile(x, y, Floor);

                return true;
            }
        }}
        else{
            if (makeRoom(x, y, dir))
            {
                setTile(x, y, Floor);

                return true;
            }
        }
        return false;
    }

//Zunächst wird ein Rechteck(Raum) erschaffen, dessen Maße zufällig zwischen der maximalen und minimalen Größe liegen, anschließend wird abgefragt,
//Welche Richtung als Parameter übergeben wurde, um anhand dessen den Ursprungspunkt für den Raum zu bestimmen. Nachdem der Raum mit placeRoom platziert wurde,
//Werden anschließend die neu entstandenen freien Ausgänge dem Vektor hinzugefügt
    bool dungeon::makeRoom(int x, int y, Direction dir, bool firstRoom){
        static const int minRoomSize = 3;
        static const int maxRoomSize = 6;

        Rect room;
        room.width = randomInt(minRoomSize, maxRoomSize);
        room.height = randomInt(minRoomSize, maxRoomSize);

        switch (dir){
        case (Up):
            room.x = x - room.width / 2;
            room.y = y - room.height;
            break;

        case (Down):
            room.x = x - room.width / 2;
            room.y = y + 1;
            break;

        case (Left):
            room.x = x - room.width;
            room.y = y - room.height / 2;
            break;


        case(Right):
            room.x = x + 1;
            room.y = y - room.height / 2;
            break;
        }
        if (placeRoom(room, Floor))
        {
            exits.emplace_back(room);

            if (dir != Down || firstRoom)
                exits.emplace_back(Rect{ room.x, room.y - 1, room.width, 1 });
            if (dir != Up || firstRoom)
                exits.emplace_back(Rect{ room.x, room.y + room.height, room.width, 1 });
            if (dir != Right || firstRoom)
                exits.emplace_back(Rect{ room.x - 1, room.y, 1, room.height });
            if (dir != Left || firstRoom)
                exits.emplace_back(Rect{ room.x + room.width, room.y, 1, room.height });

            rooms.emplace_back(room);
            return true;
        }

        return false;
    }

//Das gleiche Prinzip wie bei der Funktion makeRoom, nur dass zusätzlich durch die randomBool-Methode entschieden wird, ob der Korridor vertikal oder horizontal verlaufen soll.
    bool dungeon::makeCorridor(int x, int y, Direction dir, bool firstRoom)
        {
            static const int minCorridorLength = 3;
            static const int maxCorridorLength = 6;

            Rect corridor;
            corridor.x = x;
            corridor.y = y;

            if (randomBool())
            {
                corridor.width = randomInt(minCorridorLength, maxCorridorLength);
                corridor.height = 1;
                switch(dir){
                case Up:
                    corridor.y = y - 1;
                    if (randomBool())
                        corridor.x = x - corridor.width + 1;
                    break;

                case Down:
                    corridor.y = y + 1;

                    if (randomBool())
                        corridor.x = x - corridor.width + 1;
                    break;

                case Left:
                    corridor.x = x - corridor.width;
                    break;

                case Right:
                    corridor.x = x + 1;
                    break;
                }
            }

            else
            {
                corridor.width = 1;
                corridor.height = randomInt(minCorridorLength, maxCorridorLength);
                switch (dir){
                case Up:
                    corridor.y = y - corridor.height;
                    break;

                case Down:
                    corridor.y = y + 1;
                    break;

                case Left:
                    corridor.x = x - 1;
                    if (randomBool())
                        corridor.y = y - corridor.height + 1;
                    break;

                case Right:
                    corridor.x = x + 1;
                    if (randomBool())
                        corridor.y = y - corridor.height + 1;
                    break;
                }
            }
            if (placeRoom(corridor, Floor))
                    {
                        if (dir != Down && corridor.width != 1||firstRoom)
                            exits.emplace_back(Rect{ corridor.x, corridor.y - 1, corridor.width, 1 });
                        if (dir != Up && corridor.width != 1||firstRoom)
                            exits.emplace_back(Rect{ corridor.x, corridor.y + corridor.height, corridor.width, 1 });
                        if (dir != Right && corridor.height != 1||firstRoom)
                            exits.emplace_back(Rect{ corridor.x - 1, corridor.y, 1, corridor.height });
                        if (dir != Left && corridor.height != 1||firstRoom)
                            exits.emplace_back(Rect{ corridor.x + corridor.width, corridor.y, 1, corridor.height });
                        if(corridorsAreRooms)
                            rooms.emplace_back(corridor);
                        return true;
                    }

                    return false;
                }

//Zunächst wird überprüft, dass der Raum auch in den vorgegebenen Grenzen liegt anschließend wird über die einzelnen Reihen des Raumes iterriert,um sicher zu gehen, dass diese leer sind.
//Nun wird noch einmal über die Reihen iterriert, die und die Boden bzw. Wand-tiles entsprechend zugeordnet.
    bool dungeon::placeRoom(const Rect& rect, int tile)
    {
        if (rect.x < 1 || rect.y < 1 || rect.x + rect.width > width - 1 || rect.y + rect.height > height - 1)
            return false;

        for (int y = rect.y; y < rect.y + rect.height; ++y)
            for (int x = rect.x; x < rect.x + rect.width; ++x)
            {
                if (getTile(x, y) != Empty)
                    return false;
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




//Die Funktion fragt zunächst ab, welche Art von Dungeon gebaut werden soll, anschließend, werden über sämtliche Tiles des Layers iterriert.
//Da die Möglichkeit besteht dass sich auf dem Layer bereits Tiles befinden, werden Tiles die leer sind zur Sicherheit noch einmal mit 0 überschrieben.
    void dungeon::buildDungeon()
    {
        if(buildCave)
        transformToCave();
        for (float y = 0; y < height; ++y){
            for(float x = 0; x <width; ++x){
                tb->drawByCoordinate(x,y,nullptr);
                if (getTile(x,y)==1)
                tb->drawByCoordinate(x,y,floor);
                else if(getTile(x,y)==2)
                tb->drawByCoordinate(x,y,wall);
            }
        }
    }
//Die Funktion itteriert über alle Tiles des Layers, die Randtiles des Layers werden in Ruhe gelassen. Bei WandTiles die sich nicht am Rand des Layers befinden wird überprüft,
//ob es sich bei Ihnen um Tiles handelt, die das Dungeon abgrenzen, also ob eines ihrer Nachbartiles leer ist, ist dies nicht der Fall wird das Tile auf 1 also auf ein Bodentile umgesetzt.
    void dungeon::transformToCave(){
        for(float y = 0; y < height; ++y){
            for(float x = 0; x <width; ++x){
                if(getTile(x,y)==2){
                    }if(y>0&&y<(height-1)||x>0&&x<(width-1)){
                        bool isOuterWall = false;
                        if(getTile(x-1,y)==0)
                            isOuterWall = true;
                        else if(getTile(x-1,y-1)==0)
                            isOuterWall = true;
                        else if(getTile(x,y-1)==0)
                             isOuterWall = true;
                        else if(getTile(x+1,y-1)==0)
                              isOuterWall = true;
                        else if(getTile(x+1,y)==0)
                             isOuterWall = true;
                        else if(getTile(x+1,y+1)==0)
                             isOuterWall = true;
                        else if(getTile(x,y+1)==0)
                             isOuterWall = true;
                        else if(getTile(x-1,y+1)==0)
                             isOuterWall = true;

                        if(!isOuterWall){
                             setTile(x,y,Floor);
                        }
                    }
                }
            }
        }





