#ifndef DUNGEONDIALOG_H
#define DUNGEONDIALOG_H

#include <QDialog>
#include "ui_dungeondialog.h"

namespace Tiled {
namespace Internal {

class DungeonDialog : public QDialog, Ui::DungeonDialog
{
    Q_OBJECT

public:
    DungeonDialog(QWidget *parent = nullptr);

};

} // namespace Internal
} // namespace Tiled

#endif 
