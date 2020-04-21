#ifndef BASESTATE_H
#define BASESTATE_H

#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <algorithm>
#include "./../../lib/linker.cpp"
// #include "./../StateMachine/StateMachine.h"

#define DFLT_MAP -1
#define SELF_MAP -2



class BaseState {
    friend class StateMachine;
    private:
        BaseState(BaseState const &);
        void operator=(BaseState const &);

        class Jumper;
        static unsigned int counter;
        unsigned int const id = BaseState::counter++;
        std::vector<BaseState::Jumper const *> * const jumpers = new std::vector<BaseState::Jumper const *>;

        std::vector<BaseState::Jumper const *> * const get_jumpers() const;

        BaseState::Jumper const * const get_jumper(std::string const &) const;
        BaseState::Jumper const * const get_jumper(std::shared_ptr<BaseState> const &) const;

        void remove_all_jumpers();

    public:
        BaseState();
        ~BaseState();

        bool const operator==(BaseState const &) const;
        bool const operator!=(BaseState const &) const;

        unsigned int const getID() const;

        bool const containsJumper(std::string const &) const;
        bool const containsJumper(std::shared_ptr<BaseState> const &) const;
        bool const addJumper(std::string const &&, std::shared_ptr<BaseState> const &);
        bool const removeJumper(std::string const &);
        bool const removeJumper(std::shared_ptr<BaseState> const &);

        std::string const getJumperAction(std::shared_ptr<BaseState> const &) const;
        std::shared_ptr<BaseState> const getJumperBaseState(std::string const &) const;

        virtual void stateLoop() const = 0;
};

#include "./../Jumper/Jumper.h"

#endif