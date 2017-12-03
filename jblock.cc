#include "jblock.h"
using namespace std;

JBlock::JBlock(LevelType level, DisplayFormat format) : Block{BlockType::JBlock, level, format} {}

JBlock::~JBlock(){};

vector<pair<int, int>> JBlock::baseGetCoordinates(int rotState, pair<int, int> leftBottom) const{
  vector<pair<int, int>> coords;
  if(rotState == 0){
    coords.emplace_back(make_pair(leftBottom.first, leftBottom.second-1));
    for(int i=0; i<3; i++){
      coords.emplace_back(make_pair(leftBottom.first+i, leftBottom.second));
    }
  }
  else if(rotState == 1){
    for(int i=0; i<3; i++){
      coords.emplace_back(make_pair(leftBottom.first, leftBottom.second-i));
    }
    coords.emplace_back(make_pair(leftBottom.first+1, leftBottom.second-2));
  }
  else if(rotState == 2){
    for(int i=0; i<3; i++){
      coords.emplace_back(make_pair(leftBottom.first+i, leftBottom.second-1));
    }
    coords.emplace_back(make_pair(leftBottom.first+2, leftBottom.second));
  }
  else if(rotState == 3){
    coords.emplace_back(make_pair(leftBottom.first, leftBottom.second));
    for(int i=0; i<3; i++){
      coords.emplace_back(make_pair(leftBottom.first+1, leftBottom.second-i));
    }
  }
  return coords;
}

shared_ptr<Block> JBlock::getThisPtr(){
  shared_ptr<JBlock> now = enable_shared_from_this<JBlock>::shared_from_this();
  return dynamic_pointer_cast<Block>(now);
}

