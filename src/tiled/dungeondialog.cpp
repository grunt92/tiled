#include <QEvent>
#include <QBoxLayout>
#include <QPushButton>
#include <QSortFilterProxyModel>
#include <QTreeView>

#include "dungeondialog.h"

#include <QCoreApplication>
#include <QDesktopServices>

using namespace Tiled::Internal;

DungeonDialog::DungeonDialog(QWidget *parent, MainWindow *mw, TerrainDock *td): QDialog(parent),mainWindow(mw)//,  mUi(new Ui::DungeonDialog)
{
  //  mUi->setupUi(this);
    setupUi(this);
    mainWindow =mw;
    terrainDock = td;
    terrainView = td->getTerrainView();



    QWidget *w = new QWidget(this);

    QVBoxLayout *horizontal = new QVBoxLayout(w);
    //horizontal->setSpacing(0);
    //horizontal->setMargin(5);
    horizontal->addWidget(terrainView);

    //mUi->addWidget(w);


}

