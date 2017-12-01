#include "level3.h"
#include "info.h"
#include "iblock.h"
#include "jblock.h"
#include "lblock.h"
#include "oblock.h"
#include "sblock.h"
#include "zblock.h"
#include "tblock.h"
#include "invalidfileexcept.h"
#include "invalidshapeexcept.h"
using namespace std;

Level3::Level3(ifstream &fileStream):
        Level{LevelType::Level3, true, true}, fileStream{fileStream} {}


void Level3::setIsRandom(bool isRandom) {
        if ((isRandom == false) && !(getFileStream().is_open())) {
                throw InvalidFile{};
        }
	this->isRandom = isRandom;
}


void Level3::setFileName(string fileName) {
	this->fileName = fileName;
}

/*
void setFileStream(ifstream &fileStream) {
	this->fileStream = fileStream;
}
*/


// S: 18/81 -> 1-18
// Z: 18/81 -> 19-36
// I: 9/81 -> 37-45
// J: " -> 46-54
// L: " -> 55-63
// O: " -> 64-72
// T: " -> 73-81
shared_ptr<Block> Level3::generateBlock(BlockType type) {
	if (type == BlockType::None && getIsRandom() == false) {
		/*
		if (!(getFileStream().is_open())) {
			throw InvalidFile{};
		}
		*/
		string input;  // input is type of Blocks
		if (getFileStream() >> input) {
      type = inputInterpreter(input);
		}
	}
	else if (type == BlockType::None) {
  	int randNum = rand() % 81 + 1;  // 1-81
    if ((1 <= randNum) && (randNum <= 18)) type = BlockType::SBlock;
    else if ((19 <= randNum) && (randNum <= 36)) type = BlockType::ZBlock;
    else if ((37 <= randNum) && (randNum <= 45)) type = BlockType::IBlock;
    else if ((46 <= randNum) && (randNum <= 54)) type = BlockType::JBlock;
    else if ((55 <= randNum) && (randNum <= 63)) type = BlockType::LBlock;
    else if ((64 <= randNum) && (randNum <= 72)) type = BlockType::OBlock;
    else if ((73 <= randNum) && (randNum <= 81)) type = BlockType::TBlock;
    else{
      //throw something??
    }
	}
  return makeBlock(type, LevelType::Level3);
}


shared_ptr<Block> Level3::obstacle(pair<int,int> &) {
	return nullptr;
}

