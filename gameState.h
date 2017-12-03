#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <vector>
#include "info.h"

struct GameState{
 LevelType level;
 int playScore;
 int highScore;
 BlockType nextBlock;
 std::vector<std::pair<int, int>> nextBlockCoords;
};

#endif

