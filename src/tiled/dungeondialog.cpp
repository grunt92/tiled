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

using namespace Tiled::Internal;

DungeonDialog::DungeonDialog(QWidget *parent, MainWindow *mw, TerrainDock *td): QDialog(parent),mainWindow(mw),  mUi(new Ui::DungeonDialog)
{
    mUi->setupUi(this);
    //setupUi(this);
    mainWindow =mw;
    terrainDock = td;
    terrainView = td->getTerrainView();
    mapDocument = td->getMapDocument();
    for(SharedTileset tileset: mapDocument->map()->getTileSets()){
        for(Terrain *terrain: tileset->getTerrains()){
            //mUi->comboBox->addItem(terrain.name());
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
    mUi->OK->setEnabled(false);
    checkOk();
}

void DungeonDialog::generateDungeon(){
    Terrain* floor =  terrains.at(mUi->floorBox->currentIndex());
    Terrain* wall =  terrains.at(mUi->wallBox->currentIndex());
    Map* map = mapDocument->map();
    dungeon d(map->width(),map->height(),mainWindow, floor, wall);
    d.generate(mUi->spinBox->value());
    d.print();
}

void DungeonDialog::cancel(){
    this->close();
}

void DungeonDialog::checkOk(){
    QString eins = mUi->floorBox->currentText();
    QString zwei = mUi->wallBox->currentText();
    int anzahl = mUi->spinBox->value();
    if(eins.isEmpty()||zwei.isEmpty()||anzahl<=0){
        mUi->OK->setEnabled(false);
    }else{
        mUi->OK->setEnabled(true);
    }
}
