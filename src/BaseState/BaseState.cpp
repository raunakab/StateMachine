#include "BaseState.h"



// BaseState::Jumper::Jumper() { return; }
// BaseState::Jumper::Jumper(BaseState & baseState, std::vector<int> & inputs) : baseState(&baseState), inputs(new std::vector<int>(inputs)) { return; }
// BaseState::Jumper::Jumper(Jumper const & other) : baseState(other.getBaseState()), inputs(other.getInputs()) { return; }
// BaseState::Jumper::~Jumper() {
//     delete inputs;
//     return;
// }

// BaseState * const BaseState::Jumper::getBaseState() const { return this->baseState; }

// std::vector<int> * const BaseState::Jumper::getInputs() const { return new std::vector<int>(*(this->inputs)); }
// bool const BaseState::Jumper::setInputs(std::vector<int> const & inputs) {
//     std::vector<int const>::iterator itr(inputs.begin());
//     for (; itr!=inputs.end(); ++itr) if (((*itr) == DFLT_MAP) || ((*itr) == SELF_MAP)) return false;

//     this->inputs = new std::vector<int>(inputs);
//     return true;
// }
// bool const BaseState::Jumper::addInput(int const input) {
//     if (this->containsInput(input)) return false;
    
    
// }



// int BaseState::counter = 0;



// std::vector<int> * const BaseState::call_get      (Jumper const & jumper, int              const useless_hardcoded) const { return jumper.getInputs(); }
// bool               const BaseState::call_set      (Jumper       & jumper, std::vector<int> const & inputs)                { return jumper.setInputs(inputs); }
// bool               const BaseState::call_add      (Jumper       & jumper, int              const input)                   { return jumper.addInput(input); }
// bool               const BaseState::call_remove   (Jumper       & jumper, int              const input)                   { return jumper.removeInput(input); }
// bool               const BaseState::call_contains (Jumper const & jumper, int              const input) const             { return jumper.containsInput(input); }



// template< class PARAMETER, class RETURN> RETURN BaseState::jumpers_iterator(BaseState const & baseState, PARAMETER input, RETURN defaultReturn, RETURN (*func)(BaseState const &, PARAMETER const &)) const {
//     std::vector<Jumper *> & temp(*(this->jumpers));
//     std::vector<Jumper * const>::iterator itr(temp.begin());

//     for (; itr!=temp.end(); ++itr) if ((*itr)->baseState == &baseState) return func(baseState, input);

//     return defaultReturn;
// }



// BaseState::BaseState() { return; }
// BaseState::BaseState(std::string const name) : name(name) { return; }
// BaseState::BaseState(BaseState const & other) : jumpers(new std::vector<Jumper *>(*(other.jumpers))), defaultState(other.defaultState) { return; }
// BaseState::~BaseState() {
//     delete this->jumpers;
//     return;
// }



// void BaseState::operator=(BaseState const & other) {
//     delete jumpers;

//     this->jumpers = new std::vector<Jumper *>(*(other.jumpers));
//     this->defaultState = other.defaultState;

//     return;
// }
// bool const BaseState::operator==(BaseState const & other) const { return (*(this->jumpers) == *(other.jumpers)) && (this->defaultState == other.defaultState); }
// bool const BaseState::operator!=(BaseState const & other) const { return !this->operator==(other); }



// BaseState * const BaseState::getDefaultState() const { return this->defaultState; }
// void BaseState::setDefaultState(BaseState * const defaultState) {
//     this->defaultState = defaultState;
//     return;
// }



// int const BaseState::getIdentifier() const { return this->identifier; }



// std::string const BaseState::getName() const { return this->name; }



// bool const BaseState::addJumper(BaseState & baseState, std::vector<int> & inputs) {
//     if (this->containsJumper(baseState)) return false;

//     std::vector<Jumper *> & temp(*(this->jumpers));
//     std::vector<Jumper * const>::iterator jumpers_itr(temp.begin());
//     std::vector<int const>::iterator inputs_itr(inputs.begin());

//     for (; jumpers_itr!=temp.end(); ++jumpers_itr) for (; inputs_itr!=inputs.end(); ++inputs_itr) if ((*jumpers_itr)->containsInput(*inputs_itr)) return false;

//     Jumper * const jumper = new Jumper(baseState, inputs);
//     temp.push_back(jumper);

//     return true;
// }
// bool const BaseState::removeJumper(BaseState const & baseState) {
//     std::vector<Jumper *> & temp(*(this->jumpers));
//     std::vector<Jumper * const>::iterator itr(temp.begin());

//     for (; itr!=temp.end(); ++itr) if ((*itr)->getBaseState() == &baseState) {
//         temp.erase(itr);
//         return true;
//     }
    
//     return false;
// }
// int const BaseState::containsJumper(BaseState const & baseState) const {
//     int index = 0;
//     std::vector<Jumper *> & temp(*(this->jumpers));
//     std::vector<Jumper * const>::iterator itr(temp.begin());

//     for (; itr!=(temp.end()); ++itr) {
//         if ((*itr)->getBaseState() == &baseState) return index;
//         ++index;
//     }

//     return -1;
// }



// std::vector<int> * const BaseState::getInputs     (BaseState const & baseState) const                            { return this->jumpers_iterator<int const,std::vector<int> * const> (baseState, 0,      nullptr, this->call_get);    }
// bool               const BaseState::setInputs     (BaseState const & baseState, std::vector<int> const & inputs) { return this->jumpers_iterator<std::vector<int> const, bool const> (baseState, inputs, false,   this->call_set);    }
// bool               const BaseState::addInput      (BaseState const & baseState, int const input)                 { return this->jumpers_iterator<int const, bool const>              (baseState, input,  false,   this->call_add);    }
// bool               const BaseState::removeInput   (BaseState const & baseState, int const input)                 { return this->jumpers_iterator<int const, bool const>              (baseState, input,  false,   this->call_remove); }
// bool               const BaseState::containsInput (BaseState const & baseState, int const input) const           { return this->jumpers_iterator<int const, bool const>              (baseState, input,  false,   this->call_contains); }



// BaseState * const BaseState::transition(int const input) const {
//     return nullptr;
// }

BaseState::Jumper::Jumper() { return; }
BaseState::Jumper::Jumper(Jumper const & other) { return; }
void BaseState::Jumper::operator=(Jumper const & other) { return; }



BaseState::Jumper::Jumper(std::string const & action, std::shared_ptr<BaseState> const baseState) : action(action), baseState(baseState) { return; }
BaseState::Jumper::~Jumper() { return; }

bool const BaseState::Jumper::operator==(BaseState::Jumper const & other) const { return this->baseState == other.getBaseState(); }
bool const BaseState::Jumper::operator!=(BaseState::Jumper const & other) const { return !this->operator==(other); }

std::string const BaseState::Jumper::getAction() const { return this->action; }
std::shared_ptr<BaseState> const BaseState::Jumper::getPtr() const { return this->ptr; }


int main() {
    return 0;
}