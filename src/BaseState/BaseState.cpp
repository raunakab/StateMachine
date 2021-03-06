#include "BaseState.h"



unsigned int BaseState::counter = 0;

std::vector<BaseState::Jumper const *> * const BaseState::get_jumpers() const { return this->jumpers; }

BaseState::Jumper const * const BaseState::get_jumper(std::string const & action) const {
    if (action == std::string("")) return nullptr;

    std::vector<BaseState::Jumper const *>::iterator itr(this->jumpers->begin());
    for (; itr!=this->jumpers->end(); ++itr) if ((*itr)->getAction() == action) return (*itr);
    
    return nullptr;
}
BaseState::Jumper const * const BaseState::get_jumper(std::shared_ptr<BaseState> const & baseState) const {
    if (!baseState) return nullptr;

    std::vector<BaseState::Jumper const *>::iterator itr(this->jumpers->begin());
    for (; itr!=this->jumpers->end(); ++itr) if ((*itr)->getBaseState() == baseState) return (*itr);
    
    return nullptr;
}

void BaseState::remove_all_jumpers() {
    std::vector<BaseState::Jumper const *>::iterator itr(this->jumpers->begin());
    std::vector<BaseState::Jumper const *>::iterator starter(itr);
    
    for (; itr!=this->jumpers->end(); ++itr) {
        delete (*itr);
        (*itr) = nullptr;
    }
    this->jumpers->erase(starter,itr);

    return;
}

BaseState::BaseState() { return; }
BaseState::~BaseState() {
    this->remove_all_jumpers();
    delete jumpers;

    return;
}

bool const BaseState::operator==(BaseState const & other) const { return (this->id == other.getID()) && (this->jumpers == other.get_jumpers()); }
bool const BaseState::operator!=(BaseState const & other) const { return !this->operator==(other); }

unsigned int const BaseState::getID() const { return this->id; }

bool const BaseState::containsJumper(std::string const & action) const { return this->get_jumper(action) != nullptr; }
bool const BaseState::containsJumper(std::shared_ptr<BaseState> const & baseState) const {
    if (!baseState) return false;
    return this->get_jumper(baseState) != nullptr;
}
bool const BaseState::addJumper(std::string const && action, std::shared_ptr<BaseState> const & baseState) {
    if (!baseState || (action == std::string("")) || this->containsJumper(action) || this->containsJumper(baseState)) return false;
    this->jumpers->push_back(new BaseState::Jumper(action,baseState));

    return true;
}
bool const BaseState::removeJumper(std::string const & action) {
    std::vector<BaseState::Jumper const *>::iterator itr_a(this->jumpers->begin());
    std::vector<BaseState::Jumper const *>::iterator itr_b(itr_a);

    for (; itr_a!=this->jumpers->end(); ++itr_a) {
        if ((*itr_a)->getAction() != action) {
            *itr_b = *itr_a;
            ++itr_b;
        } else {
            delete *itr_a;
            *itr_a = nullptr;
        }
    }
    if (itr_a == itr_b) {
        this->jumpers->erase(itr_b,itr_a);
        return true;
    }

    return false;
}
bool const BaseState::removeJumper(std::shared_ptr<BaseState> const & baseState) {
    std::vector<BaseState::Jumper const *>::iterator itr_a(this->jumpers->begin());
    std::vector<BaseState::Jumper const *>::iterator itr_b(itr_a);

    for (; itr_a!=this->jumpers->end(); ++itr_a) {
        if ((*itr_a)->getBaseState() != baseState) {
            if (itr_a != itr_b) *itr_b = *itr_a;
            ++itr_b;
        } else {
            delete *itr_a;
            *itr_a = nullptr;
        }
    }
    if (itr_a == itr_b) {
        this->jumpers->erase(itr_b,itr_a);
        return true;
    }

    return false;
}

std::string const BaseState::getJumperAction(std::shared_ptr<BaseState> const & baseState) const {
    if (!baseState) return std::string("");

    BaseState::Jumper const * const temp(this->get_jumper(baseState));
    return temp ? temp->getAction() : std::string("");
}
std::shared_ptr<BaseState> const BaseState::getJumperBaseState(std::string const & action) const {
    if (action == std::string("")) return std::shared_ptr<BaseState>(nullptr);

    BaseState::Jumper const * const temp(this->get_jumper(action));
    return temp ? temp->getBaseState() : std::shared_ptr<BaseState>(nullptr);
}