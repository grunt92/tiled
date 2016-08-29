#include <QEvent>
#include <QBoxLayout>
#include <QPushButton>
#include <QSortFilterProxyModel>
#include <QTreeView>
#include "tileset.h"
#include "terrain.h"
#include "dungeondialog.h"
#include "dungeon.h"
#include "map.h"
#include <iostream>
#include <QCoreApplication>
#include <QDesktopServices>
#include <random>


    std::random_device rd;
    std::mt19937 mt(rd());

    int randomInt(int exclusiveMax)
    {
        std::uniform_int_distribution<> dist(0, exclusiveMax - 1);
        return dist(mt);
    }


using namespace Tiled::Internal;

DungeonDialog::DungeonDialog(QWidget *parent, MainWindow *mw, TerrainDock *td): QDialog(parent),mainWindow(mw),  mUi(new Ui::DungeonDialog)
{
    mUi->setupUi(this);
    mainWindow =mw;
    terrainDock = td;
    terrainView = td->getTerrainView();
    mapDocument = td->getMapDocument();
    for(SharedTileset tileset: mapDocument->map()->getTileSets()){
        for(Terrain *terrain: tileset->getTerrains()){
            terrains.emplace_back(terrain);
        }
    }
    for(int i=0; i< terrains.size(); ++i){
        Terrain* t = terrains.at(i);
        QString name = t->name();
        mUi->floorBox->addItem(name);
        mUi->wallBox->addItem(name);

    }
    connect(mUi->OK,SIGNAL(clicked(bool)),SLOT(generateDungeon()));
    connect(mUi->Cancel,SIGNAL(clicked(bool)),SLOT(cancel()));
    connect(mUi->floorBox,SIGNAL(currentTextChanged(QString)),SLOT(checkOK()));
    connect(mUi->wallBox,SIGNAL(currentTextChanged(QString)),SLOT(checkOk()));
    connect(mUi->spinBox,SIGNAL(valueChanged(int)),SLOT(checkOk()));
    connect(mUi->checkBox_2,SIGNAL(clicked(bool)),SLOT(checkProbability()));
     connect(mUi->checkBox_2,SIGNAL(clicked(bool)),SLOT(checkOk()));
    connect(mUi->spinBox_2,SIGNAL(valueChanged(int)),SLOT(checkOk()));
    mUi->OK->setEnabled(false);
    mUi->spinBox_2->setEnabled(false);
    mUi->checkBox_3->setEnabled(false);
    int num = randomInt(99);
    mUi->spinBox_3->setValue(num);
    checkOk();
}

void DungeonDialog::generateDungeon(){
    Terrain* floor =  terrains.at(mUi->floorBox->currentIndex());
    Terrain* wall =  terrains.at(mUi->wallBox->currentIndex());
    Map* map = mapDocument->map();
    bool buildcave = mUi->checkBox->isChecked();
    bool corridors = mUi->checkBox_2->isChecked();
    bool cAR = mUi->checkBox_3->isChecked();
    bool fill = mUi->checkBox_4->isChecked();
    int number = mUi->spinBox_3->value();
    if(corridors){
        dungeon d(map->width(),map->height(),mainWindow, floor, wall, buildcave, corridors,mUi->spinBox_2->value(),cAR,fill,number);
        d.generate(mUi->spinBox->value());
        d.buildDungeon();
    }else{
        dungeon d(map->width(),map->height(),mainWindow, floor, wall, buildcave, corridors,100,cAR, fill,number);
        d.generate(mUi->spinBox->value());
        d.buildDungeon();
    }

}

void DungeonDialog::cancel(){
    this->close();
}

void DungeonDialog::checkOk(){
    QString one = mUi->floorBox->currentText();
    QString two = mUi->wallBox->currentText();
    int number = mUi->spinBox->value();
    if(one.isEmpty()||two.isEmpty()||number<=0){
        mUi->OK->setEnabled(false);
    }else{
        mUi->OK->setEnabled(true);
    }
}

void DungeonDialog::checkProbability(){
    bool corridors = mUi->checkBox_2->isChecked();
    if(corridors){
       mUi->spinBox_2->setEnabled(true);
       mUi->checkBox_3->setEnabled(true);
    }else{
       mUi->spinBox_2->setEnabled(false);
       mUi->checkBox_3->setEnabled(false);
    }
}
