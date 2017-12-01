#ifndef LEVEL3_H
#define LEVEL3_H

class Level3 : public Level {
        public:
        void setIsRandom(bool) override;
        void setFileName(string) override;
	void setFileStream(ifstream &) override;
        shared_ptr<Block> generateBlock() override;
        shared_ptr<Block> obstacle(pair<int,int> &) override;
};

#endif
