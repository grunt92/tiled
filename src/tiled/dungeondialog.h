#ifndef DUNGEONDIALOG_H
#define DUNGEONDIALOG_H

#include <QDialog>
#include "ui_dungeondialog.h"
#include "mainwindow.h"
#include "terraindock.h"
#include "terrainview.h"

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
    //Ui::DungeonDialog *mUi;

};

} // namespace Internal
} // namespace Tiled

#endif 
