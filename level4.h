#ifndef LEVEL4_H
#define LEVEL4_H
#include <fstream>
#include <memory>
#include "level.h"
class Block;

class Level4 : public Level {
	std::ifstream fileStream;
  int numDrops = 0;
        public:
	Level4(std::string fileName = "");
        void setIsRandom(bool) override;
        void setFileName(std::string) override;
//	void setFileStream(ifstream &) override;
        std::shared_ptr<Block> generateBlock(BlockType type = BlockType::None) override;
        std::shared_ptr<Block> obstacle(std::pair<int,int> &) override;
};

#endif
