#include "level1.h"

void setIsRandom(bool) override;
void setFileName(string) override;


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
		blockType = BlockType::SBlock;
	}
	else if ((8 <= randNum) && (randNum <= 14)) {
		blockType = BlockType::ZBlock;
	}
	else if ((15 <= randNum) && (randNum <= 28)) {
		blockType = BlockType::IBlock;
	}
	else if ((29 <= randNum) && (randNum <= 42)) {
		blockType = BlockType::JBlock;
	}
	else if ((43 <= randNum) && (randNum <= 56)) {
		blockType = BlockType::LBlock;
	}
	else if ((57 <= randNum) && (randNum <= 70)) {
		blockType = BlockType::OBlock;
	}
	else {
		blockType = BlockType::TBlock;
	}
	return make_shared<Block>(blockType, LevelType::Level1, DisplayFormat::Standard);
}

shared_ptr<Block> obstacle(pair<int,int> &) override;
