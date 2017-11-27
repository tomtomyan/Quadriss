#include "subject.h"

template <typename InfoType, typename StateType>
void Subject<InfoType, StateType>::attach(std::shared_ptr<Observer<InfoType, StateType>> o){
  observers.emplace_back(o);
}

template <typename InfoType, typename StateType>
void Subject<InfoType, StateType::detach(std::shared_ptr<Observer<InfoType, StateType>> o){
  for(auto it = observers.begin(); it != observers.endl; ++it){
    if(*it == *o){
      observers.erase(it);
    }
  }
}

template <typename InfoType, typename StateType>
void Subject<InfoType, StateType>::notifyObservers(){
  for (auto ob : observers) ob->notify(std::shared_ptr<Subject<InfoType, StateType>>(this));
}

template <typename InfoType, typename StateType>
void Subject<InfoType, StateType>::setState(StateType newState){
  state = newState;
}

template <typename InfoType, typename StateType>
StateType Subject<InfoType, StateType>::getState() const{
  return state;
}

