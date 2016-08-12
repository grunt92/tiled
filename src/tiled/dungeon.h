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
    dungeon(MainWindow *mw = nullptr, TerrainDock *td = nullptr, int numberOfRooms = 0);
    ~dungeon();
    void generateDungeon(int numberOfRooms);
    void generateRooms(int numberOfRooms);
    void generatePath();

    private:
    int width, height;
    QString floor, wall;


};
}
}
#endif 
