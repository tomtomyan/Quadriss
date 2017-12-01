#include "level1.h"


Level1::Level1():
        Level{LevelType::Level1, false, true} {}


void setIsRandom(bool) {}


void setFileName(string fileName) {}


void setFileStream(ifstream &fileStream) {}


// generate a random number between 1 and 84 inclusive
// if this number is:
// 1-7: S-Block
// 8-14: Z-Block
// 15-28: I
// 29-42: J
// 43-56: L
// 57-70: O
// 71-84: T
shared_ptr<Block> generateBlock() {
	BlockType blockType;
	int randNum = rand() % 100 + 1 - 16;
	if ((1 <= randNum) && (randNum <= 7)) {
		return make_shared<SBlock>(LevelType::Level1, DisplayFormat::Standard);
	}
	else if ((8 <= randNum) && (randNum <= 14)) {
		return make_shared<ZBlock>(LevelType::Level1, DisplayFormat::Standard);
	}
	else if ((15 <= randNum) && (randNum <= 28)) {
		return make_shared<IBlock>(LevelType::Level1, DisplayFormat::Standard);
	}
	else if ((29 <= randNum) && (randNum <= 42)) {
		return make_shared<JBlock>(LevelType::Level1, DisplayFormat::Standard);
	}
	else if ((43 <= randNum) && (randNum <= 56)) {
		return make_shared<LBlock>(LevelType::Level1, DisplayFormat::Standard);
	}
	else if ((57 <= randNum) && (randNum <= 70)) {
		return make_shared<OBlock>(LevelType::Level1, DisplayFormat::Standard);
	}
	else {
		return make_shared<TBlock>(LevelType::Level1, DisplayFormat::Standard);
	}
}


shared_ptr<Block> obstacle(pair<int,int> &) {
	return nullptr;
}
