#include "StateMachine.h"



StateMachine::StateMachine() { return; }
StateMachine::~StateMachine() {
    this->currentState = nullptr;

    std::vector<std::shared_ptr<BaseState>>::iterator itr(this->baseStates->begin());
    for (; itr!=this->baseStates->end(); ++itr) {
        (*itr)->remove_all_jumpers();
        (*itr) = nullptr;
    }
    delete this->baseStates;

    return;
}

bool const StateMachine::operator==(StateMachine const & other) const { return this->baseStates == other.get_base_states(); }
bool const StateMachine::operator!=(StateMachine const & other) const { return !this->operator==(other); }

bool const StateMachine::containsBaseState(std::shared_ptr<BaseState> const & baseState) const { return Iterators<std::shared_ptr<BaseState>>::contains(*this->baseStates,baseState); }
std::shared_ptr<BaseState> const StateMachine::getBaseState(int const index) const { return Iterators<std::shared_ptr<BaseState>>::get(*this->baseStates,index); }
bool const StateMachine::addBaseState(std::shared_ptr<BaseState> const & baseState) {
    if (!baseState) return false;
    return Iterators<std::shared_ptr<BaseState>>::setInsert(*this->baseStates,baseState,-1);
}
bool const StateMachine::removeBaseState(std::shared_ptr<BaseState> const & baseState) {
    if (!baseState) return false;
    return Iterators<std::shared_ptr<BaseState>>::remove(*this->baseStates,baseState);
}

std::shared_ptr<BaseState> const StateMachine::getCurrentState() const { return this->currentState; }

bool const StateMachine::start(std::shared_ptr<BaseState> const & baseState) {
    if (!baseState || !this->containsBaseState(baseState)) return false;
    baseState->stateLoop();

    return true;
}
bool const StateMachine::transition(std::string const & action) const {
    // this->currentState->transition(action);
}