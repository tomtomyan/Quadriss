#ifndef LEVEL1_H
#define LEVEL1_H

class Level1 : public Level {
	public:
	void setIsRandom(bool) override;
	void setFileName(string) override;
	shared_ptr<Block> generateBlock() override;
	shared_ptr<Block> obstacle(pair<int,int> &) override;
};

#endif
