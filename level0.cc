#include "level0.h"
/*
#include "iblock.h"
#include "jblock.h"
#include "lblock.h"
#include "oblock.h"
#include "sblock.h"
#include "zblock.h"
#include "tblock.h"
*/
#include "invalidfileexcept.h"
#include "invalidshapeexcept.h"
#include <iostream>
#include <fstream>
using namespace std;


Level0::Level0(string fileName):
	Level{LevelType::Level0, false, true}, fileStream{ifstream{fileName}} {}


void Level0::setIsRandom(bool isRandom) {
	if ((isRandom == false) && !(fileStream.is_open())) {
		throw InvalidFile{};
	}
	this->isRandom = isRandom;
}


void Level0::setFileName(string fileName) {
	this->fileName = fileName;
}

/*
void setFileStream(ifstream &fileStream) {
	this->fileStream = fileStream;
}
*/


// Block constructor
// Block(LevelType level, DisplayFormat format)
shared_ptr<Block> Level0::generateBlock(BlockType type) {
  if(type == BlockType::None){
    string input;
	/*
	if (!(getFileStream().is_open())) {
		throw InvalidFile{};
	}
	*/
    if (fileStream >> input) {
      type = inputInterpreter(input);
    }
  }

  return makeBlock(type, LevelType::Level0);
// no Current enumeration
}


shared_ptr<Block> Level0::obstacle(pair<int,int> &) {
	return nullptr;
}
