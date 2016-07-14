import qbs 1.0

TiledPlugin {
	cpp.defines: ["DUNGEON_LIBRARY"]
	
	files:[
		"dungeon_global.h",
		"dungeonplugin.cpp"
		"dungeonplugin.h"
		"plugin.json"
	]
}