#ifndef STATE_H
#define STATE_H

//#include <iostream>
#include <utility>

enum class Message{None, Attach, Detach, Delete, DeleteRows};

struct State{
  std::pair<int, int> coordinates;
  Message message;
};
/*
std::ostream &operator<<(std::ostream &out, const Message &m){
  if(m == Message::None) out << "None";
  else if(m == Message::Attach) out << "Attach";
  else if(m == Message::Detach) out << "Detach";
  else if(m == Message::Delete) out << "Delete";
  return out;
}
*/
#endif

