#include "level0.h"
#include "invalidfileexcept.h"
#include "invalidshapeexcept.h"
#include <iostream>
#include <fstream>
using namespace std;

Level0::Level0(int seed, string fileName):
	Level{LevelType::Level0, false, false,seed, fileName}, fileStream{ifstream{fileName}} {
  if(!fileStream) throw InvalidFile();
}

void Level0::setIsRandom(bool isRandom, string fileName) {}

// Block constructor
// Block(LevelType level, DisplayFormat format)
shared_ptr<Block> Level0::generateBlock(BlockType type) {
  if(type == BlockType::None){
    string input;
    if (fileStream >> input) {
      type = inputInterpreter(input);
    }
    if(type == BlockType::None){
      cout << "End of file, restarting from the begining" << endl;
      fileStream = ifstream{fileName};
      if(fileStream >> input) type = inputInterpreter(input);
      else throw InvalidFile{};
    }
  }
  return makeBlock(type, LevelType::Level0);
}

shared_ptr<Block> Level0::obstacle(pair<int,int> &) {
	return nullptr;
}
