#include "iblock.h"
using namespace std;

IBlock::IBlock(LevelType level, DisplayFormat format) : Block{BlockType::IBlock, level, format} {}

IBlock::~IBlock(){};

vector<pair<int, int>> IBlock::baseGetCoordinates(int rotState, pair<int, int> leftBottom) const{
  vector<pair<int, int>> coords;
  if(rotState == 1 || rotState == 3){
    for(int i=0; i<4; i++){
      coords.emplace_back(make_pair(leftBottom.first, leftBottom.second-i));
    }
  }
  else if(rotState == 0 || rotState == 2){
    for(int i=0; i<4; i++){
      coords.emplace_back(make_pair(leftBottom.first+i, leftBottom.second));
    }
  }
  return coords;
}

shared_ptr<Block> IBlock::getThisPtr(){
  shared_ptr<IBlock> now = shared_from_this();
  return dynamic_pointer_cast<Block>(now);
}

