#ifndef LEVEL0_H
#define LEVEL0_H
#include <fstream>
#include <memory>
class Block;

class Level0 : public Level {
	std::ifstream &fileStream;
	public:
	Level0(std::ifstream &);
	void setIsRandom(bool) override;
	void setFileName(std::string) override;
//	void setFileStream(ifstream &) override;
	std::shared_ptr<Block> generateBlock() override;
	std::shared_ptr<Block> obstacle(std::pair<int,int> &) override;
};

#endif
