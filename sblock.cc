#include "sblock.h"
using namespace std;

SBlock::SBlock(LevelType level, DisplayFormat format) : Block{BlockType::SBlock, level, format} {}

SBlock::~SBlock(){};

vector<pair<int, int>> SBlock::baseGetCoordinates(int rotState, pair<int, int> leftBottom) const{
  vector<pair<int, int>> coords;
  if(rotState == 0 || rotState == 2){
    for(int i=0; i<2; i++){
      coords.emplace_back(make_pair(leftBottom.first+i, leftBottom.second));
      coords.emplace_back(make_pair(leftBottom.first+1+i, leftBottom.second-1));
    }
  }
  else if(rotState == 1 || rotState == 3){
    for(int i=0; i<2; i++){
      coords.emplace_back(make_pair(leftBottom.first, leftBottom.second-1-i));
      coords.emplace_back(make_pair(leftBottom.first+1, leftBottom.second-i));
    }
  }
  return coords;
}

shared_ptr<Block> SBlock::getThisPtr(){
  shared_ptr<SBlock> now = shared_from_this();
  return dynamic_pointer_cast<Block>(now);
}

