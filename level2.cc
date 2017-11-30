#include "level2.h"


Level2::Level2():
        Level{LevelType::Level2, false, true} {}


void setIsRandom(bool isRandom) {}


void setFileName(string fileName) {}


void setFileStream(ifstream &fileStream) {}


shared_ptr<Block> generateBlock() {
        BlockType blockType;
        int randNum = rand() % 100 + 1 - 93;
        if (randNum == 1) {
                return make_shared<SBlock>(LevelType::Level2, DisplayFormat::Standard);
        }
        else if (randNum == 2) {
                return make_shared<ZBlock>(LevelType::Level2, DisplayFormat::Standard);
        }
        else if (randNum == 3) {
                return make_shared<IBlock>(LevelType::Level2, DisplayFormat::Standard);
        }
        else if (randNum == 4) {
                return make_shared<JBlock>(LevelType::Level2, DisplayFormat::Standard);
        }
        else if (randNum == 5) {
                return make_shared<LBlock>(LevelType::Level2, DisplayFormat::Standard);
        }
        else if (randNum == 6) {
                return make_shared<OBlock>(LevelType::Level2, DisplayFormat::Standard);
        }
        else {
                return make_shared<TBlock>(LevelType::Level2, DisplayFormat::Standard);
        }
}


shared_ptr<Block> obstacle(pair<int,int> &) {
	return nullptr;
}
