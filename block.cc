#include "block.h"
using namespace std;

Info Block::getInfo() const{
  return Info{level, type, format};
}

LevelType Block::cellDeleted(){
  cellsLeft--;
  if(cellsLeft <=0 ) return level;
  return level;
}


vector<pair<int, int>> Block::getCoordinates(pair<int, int>) const{
  return vector<pair<int, int>>();
}

void Block::notifyAttachDetach(bool isAttach, shared_ptr<Observer<Info, State>> ob, pair<int, int> coords){
  State newState;
  newState.coordinates = coords;
  newState.message = isAttach ? Message::Attach : Message::Detach;
  setState(newState);
  ob->notify(shared_ptr<Subject<Info, State>>(this));
  if(isAttach) attach(ob);
  else detach(ob);
}

