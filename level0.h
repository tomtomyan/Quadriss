#ifndef LEVEL0_H
#define LEVEL0_H

class Level0 : public Level {
	public:
	void setIsRandom(bool) override;
	Block *generateBlock() override;
	Block *obstacle(Pair<int,int> &) override;
};

#endif
