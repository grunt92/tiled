#include <QEvent>
#include <QBoxLayout>
#include <QPushButton>
#include <QSortFilterProxyModel>
#include <QTreeView>
#include "tileset.h"
#include "terrain.h"
#include "dungeondialog.h"

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
            QString s = terrain->name();
            mUi->floorBox->addItem(s);
            mUi->wallBox->addItem(s);

        }
    }
    connect(mUi->OK,SIGNAL(clicked(bool)),SLOT(generateDungeon()));
    connect(mUi->Cancel,SIGNAL(clicked(bool)),SLOT(cancel()));
    connect(mUi->floorBox,SIGNAL(currentTextChanged(QString)),SLOT(checkOK()));
    connect(mUi->wallBox,SIGNAL(currentTextChanged(QString)),SLOT(checkOk()));
    mUi->OK->setEnabled(false);
}

void DungeonDialog::generateDungeon(){

}

void DungeonDialog::cancel(){
    this->close();
}

void DungeonDialog::checkOk(){
    QString eins = mUi->floorBox->currentText();
    QString zwei = mUi->wallBox->currentText();
    if(eins.isEmpty()||zwei.isEmpty()){
        mUi->OK->setEnabled(false);
    }else{
        mUi->OK->setEnabled(true);
    }
}
