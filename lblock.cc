#include "lblock.h"
using namespace std;

LBlock::LBlock(LevelType level, DisplayFormat format) : Block{BlockType::LBlock, level, format} {}

LBlock::~LBlock(){};

vector<pair<int, int>> LBlock::baseGetCoordinates(int rotState, pair<int, int> leftBottom) const{
  vector<pair<int, int>> coords;
  if(rotState == 0){
    coords.emplace_back(make_pair(leftBottom.first+2, leftBottom.second-1));
    for(int i=0; i<3; i++){
      coords.emplace_back(make_pair(leftBottom.first+i, leftBottom.second));
    }
  }
  else if(rotState == 1){
    for(int i=0; i<3; i++){
      coords.emplace_back(make_pair(leftBottom.first, leftBottom.second-i));
    }
    coords.emplace_back(make_pair(leftBottom.first+1, leftBottom.second));
  }
  else if(rotState == 2){
    for(int i=0; i<3; i++){
      coords.emplace_back(make_pair(leftBottom.first+i, leftBottom.second-1));
    }
    coords.emplace_back(make_pair(leftBottom.first, leftBottom.second));
  }
  else if(rotState == 3){
    coords.emplace_back(make_pair(leftBottom.first, leftBottom.second-2));
    for(int i=0; i<3; i++){
      coords.emplace_back(make_pair(leftBottom.first+1, leftBottom.second-i));
    }
  }
  return coords;
}

shared_ptr<Block> LBlock::getThisPtr(){
  shared_ptr<LBlock> now = enable_shared_from_this<LBlock>::shared_from_this();
  return dynamic_pointer_cast<Block>(now);
}

