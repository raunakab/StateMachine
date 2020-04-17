#ifndef JUMPER_H
#define JUMPER_H

class BaseState::Jumper {
    private:
        Jumper();
        Jumper(BaseState::Jumper const &);
        void operator=(BaseState::Jumper const &);

        std::string const action = "";
        std::shared_ptr<BaseState> const baseState = nullptr;

    public:
        Jumper(std::string const &, std::shared_ptr<BaseState> const &);
        ~Jumper();

        bool const operator==(BaseState::Jumper const &) const;
        bool const operator!=(BaseState::Jumper const &) const;

        std::string const getAction() const;
        std::shared_ptr<BaseState> const getBaseState() const;
};

#endif