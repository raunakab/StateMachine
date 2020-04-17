#include "Jumper.h"



BaseState::Jumper::Jumper(std::string const & action, std::shared_ptr<BaseState> const & baseState) : action(((action != "") && baseState) ? action : ""), baseState(((action != "") && baseState) ? baseState : std::shared_ptr<BaseState>(nullptr)) { return; }
BaseState::Jumper::~Jumper() { return; }

bool const BaseState::Jumper::operator==(BaseState::Jumper const & other) const { return this->baseState == other.getBaseState(); }
bool const BaseState::Jumper::operator!=(BaseState::Jumper const & other) const { return !this->operator==(other); }

std::string const BaseState::Jumper::getAction() const { return this->action; }
std::shared_ptr<BaseState> const BaseState::Jumper::getBaseState() const { return this->baseState; }