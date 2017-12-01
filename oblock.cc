#include "oblock.h"
using namespace std;

OBlock::OBlock(LevelType level, DisplayFormat format) : Block{BlockType::OBlock, level, format} {}

OBlock::~OBlock(){};

vector<pair<int, int>> OBlock::baseGetCoordinates(int rotState, pair<int, int> leftBottom) const{
  vector<pair<int, int>> coords;
  if(rotState == 0 || rotState == 1 || rotState == 2 || rotState == 3){
    for(int i=0; i<2; i++){
      coords.emplace_back(make_pair(leftBottom.first+i, leftBottom.second-1));
      coords.emplace_back(make_pair(leftBottom.first+i, leftBottom.second));
    }
  }
  return coords;
}

shared_ptr<Block> OBlock::getThisPtr(){
  shared_ptr<OBlock> now = shared_from_this();
  return dynamic_pointer_cast<Block>(now);
}

