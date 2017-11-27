#include "subject.h"

/*
template <typename InfoType, typename StateType>
void Subject<InfoType, StateType>::attach(Observer<InfoType, StateType> *o){
  observers.emplace_back(o);
}
hi
template <typename InfoType, typename StateType>
void Subject<InfoType, StateType>::notifyObservers(){
  for (auto &ob : observers) ob->notify(*this);
}
*/

template <typename InfoType, typename StateType>
void Subject<InfoTYpe, StateType>::setState(StateType newState){
  state = newState;
}

template <typename InfoType, typename StateType>
StateType Subject<InfoType, StateType>::getState() const{
  return state;
}

