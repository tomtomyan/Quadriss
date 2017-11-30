#include "level2.h"

void setIsRandom(bool) override;
void setFileName(string) override;

shared_ptr<Block> generateBlock() {
        BlockType blockType;
        int randNum = rand() % 100 + 1 - 93;
        if (randNum == 1) {
                blockType = BlockType::SBlock;
        }
        else if (randNum == 2) {
                blockType = BlockType::ZBlock;
        }
        else if (randNum == 3) {
                blockType = BlockType::IBlock;
        }
        else if (randNum == 4) {
                blockType = BlockType::JBlock;
        }
        else if (randNum == 5) {
                blockType = BlockType::LBlock;
        }
        else if (randNum == 6) {
                blockType = BlockType::OBlock;
        }
        else {
                blockType = BlockType::TBlock;
        }
        return make_shared<Block>(blockType, LevelType::Level2, DisplayFormat::Standard);
}

shared_ptr<Block> obstacle(pair<int,int> &) override;
