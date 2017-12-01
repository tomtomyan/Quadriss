#include "jblock.h"
using namespace std;

JBlock::JBlock(LevelType level, DisplayFormat format) : Block{BlockType::JBlock, level, format} {}

JBlock::~JBlock(){};
/*
Info JBlock::getInfo(){
  return Info{LevelType::None,BlockType::JBlock, DisplayFormat::Standard};
}
*/

vector<pair<int, int>> baseGetCoordinates(int rotState, pair<int, int> leftBottom){
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
    for(int i; i<3; i++){
      coords.emplace_back(make_pair(leftBottom.first+1, leftBottom.second-i));
    }
  }
  return coords;
}

