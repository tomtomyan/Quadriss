#ifndef LEVEL2_H
#define LEVEL2_H

class Level2 : public Level {
        public:
        void setIsRandom(bool) override;
        void setFileName(string) override;
        shared_ptr<Block> generateBlock() override;
        shared_ptr<Block> obstacle(pair<int,int> &) override;
};

#endif
