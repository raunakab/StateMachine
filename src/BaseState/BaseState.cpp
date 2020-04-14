#include "BaseState.h"



BaseState::Jumper::Jumper() { return; }
BaseState::Jumper::Jumper(Jumper const & other) { return; }
void BaseState::Jumper::operator=(Jumper const & other) { return; }
BaseState::BaseState(BaseState const & other) { return; }
void BaseState::operator=(BaseState const & other) { return; }



BaseState::Jumper::Jumper(std::string const & action, std::shared_ptr<BaseState> const baseState) : action(action), baseState(baseState) { return; }
BaseState::Jumper::~Jumper() { return; }

bool const BaseState::Jumper::operator==(BaseState::Jumper const & other) const { return this->baseState == other.getBaseState(); }
bool const BaseState::Jumper::operator!=(BaseState::Jumper const & other) const { return !this->operator==(other); }

std::string const BaseState::Jumper::getAction() const { return this->action; }
std::shared_ptr<BaseState> const BaseState::Jumper::getBaseState() const { return this->baseState; }



unsigned int BaseState::counter = 0;

BaseState::BaseState() { return; }
BaseState::~BaseState() {
    typename std::vector<BaseState::Jumper const *>::iterator itr(this->jumpers->begin());
    for (; itr!=this->jumpers->end(); ++itr) delete *itr;

    delete jumpers;
    return;
}

bool const BaseState::operator==(BaseState const & other) const { return this->id == other.getID(); }
bool const BaseState::operator!=(BaseState const & other) const { return !this->operator==(other); }

int const BaseState::getID() const { return this->id; }

bool const BaseState::containsAction(std::string const & action) const {
    typename std::vector<BaseState::Jumper const *>::iterator itr(this->jumpers->begin());
    for (; itr!=this->jumpers->end(); ++itr) if ((*itr)->getAction() == action) return true;

    return false;
}
bool const BaseState::containsBaseState(std::shared_ptr<BaseState> const & baseState) const {
    if (!baseState) return false;

    typename std::vector<BaseState::Jumper const *>::iterator itr(this->jumpers->begin());
    for (; itr!=this->jumpers->end(); ++itr) if ((*itr)->getBaseState() == baseState) return true;

    return false;
}
bool const BaseState::addJumper(std::string const && action, std::shared_ptr<BaseState> const baseState) {
    if (!baseState || this->containsAction(action) || this->containsBaseState(baseState)) return false;
    this->jumpers->push_back(new BaseState::Jumper(action,baseState));

    return true;
}
bool const BaseState::removeJumper(std::string const & action) {
    typename std::vector<BaseState::Jumper const *>::iterator itr_a(this->jumpers->begin());
    typename std::vector<BaseState::Jumper const *>::iterator itr_b(itr_a);
    BaseState::Jumper const * temp(nullptr);

    for (; itr_a!=this->jumpers->end(); ++itr_a) {
        if ((*itr_a)->getAction() != action) {
            *itr_b = *itr_a;
            ++itr_b;
        } else {
            delete *itr_a;
            *itr_a = nullptr;
        }
    }
    this->jumpers->erase(itr_b,itr_a);

    return false;
}

std::shared_ptr<BaseState> const BaseState::transition(std::string const & action) const {
    typename std::vector<BaseState::Jumper const *>::iterator itr(this->jumpers->begin());
    for (; itr!=this->jumpers->end(); ++itr) if ((*itr)->getAction() == action) return (*itr)->getBaseState();
    
    return nullptr;
}


int main() {
    return 0;
}