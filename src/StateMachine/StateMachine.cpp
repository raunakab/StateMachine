#include "StateMachine.h"



StateMachine::StateMachine() { return; }
StateMachine::~StateMachine() {
    
    return;
}

bool const StateMachine::operator==(StateMachine const & other) const { return false; }
bool const StateMachine::operator!=(StateMachine const & other) const { return !this->operator==(other); }

bool const StateMachine::contains_base_state(std::shared_ptr<BaseState> const & baseState) const {
    return false;
}
bool const StateMachine::containsBaseState(int const id) const {
    std::vector<std::shared_ptr<BaseState>>::iterator itr(this->baseStates->begin());
    for (; itr!=this->baseStates->end(); ++itr) if ((*itr)->getID() == id) return true;

    return false;
}
std::shared_ptr<BaseState> const StateMachine::get_base_state(int const id) const {

}
int const StateMachine::get_id(std::shared_ptr<BaseState> const & baseState) const {

}
bool const StateMachine::addBaseState(std::shared_ptr<BaseState> const && baseState) {
    
}
bool const StateMachine::removeBaseState(int const id) {

}