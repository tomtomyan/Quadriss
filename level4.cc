#include "level4.h"
using namespace std;

void setIsRandom(bool) override;
void setFileName(string) override;

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
        return make_shared<Block>(LevelType::Level3, DisplayFormat::Standard);
}

shared_ptr<Block> obstacle(pair<int,int> &leftBottom) {
	int leftBottomRow = leftBottom.second; // y-value
	leftBottom = make_pair(5, leftBottomRow);
	return make_shared<OneCell>(LevelType::OneCell, DisplayFormat::Standard);
}
