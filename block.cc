#include "block.h"

using namespace std;

Block::Block(BlockType type, LevelType level, DisplayFormat format) : 
 type{type}, level{level}, format{format}, cellsLeft{4}, rotationState{0} {};

Info Block::getInfo() const{
  return Info{level, type, format};
}

vector<pair<int, int>> Block::baseGetCoordinates(int roState, pair<int, int> coords) const{
  return vector<pair<int, int>>();
}

vector<pair<int, int>> Block::getRotated(bool clockwise, pair<int, int> leftBottom) const{
  int newRoState;
  if(clockwise){
    newRoState = rotationState == 4 ? 0 : rotationState+1;
  }
  else{
    newRoState = rotationState == 0 ? 4 : rotationState-1;
  }
  return baseGetCoordinates(newRoState, leftBottom);
}

void Block::rotate(bool clockwise){
  if(clockwise){
    rotationState = rotationState == 4 ? 0 : rotationState+1;
  }
  else{
    rotationState = rotationState == 0 ? 4 : rotationState-1;
  }
}

LevelType Block::cellDeleted(){
  cellsLeft--;
  if(cellsLeft <=0 ) return level;
  return level;
}

vector<pair<int, int>> Block::getCoordinates(pair<int, int> coords) const{
  return baseGetCoordinates(rotationState, coords);
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

ostream &operator<<(ostream &out, const shared_ptr<Block> &b){
  out << "Type: " << b->type << "  Level: " << b->level << "  Format: " << b->format << endl;
  out << "  RotationState: " << b->rotationState << "  CellsLeft: " << b->cellsLeft << endl;
  return out;
}

