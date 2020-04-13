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

// class BaseState {
//     private:
//         class Jumper {
//             private:
//                 BaseState * const baseState = nullptr;
//                 std::vector<int> * inputs = nullptr;

//             public:
//                 Jumper();
//                 Jumper(BaseState & baseState, std::vector<int> & inputs);
//                 Jumper(Jumper const & other);
//                 ~Jumper();

//                 void operator=(Jumper const & other);
//                 bool const operator==(Jumper const & other) const;
//                 bool const operator!=(Jumper const & other) const;

                

//                 BaseState * const getBaseState() const;

//                 std::vector<int> * const getInputs     () const;
//                 bool               const setInputs     (std::vector<int> const & inputs);
//                 bool               const addInput      (int const input);
//                 bool               const removeInput   (int const input);
//                 bool               const containsInput (int const input) const;
//         };

//         static int counter;

//         int         const   identifier = BaseState::counter++;
//         std::string const & name       = "";

//         std::vector<Jumper *> * jumpers = new std::vector<Jumper *>();
//         BaseState * defaultState = nullptr;



//         std::vector<int> * const call_get      (Jumper const & jumper, int              const useless_hardcoded) const;
//         bool               const call_set      (Jumper       & jumper, std::vector<int> const & inputs);
//         bool               const call_add      (Jumper       & jumper, int              const input);
//         bool               const call_remove   (Jumper       & jumper, int              const input);
//         bool               const call_contains (Jumper const & jumper, int              const input) const;

//         template<class PARAMETER, class RETURN> RETURN jumpers_iterator(BaseState const & baseState, PARAMETER input, RETURN defaultReturn, RETURN (*func)(BaseState const &, PARAMETER const &)) const;

//     public:
//         /* CONSTRUCTORS + DESTRUCTORS: */
//         BaseState  ();
//         BaseState  (std::string const name);
//         BaseState  (BaseState const & other);
//         ~BaseState ();


//         /* OPERATORS: */
//         void       operator=  (BaseState const & other);
//         bool const operator== (BaseState const & other) const;
//         bool const operator!= (BaseState const & other) const;


//         /* DefaultState ==> getters, setters, modifiers */
//         BaseState * const getDefaultState () const;
//         void              setDefaultState (BaseState * const defaultState);

//         /* Identifier ==> getters, setters, modifiers */
//         int const getIdentifier() const;
//         // Setter not available (const)

//         /* Name ==> getters, setters, modifiers */
//         std::string const getName() const;
//         // Setter not available (const)

//         /* Jumpers ==> getters, setters, modifiers */
//         // Getter not available
//         // Setter is private
//         bool const addJumper      (BaseState       & baseState, std::vector<int> & inputs);
//         bool const removeJumper   (BaseState const & baseState);
//         int  const containsJumper (BaseState const & baseState) const;

//         /* Jumper[i].inputs ==> getters, setters, modifiers */
//         std::vector<int> * const getInputs     (BaseState const & baseState) const;
//         bool               const setInputs     (BaseState const & baseState, std::vector<int> const & inputs);
//         bool               const addInput      (BaseState const & baseState, int const input);
//         bool               const removeInput   (BaseState const & baseState, int const input);
//         bool               const containsInput (BaseState const & baseState, int const input) const;

//         /* Jumper[i].baseState ==> getters, setters, modifiers */
//         // Getter not available (redundant)
//         // Setter not available (const)


//         /* FEATURES: */
//         BaseState * const transition(int const input) const;
// };

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
BaseState::BaseState(BaseState const & other) { return; }
void BaseState::operator=(BaseState const & other) { return; }



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



#endif