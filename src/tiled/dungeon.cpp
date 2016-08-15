#include "dungeon.h"

using namespace Tiled;
using namespace Tiled::Internal;



dungeon::dungeon(int width, int height){
    width = width;
    height = height;
    tiles = std::vector<int> (width*height, 0);

}
dungeon::~dungeon(){}

int dungeon::get(int x, int y){
    if(x>=0&&y>=0&&x<width&&y<height)
        return tiles.at(y*width + x);
    else
        return 0;

}

void dungeon::set(int x, int y, int value){
    if(x>=0&&y>=0&&x<width&&y<height){
    tiles.at(y*width + x) = value;
}
}



