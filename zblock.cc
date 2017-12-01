#include "zblock.h"
using namespace std;

ZBlock::ZBlock(LevelType level, DisplayFormat format) : Block{BlockType::ZBlock, level, format} {}

ZBlock::~ZBlock(){};

vector<pair<int, int>> ZBlock::baseGetCoordinates(int rotState, pair<int, int> leftBottom) const{
  vector<pair<int, int>> coords;
  if(rotState == 0 || rotState == 2){
    for(int i=0; i<2; i++){
      coords.emplace_back(make_pair(leftBottom.first+1+i, leftBottom.second));
      coords.emplace_back(make_pair(leftBottom.first+i, leftBottom.second-1));
    }
  }
  else if(rotState == 1 || rotState == 3){
    for(int i=0; i<2; i++){
      coords.emplace_back(make_pair(leftBottom.first, leftBottom.second-i));
      coords.emplace_back(make_pair(leftBottom.first+1, leftBottom.second-1-i));
    }
  }
  return coords;
}

shared_ptr<Block> ZBlock::getThisPtr(){
  shared_ptr<ZBlock> now = shared_from_this();
  return dynamic_pointer_cast<Block>(now);
}

