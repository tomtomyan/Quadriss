#ifndef LEVEL1_H
#define LEVEL1_H
#include <memory>
class Block;

class Level1 : public Level {
	public:
	Level1();
	void setIsRandom(bool) override;
	void setFileName(std::string) override;
//	void setFileStream(ifstream &) override;
	std::shared_ptr<Block> generateBlock() override;
	std::shared_ptr<Block> obstacle(std::pair<int,int> &) override;
};

#endif
