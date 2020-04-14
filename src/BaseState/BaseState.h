#ifndef BASESTATE_H
#define BASESTATE_H

#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <algorithm>
#include "../../lib/linker.cpp"

#define DFLT_MAP -1
#define SELF_MAP -2



class Manager {
    private:
        std::vector<BaseState * const> * const states = new std::vector<BaseState * const>();

    public:
        Manager();
        Manager(Manager const & other);
        ~Manager();

        void operator=(Manager const & other);
        bool const operator==(Manager const & other) const;
        bool const operator!=(Manager const & other) const;

        std::vector<BaseState * const> * const getState() const;
        // Setter not available
        bool const addBaseState(BaseState const & baseState);
        bool const removeBaseState(BaseState const & baseState);
        bool const containsBaseState(BaseState const & baseState);
};

class BaseState {
    private:
        class Jumper {
            private:
                std::string const action = "";
                std::shared_ptr<BaseState> const baseState = nullptr;

                Jumper();
                Jumper(BaseState::Jumper const &);
                void operator=(BaseState::Jumper const &);

            public:
                Jumper(std::string const &, std::shared_ptr<BaseState> const);
                ~Jumper();

                bool const operator==(BaseState::Jumper const &) const;
                bool const operator!=(BaseState::Jumper const &) const;

                std::string const getAction() const;
                std::shared_ptr<BaseState> const getBaseState() const;
        };

        static unsigned int counter;
        int const id = BaseState::counter++;
        std::vector<BaseState::Jumper const *> * const jumpers = new std::vector<BaseState::Jumper const *>;

        std::vector<BaseState::Jumper const *> * const get_jumpers() const;

        BaseState(BaseState const &);
        void operator=(BaseState const &);

    public:
        BaseState();
        ~BaseState();

        bool const operator==(BaseState const &) const;
        bool const operator!=(BaseState const &) const;

        int const getID() const;

        bool const containsAction(std::string const &) const;
        bool const containsBaseState(std::shared_ptr<BaseState> const &) const;
        bool const addJumper(std::string const &&, std::shared_ptr<BaseState> const);
        bool const removeJumper(std::string const &);

        std::shared_ptr<BaseState> const transition(std::string const &) const;
};



#endif