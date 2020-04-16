#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include "./../BaseState/BaseState.h"

class StateMachine {
    private:
        StateMachine(StateMachine const &);
        void operator=(StateMachine const &);

        std::vector<BaseState *> * const baseStates = new std::vector<BaseState *>;
        BaseState * currentState = nullptr;

    public:
        StateMachine();
        ~StateMachine();

        bool const operator==(StateMachine const &) const;
        bool const operator!=(StateMachine const &) const;

        bool const containsBaseState(int const) const;
        bool const addBaseState(std::shared_ptr<BaseState> const &&);
        bool const removeBaseState(int const);
};

#endif