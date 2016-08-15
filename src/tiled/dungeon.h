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
    dungeon (int width, int height);
    ~dungeon();
    int getWidth(){return width;}
    int getHeight(){return height;}
    int get(int x, int y);
    void set(int x, int y, int value);

    private:
    int width, height;
    std::vector<int> tiles;

};
}
}
#endif 
