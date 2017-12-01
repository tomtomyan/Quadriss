#include "block.h"
#include <iostream>
using namespace std;

Block::Block(BlockType type, LevelType level, DisplayFormat format) : 
 type{type}, level{level}, format{format}, cellsLeft{4}, rotationState{0} {};

Block::~Block(){};

int Block::getCellsLeft() const{
  return cellsLeft;
}

int Block::getRotationState() const{
  return rotationState;
}

Info Block::getInfo() const{
  return Info{level, type, format};
}

vector<pair<int, int>> Block::getRotated(bool clockwise, pair<int, int> leftBottom) const{
  int newRoState;
  if(clockwise){
    newRoState = rotationState == 3 ? 0 : rotationState+1;
  }
  else{
    newRoState = rotationState == 0 ? 3 : rotationState-1;
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
  ob->notify(getThisPtr());
  if(isAttach) attach(ob);
  else detach(ob);
}

ostream &operator<<(ostream &out, const shared_ptr<Block> &b){
  out << "Type: " << b->getInfo().type << "  Level: " << b->getInfo().level << "  Format: " << b->getInfo().format << endl;
  out << "  RotationState: " << b->getRotationState() << "  CellsLeft: " << b->getCellsLeft() << endl;
  return out;
}

