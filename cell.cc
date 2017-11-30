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

LevelType Cell::deleteCell(pair<int, int> coords){
  LevelType lt = LevelType::None;
  if(block){
    State s = {coords, Message::Delete};
    setState(s);
    notifyObservers();
    lt = block->cellDeleted();
    //maybe delete current here? or not... hmmmm
    block = nullptr;
  }
  return lt; // there's something wrong if cell gets deleted with no block in it...
}

std::ostream &operator<<(std::ostream &out, const shared_ptr<Cell> &c){
  if(c->block){
    out << "Type: " << c->block->getInfo().type << "  Level: " << c->block->getInfo().level << "  Format: " << c->block->getInfo().format;
  }
  else{
    out << "BLANK";
  }
  return out;
}

