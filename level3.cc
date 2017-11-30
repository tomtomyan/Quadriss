#include "level3.h"


Level3::Level3():
        Level{LevelType::Level3, true, true} {}


void setIsRandom(bool isRandom) {
	this->isRandom = isRandom;
}


void setFileName(string fileName) {
	this->fileName = fileName;
}


void setFileStream(ifstream &fileStream) {
	this->fileStream = fileStream;
}


// S: 18/81 -> 1-18
// Z: 18/81 -> 19-36
// I: 9/81 -> 37-45
// J: " -> 46-54
// L: " -> 55-63
// O: " -> 64-72
// T: " -> 73-81
shared_ptr<Block> generateBlock() {
	if (getIsRandom() == false) {
		string input;  // input is type of Blocks
		if (getFileStream() >> input) {
                	if (input == "I") {
                        	return make_shared<IBlock>(LevelType::Level3, DisplayFormat::Standard);
                	}
                	else if (input == "J") {
                        	return make_shared<JBlock>(LevelType::Level3, DisplayFormat::Standard);
                	}
                	else if (input == "L") {
                        	return make_shared<LBlock>(LevelType::Level3, DisplayFormat::Standard);
                	}
                	else if (input == "O") {
                        	return make_shared<OBlock>(LevelType::Level3, DisplayFormat::Standard);
                	}
                	else if (input == "S") {
                        	return make_shared<SBlock>(LevelType::Level3, DisplayFormat::Standard);
                	}
                	else if (input == "Z") {
                        	return make_shared<ZBlock>(LevelType::Level3, DisplayFormat::Standard);
                	}
                	else if (input == "T") {
                        	return make_shared<TBlock>(LevelType::Level3, DisplayFormat::Standard);
                	}
                	else {
                        //////// throw exception for invalid input?????
                	}
		}
	}
	else {
	BlockType blockType;
	int randNum = rand() % 100 + 1 - 37;  // 1-81
        if ((1 <= randNum) && (randNum <= 18)) {
                return make_shared<SBlock>(LevelType::Level4, DisplayFormat::Standard);
        }
        else if ((19 <= randNum) && (randNum <= 36)) {
                return make_shared<ZBlock>(LevelType::Level4, DisplayFormat::Standard);
        }
        else if ((37 <= randNum) && (randNum <= 45)) {
                return make_shared<IBlock>(LevelType::Level4, DisplayFormat::Standard);
        }
        else if ((46 <= randNum) && (randNum <= 54)) {
                return make_shared<JBlock>(LevelType::Level4, DisplayFormat::Standard);
        }
        else if ((55 <= randNum) && (randNum <= 63)) {
                return make_shared<LBlock>(LevelType::Level4, DisplayFormat::Standard);
        }
        else if ((64 <= randNum) && (randNum <= 72)) {
                return make_shared<OBlock>(LevelType::Level4, DisplayFormat::Standard);
        }
        else {
                return make_shared<TBlock>(LevelType::Level4, DisplayFormat::Standard);
        }
	}
}


shared_ptr<Block> obstacle(pair<int,int> &) {
	return nullptr;
}

