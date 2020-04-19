#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include "./../BaseState/BaseState.h"

class StateMachine {
    private:
        StateMachine(StateMachine const &);
        void operator=(StateMachine const &);

        std::vector<std::shared_ptr<BaseState>> * const baseStates = new std::vector<std::shared_ptr<BaseState>>;
        std::shared_ptr<BaseState> currentState = std::shared_ptr<BaseState>(nullptr);

        std::vector<std::shared_ptr<BaseState>> * const get_base_states() const;

    public:
        StateMachine();
        ~StateMachine();

        bool const operator==(StateMachine const &) const;
        bool const operator!=(StateMachine const &) const;

        bool const containsBaseState(std::shared_ptr<BaseState> const &) const;
        std::shared_ptr<BaseState> const getBaseState(int const) const;
        bool const addBaseState(std::shared_ptr<BaseState> const &);
        bool const removeBaseState(std::shared_ptr<BaseState> const &);

        std::shared_ptr<BaseState> const getCurrentState() const;

        bool const start(std::shared_ptr<BaseState> const &);
        bool const transition(std::string const &) const;
};

#endif