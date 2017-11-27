#include "cell.h"
using namespace std;

void Cell::notify(shared_ptr<Subject<Info, State>> whoFrom){
  State wfState = whoFrom->getState();
  if(wfState.message == Message::Attach){
    block = dynamic_pointer_cast<Block>(whoFrom);
    if(block){
      setState(wfState);
      notifyObservers();
    }
  }
  else if(wfState.message == Message::Detach){
    block = nullptr;
    setState(wfState);
    notifyObservers();
  }
}

Info Cell::getInfo() const{
  if(block){
    return block->getInfo();
  }
  return Info{LevelType::None, BlockType::None, DisplayFormat::Standard};
}

LevelType Cell::deleteCell() const{
  if(block){
    return block->cellDeleted();
  }
  return LevelType::None;
}

