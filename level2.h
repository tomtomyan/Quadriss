#ifndef LEVEL2_H
#define LEVEL2_H
#include <memory>
class Block;

class Level2 : public Level {
        public:
	Level2();
        void setIsRandom(bool) override;
        void setFileName(std::string) override;
//	void setFileStream(ifstream &) override;
        std::shared_ptr<Block> generateBlock() override;
        std::shared_ptr<Block> obstacle(std::pair<int,int> &) override;
};

#endif
