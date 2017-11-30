#include "level0.h"
#include <fstream>


// Block constructor
// Block(BlockType type, LevelType level, DisplayFormat format)
shared_ptr<Block> Level0::generateBlock() {
	string input;
	BlockType blockType;
	if (getFileStream() >> input) {
		if (input == "I") {
			blockType = BlockType::IBlock;
		}
		else if (input == "J") {
                        blockType = BlockType::JBlock;
		}
		else if (input == "L") {
                        blockType = BlockType::LBlock;
		}
		else if (input == "O") {
                        blockType = BlockType::OBlock;
		}
		else if (input == "S") {
                        blockType = BlockType::SBlock;
		}
		else if (input == "Z") {
                        blockType = BlockType::ZBlock;
		}
		else if (input == "T") {
                        blockType = BlockType::TBlock;
		}
		else {
			//////// throw exception for invalid input?????
		}
	}
        return make_shared<Block>(LevelType::Level0, DisplayFormat::Standard);
// no Current enumeration
}

