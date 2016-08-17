#ifndef DUNGEONDIALOG_H
#define DUNGEONDIALOG_H

#include <QDialog>
#include "ui_dungeondialog.h"
#include "mainwindow.h"
#include "terraindock.h"
#include "terrainview.h"
#include "mapdocument.h"

namespace Tiled {
namespace Internal {

class DungeonDialog : public QDialog , public Ui::DungeonDialog
{
    Q_OBJECT

public:
    DungeonDialog(QWidget *parent = nullptr, MainWindow *mw = nullptr, TerrainDock *td = nullptr);
private:
    MainWindow *mainWindow;
    TerrainDock *terrainDock;
    TerrainView *terrainView;
    Ui::DungeonDialog *mUi;
    MapDocument *mapDocument;
    std::vector<Terrain*> terrains;
private slots:
    void generateDungeon();
    void cancel();
    void checkOk();

};

} // namespace Internal
} // namespace Tiled

#endif 
