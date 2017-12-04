#include "level0.h"
#include "invalidfileexcept.h"
#include "invalidshapeexcept.h"
#include <iostream>
#include <fstream>
using namespace std;

Level0::Level0(int seed, string fileName):
	Level{LevelType::Level0, false, false,seed, fileName}, fileStream{ifstream{fileName}} {}

void Level0::setIsRandom(bool isRandom, string fileName) {}
/*
void Level0::setFileName(string fileName) {
	this->fileName = fileName;
}
*/
// Block constructor
// Block(LevelType level, DisplayFormat format)
shared_ptr<Block> Level0::generateBlock(BlockType type) {
  if(type == BlockType::None){
    string input;
    if (fileStream >> input) {
      type = inputInterpreter(input);
    }
  }
  return makeBlock(type, LevelType::Level0);
}

shared_ptr<Block> Level0::obstacle(pair<int,int> &) {
	return nullptr;
}
