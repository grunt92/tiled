#include "dungeondialog.h"

#include <QCoreApplication>
#include <QDesktopServices>

using namespace Tiled::Internal;

DungeonDialog::DungeonDialog(QWidget *parent): QDialog(parent)
{
    setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    setMaximumSize(432, 460);

    const QString html = QCoreApplication::translate(
            "AboutDialog",
            "<p align=\"center\"><font size=\"+2\"><b>Tiled Map Editor</b></font><br><i>Version %1</i></p>\n"
            "<p align=\"center\">Copyright 2008-2016 Thorbj&oslash;rn Lindeijer<br>(see the AUTHORS file for a full list of contributors)</p>\n"
            "<p align=\"center\">You may modify and redistribute this program under the terms of the GPL (version 2 or later). "
            "A copy of the GPL is contained in the 'COPYING' file distributed with Tiled.</p>\n"
            "<p align=\"center\"><a href=\"http://www.mapeditor.org/\">http://www.mapeditor.org/</a></p>\n")
            .arg(QApplication::applicationVersion());

}

