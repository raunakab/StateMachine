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

bool const StateMachine::containsBaseState(std::shared_ptr<BaseState> const & baseState) const {
    std::vector<std::shared_ptr<BaseState>>::iterator itr(this->baseStates->begin());
    for (; itr!=this->baseStates->end(); ++itr) if (baseState == (*itr)) return true;

    return false;
}
std::shared_ptr<BaseState> const StateMachine::getBaseState(int const index) const {
    int const x((index >= 0) ? 1 : 0);
    int const size(this->baseStates->size());
    
    switch (x) {
        case 0: {
            int const index_mod(((-index-1) % (size+1)));
            std::vector<std::shared_ptr<BaseState>>::reverse_iterator r_itr(this->baseStates->rbegin());
            std::advance(r_itr,index_mod);
            return (*r_itr);
        }
        case 1: {
            int const i_mod(index % (size + 1));
            std::vector<std::shared_ptr<BaseState>>::iterator itr(this->baseStates->begin());
            std::advance(itr,i_mod);
            return (*itr);
        }
        default: break;
    }

    return std::shared_ptr<BaseState>(nullptr);
}
bool const StateMachine::addBaseState(std::shared_ptr<BaseState> const & baseState) {
    if (!baseState || this->containsBaseState(baseState)) return false;
    this->baseStates->push_back(baseState);

    return true;
}
bool const StateMachine::removeBaseState(std::shared_ptr<BaseState> const & baseState) {
    if (!baseState) return false;

    std::vector<std::shared_ptr<BaseState>>::iterator itr_a(this->baseStates->begin());
    std::vector<std::shared_ptr<BaseState>>::iterator itr_b(itr_a);

    for (; itr_a!=this->baseStates->end(); ++itr_a) {
        if ((*itr_a) != baseState) {
            if (itr_a != itr_b) (*itr_b) = (*itr_a);
            ++itr_b;
        } else (*itr_a) = nullptr;
    }

    if (itr_a != itr_b) {
        this->baseStates->erase(itr_b,itr_a);
        return true;
    }

    return false;
}

std::shared_ptr<BaseState> const StateMachine::getCurrentState() const { return this->currentState; }

bool const StateMachine::start(std::shared_ptr<BaseState> const & baseState) {
    if (!baseState || !this->containsBaseState(baseState)) return false;
    baseState->stateLoop();

    return true;
}
bool const StateMachine::transition(std::string const & action) const { return false; }