#ifndef LEVEL4_H
#define LEVEL4_H

class Level4 : public Level {
        public:
        void setIsRandom(bool) override;
        void setFileName(string) override;
        shared_ptr<Block> generateBlock() override;
        shared_ptr<Block> obstacle(pair<int,int> &) override;
};

#endif
