#ifndef LEVEL0_H
#define LEVEL0_H

class Level0 : public Level {
	public:
	void setIsRandom(bool) override;
	shared_ptr<Block>generateBlock() override;
	shared_ptr<Block>obstacle(Pair<int,int> &) override;
};

#endif
