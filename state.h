#ifndef STATE_H
#define STATE_H

//#include <utility>

enum class Message{None, Attach, Detach, Delete};

struct State{
  std::pair<int, int> coordinates;
  Message message;
};

#endif

