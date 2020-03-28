#include <stdlib.h>
#include <stdio.h>
#include <vector>

#define POSITIVE 1
#define NEGATIVE 0



template<class T> class Iterators {
    private:
        Iterators();
        Iterators(Iterators const & other);
        ~Iterators();

    public:
        static                   bool                     const contains    (std::vector<T> const & inputs, T    const & t);
        template<class U> static bool                     const contains    (std::vector<T> const & inputs, U    const & u, U * const (* const f)(T const &));
        static                   bool                     const comparator  (std::vector<T> const & inputs, bool const (* const f)(T const &, T const &));
        static                   bool                     const ormap       (std::vector<T> const & inputs, bool const (* const f)(T const &));
        static                   bool                     const andmap      (std::vector<T> const & inputs, bool const (* const f)(T const &));
        static                   std::vector<T const *> * const filter      (std::vector<T> const & inputs, bool const (* const f)(T const &));
        static                   std::vector<T *>       * const newFilter   (std::vector<T> const & inputs, bool const (* const f)(T const &));
        template<class U> static std::vector<U *>       * const map         (std::vector<T> const & inputs, U  * const (* const f)(T const &));
        static                   void                           apply       (std::vector<T> const & inputs, void       (* const f)(T const &));
        static                   void                           insert      (std::vector<T>       & inputs, T    const & t, int const i);
        static                   bool                     const setInsert   (std::vector<T>       & inputs, T    const & t, int const i);
        static                   void                           remove      (std::vector<T>       & inputs, T    const & t);
        template<class U> static void                           remove      (std::vector<T> const & inputs, U    const & u, U * const (* const f)(T const &));
        static                   T                      * const accumulate  (std::vector<T> const & inputs, void       (* const f)(T &, T const &));
        static                   std::vector<T>         * const dereference (std::vector<T *> const & inputs);
};



template<class T> bool const Iterators<T>::contains(std::vector<T> const & inputs, T const & t) {
    typename std::vector<T>::const_iterator const_itr(inputs.begin());
    for (; const_itr!=inputs.end(); ++const_itr) if ((*const_itr) == t) return true;

    return false;
}
template<class T> template<class U> bool const Iterators<T>::contains(std::vector<T> const & inputs, U const & u, U * const (* const f)(T const &)) {
    std::vector<U *> * const transformed = Iterators<T>::map<U>(inputs,f);
    return Iterators<U *>::contains(*transformed,&u);
}
template<class T> bool const Iterators<T>::comparator(std::vector<T> const & inputs, bool const (* const f)(T const &, T const &)) {
    if (!f) return false;

    typename std::vector<T>::const_iterator const_itr(inputs.begin());
    T const * t = &(*const_itr);
    ++const_itr;

    for (; const_itr!=inputs.end(); ++const_itr) if (!f(*t,*const_itr)) return false;
    
    return true;
}
template<class T> bool const Iterators<T>::ormap(std::vector<T> const & inputs, bool const (* const f)(T const &)) {
    if (!f) return false;

    typename std::vector<T>::const_iterator const_itr(inputs.begin());
    for (; const_itr!=inputs.end(); ++const_itr) if (f(*const_itr)) return true;

    return false;
}
template<class T> bool const Iterators<T>::andmap(std::vector<T> const & inputs, bool const (* const f)(T const &)) {
    if (!f) return false;

    typename std::vector<T>::const_iterator const_itr(inputs.begin());
    for (; const_itr!=inputs.end(); ++const_itr) if (!f(*const_itr)) return false;

    return true;
}
template<class T> std::vector<T const *> * const Iterators<T>::filter(std::vector<T> const & inputs, bool const (* const f)(T const &)) {
    if (!f) return nullptr;

    std::vector<T const *> * const ret = new std::vector<T const *>();
    typename std::vector<T>::const_iterator const_itr(inputs.begin());

    for (; const_itr!=inputs.end(); ++const_itr) if (f(*const_itr)) ret->push_back(&(*const_itr));

    return ret->size() ? ret : nullptr;
}
template<class T> std::vector<T *> * const Iterators<T>::newFilter(std::vector<T> const & inputs, bool const (* const f)(T const &)) {
    if (!f) return nullptr;

    std::vector<T *> * const ret = new std::vector<T *>();
    typename std::vector<T>::const_iterator const_itr(inputs.begin());

    for (; const_itr!=inputs.end(); ++const_itr) if (f(*const_itr)) {
        T * const filtered_input = new T(*const_itr);
        ret->push_back(filtered_input);
    }

    return ret->size() ? ret : nullptr;
}
template<class T> template<class U> std::vector<U *> * const Iterators<T>::map(std::vector<T> const & inputs, U * const (* const f)(T const &)) {
    if (!f) return nullptr;

    int const size = inputs.size();
    std::vector<U *> * const ret = new std::vector<U *>(size);
    typename std::vector<U *>::iterator ret_itr(ret->begin());
    typename std::vector<T>::const_iterator const_itr(inputs.begin());

    for (; const_itr!=inputs.end(); ++const_itr, ++ret_itr) (*ret_itr) = f(*const_itr);

    return ret;
}
template<class T> void Iterators<T>::apply(std::vector<T> const & inputs, void (* const f)(T const &)) {
    if (!f) return;

    typename std::vector<T>::const_iterator const_itr(inputs.begin());
    for (; const_itr!=inputs.end(); ++const_itr) f(*const_itr);

    return;
}
template<class T> void Iterators<T>::insert(std::vector<T> & inputs, T const & t, int const i) {
    int const x = ((i >= 0) ? POSITIVE : NEGATIVE);
    int const size = inputs.size();
    
    switch (x) {
        case NEGATIVE: {
            int const i_mod = (((-i) - 1) % (size + 1));
            typename std::vector<T>::reverse_iterator r_itr(inputs.rbegin());
            std::advance(r_itr,i_mod);
            inputs.insert(r_itr.base(), t);
            return;
        }
        case POSITIVE: {
            int const i_mod = (i % (size + 1));
            typename std::vector<T>::iterator itr(inputs.begin());
            std::advance(itr,i_mod);
            inputs.insert(itr,t);
            return;
        }
        default: return;
    }
}
template<class T> bool const Iterators<T>::setInsert(std::vector<T> & inputs, T const & t, int const i) {
    if (Iterators<T>::contains(inputs, t)) return false;

    int const x = ((i >= 0) ? POSITIVE : NEGATIVE);
    int const size = inputs.size();
    
    switch (x) {
        case NEGATIVE: {
            int const i_mod = (((-i) - 1) % (size + 1));
            typename std::vector<T>::reverse_iterator r_itr(inputs.rbegin());
            std::advance(r_itr,i_mod);
            inputs.insert(r_itr.base(), t);
            return true;
        }
        case POSITIVE: {
            int const i_mod = (i % (size + 1));
            typename std::vector<T>::iterator itr(inputs.begin());
            std::advance(itr,i_mod);
            inputs.insert(itr,t);
            return true;
        }
        default: return false;
    }
}
template<class T> void Iterators<T>::remove(std::vector<T> & inputs, T const & t) {
    // typename std::vector<T>::iterator itr(inputs.begin());
    // for (; itr!=inputs.end(); ++itr) if ((*itr) == t) {
    //     inputs.erase(itr);
    //     --itr;
    // }

    // return;

    std::remove(inputs.begin(), inputs.end(), t);
    return;
}
template<class T> template<class U> void Iterators<T>::remove(std::vector<T> const & inputs, U const & u, U * const (* const f)(T const &)) {
    typename std::vector<T>::iterator itr(inputs.begin());
    for (; itr!=inputs.end(); ++itr) if ((f(*itr))->operator==(u)) {
        inputs.erase(itr);
        --itr;
    }

    return;
}
template<class T> T * const Iterators<T>::accumulate(std::vector<T> const & inputs, void (* const f)(T &, T const &)) {
    if ((!f) || (inputs.size() <= 1)) return nullptr;

    typename std::vector<T>::const_iterator const_itr(inputs.begin());
    T * t = new T(*const_itr);
    ++const_itr;
    for (; const_itr!=inputs.end(); ++const_itr) f(*t,*const_itr);

    return t;
}
template<class T> std::vector<T> * const Iterators<T>::dereference(std::vector<T *> const & inputs) {
    std::vector<T> * const ret = new std::vector<T>();
    typename std::vector<T *>::const_iterator const_itr(inputs.begin());

    for (; const_itr!=inputs.end(); ++const_itr) ret->push_back(**const_itr);

    return ret;
}