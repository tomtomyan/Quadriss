#ifndef INFO_H
#define INFO_H

enum class DisplayFormat {Standard, Hint, Obstacle, Current};
enum class LevelType {None, Level1, Level2, Level3 , Level4};
enum class BlockType {None, IBlock, JBlock, LBlock, OBlock, SBlock, ZBlock, TBlock, OneCell};

struct Info{
  LevelType level;
  BlockType block;
  DisplayFormat format;
};

#endif

