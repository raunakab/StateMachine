#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include "./../BaseState/BaseState.h"

class StateMachine {
    private:
        StateMachine(StateMachine const &);
        void operator=(StateMachine const &);

        std::vector<std::shared_ptr<BaseState>> * const baseStates = new std::vector<std::shared_ptr<BaseState>>;
        std::shared_ptr<BaseState> currentState = nullptr;

        bool const contains_base_state(std::shared_ptr<BaseState> const &) const;
        std::shared_ptr<BaseState> const get_base_state(int const) const;
        int const get_id(std::shared_ptr<BaseState> const &);

    public:
        StateMachine();
        ~StateMachine();

        bool const operator==(StateMachine const &) const;
        bool const operator!=(StateMachine const &) const;

        bool const containsBaseState(int const) const;
        bool const addBaseState(std::shared_ptr<BaseState> const &&);
        bool const removeBaseState(int const);
};

/*
 *  contains_BaseState  (std::shared_ptr<BaseState> const &);   _/  :private
 *  contains_BaseState  (int const);                            _/  :public
 *  contains_ID         (std::shared_ptr<BaseState> const &);   X
 *  contains_ID         (int const);                            X
 *
 *  get_BaseState       (std::shared_ptr<BaseState> const &);   X
 *  get_BaseState       (int const);                            _/  :private
 *  get_ID              (std::shared_ptr<BaseState> const &);   _/  :private
 *  get_ID              (int const);                            X
 *
 *  add_BaseState       (std::shared_ptr<BaseState> const &);   _/  :public
*/

#endif