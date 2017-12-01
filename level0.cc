#include "level0.h"
#include "iblock.h"
#include "jblock.h"
#include "lblock.h"
#include "oblock.h"
#include "sblock.h"
#include "zblock.h"
#include "tblock.h"
#include "invalidfileexcept.h"
#include "invalidshapeexcept.h"
#include <iostream>
using namespace std;


Level0::Level0(ifstream &fileStream):
	Level{LevelType::Level0, false, true}, fileStream{fileStream} {}


void Level0::setIsRandom(bool isRandom) {
	if ((isRandom == false) && !(getFileStream().is_open())) {
		throw InvalidFile{};
	}
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
shared_ptr<Block> Level0::generateBlock() {
	string input;
	/*
	if (!(getFileStream().is_open())) {
		throw InvalidFile{};
	}
	*/
	if (getFileStream() >> input) {
		if (input == "I") {
			return make_shared<IBlock>(LevelType::Level0, DisplayFormat::Standard);
		}
		else if (input == "J") {
                        return make_shared<JBlock>(LevelType::Level0, DisplayFormat::Standard);
		}
		else if (input == "L") {
                        return make_shared<LBlock>(LevelType::Level0, DisplayFormat::Standard);
		}
		else if (input == "O") {
                        return make_shared<OBlock>(LevelType::Level0, DisplayFormat::Standard);
		}
		else if (input == "S") {
                        return make_shared<SBlock>(LevelType::Level0, DisplayFormat::Standard);
		}
		else if (input == "Z") {
                        return make_shared<ZBlock>(LevelType::Level0, DisplayFormat::Standard);
		}
		else if (input == "T") {
                        return make_shared<TBlock>(LevelType::Level0, DisplayFormat::Standard);
		}
		else {
			throw InvalidShape{};
		}
	}
// no Current enumeration
}


shared_ptr<Block> Level0::obstacle(pair<int,int> &) {
	return nullptr;
}
