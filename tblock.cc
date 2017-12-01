#include "tblock.h"
using namespace std;

TBlock::TBlock(LevelType level, DisplayFormat format) : Block{BlockType::TBlock, level, format} {}

TBlock::~TBlock(){};

vector<pair<int, int>> TBlock::baseGetCoordinates(int rotState, pair<int, int> leftBottom) const{
  vector<pair<int, int>> coords;
  if(rotState == 0){
    coords.emplace_back(make_pair(leftBottom.first+1, leftBottom.second));
    for(int i=0; i<3; i++){
      coords.emplace_back(make_pair(leftBottom.first+i, leftBottom.second-1));
    }
  }
  else if(rotState == 1){
    for(int i=0; i<3; i++){
      coords.emplace_back(make_pair(leftBottom.first+1, leftBottom.second-i));
    }
    coords.emplace_back(make_pair(leftBottom.first, leftBottom.second-1));
  }
  else if(rotState == 2){
    for(int i=0; i<3; i++){
      coords.emplace_back(make_pair(leftBottom.first+i, leftBottom.second));
    }
    coords.emplace_back(make_pair(leftBottom.first+1, leftBottom.second-1));
  }
  else if(rotState == 3){
    coords.emplace_back(make_pair(leftBottom.first+1, leftBottom.second-1));
    for(int i; i<3; i++){
      coords.emplace_back(make_pair(leftBottom.first, leftBottom.second-i));
    }
  }
  return coords;
}

shared_ptr<Block> TBlock::getThisPtr(){
  shared_ptr<TBlock> now = enable_shared_from_this<TBlock>::shared_from_this();
  return dynamic_pointer_cast<Block>(now);
}

