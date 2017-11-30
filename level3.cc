#include "level3.h"

void setIsRandom(bool) override;
void setFileName(string) override;

// S: 18/81 -> 1-18
// Z: 18/81 -> 19-36
// I: 9/81 -> 37-45
// J: " -> 46-54
// L: " -> 55-63
// O: " -> 64-72
// T: " -> 73-81
shared_ptr<Block> generateBlock() {
	BlockType blockType;
	int randNum = rand() % 100 + 1 - 37;  // 1-81
        if ((1 <= randNum) && (randNum <= 18)) {
                blockType = BlockType::SBlock;
        }
        else if ((19 <= randNum) && (randNum <= 36)) {
                blockType = BlockType::ZBlock;
        }
        else if ((37 <= randNum) && (randNum <= 45)) {
                blockType = BlockType::IBlock;
        }
        else if ((46 <= randNum) && (randNum <= 54)) {
                blockType = BlockType::JBlock;
        }
        else if ((55 <= randNum) && (randNum <= 63)) {
                blockType = BlockType::LBlock;
        }
        else if ((64 <= randNum) && (randNum <= 72)) {
                blockType = BlockType::OBlock;
        }
        else {
                blockType = BlockType::TBlock;
        }
        return make_shared<Block>(blockType, LevelType::Level3, DisplayFormat::Standard);
}

shared_ptr<Block> obstacle(pair<int,int> &) override;

