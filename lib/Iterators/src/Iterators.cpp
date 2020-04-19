#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>

#define POSITIVE 1
#define NEGATIVE 0



template<class T> class Iterators {
    private:
        Iterators();
        Iterators(Iterators const & other);
        ~Iterators();

    public:
        static                   bool                     const contains    (std::vector<T> const &, T    const &);
        template<class U> static bool                     const contains    (std::vector<T> const &, U    const &, U const (* const)(T const &));
        static                   bool                     const comparator  (std::vector<T> const &, bool const (* const)(T const &, T const &));
        static                   bool                     const ormap       (std::vector<T> const &, bool const (* const)(T const &));
        static                   bool                     const andmap      (std::vector<T> const &, bool const (* const)(T const &));
        // static                   std::vector<T const *> * const filter      (std::vector<T> const & inputs, bool const (* const f)(T const &));
        static                   std::vector<T>         * const filter      (std::vector<T> const &, bool const (* const)(T const &));
        template<class U> static std::vector<U>         * const map         (std::vector<T> const &, U    const (* const)(T const &));
        static                   void                           apply       (std::vector<T> const &, void       (* const)(T const &));
        static                   T                      const & get         (std::vector<T> const &, int const);
        static                   void                           insert      (std::vector<T>       &, T    const &, int const);
        static                   bool                     const setInsert   (std::vector<T>       &, T    const &, int const);
        static                   bool                     const remove      (std::vector<T>       &, T    const &);
        template<class U> static std::vector<T>         * const remove      (std::vector<T> const &, U    const &, U const (* const)(T const &));
        static                   T                      * const accumulate  (std::vector<T> const &, void       (* const)(T &, T const &));
        static                   std::vector<T>         * const dereference (std::vector<T *> const &);
};



/*
 *  @param_1: std::vector<T> const &
 *      A reference to the constant T-template inputs being searched through.
 *      These inputs cannot be modified.
 *  @param_2: T const &
 *      A reference to the constant element being searched for in the @param_1 list.
 *      This input cannot be modified.
 *
 *  @requirement(s):
 *      The function pointer must be non-null; else false will be returned.
 *
 *  @returns:
 *      A constant boolean rvalue.
 *      True if @param_2 exists inside of @param_1; false otherwise.
 *
 *  @usage:
 *      To determine whether or not an element exists in the list.
*/
template<class T> bool const Iterators<T>::contains(std::vector<T> const & inputs, T const & t) {
    typename std::vector<T>::const_iterator const_itr(inputs.begin());
    for (; const_itr!=inputs.end(); ++const_itr) if ((*const_itr) == t) return true;

    return false;
}

/*
 *  @param_1: std::vector<T> const &
 *      A reference to the constant T-template inputs being searched through.
 *      These inputs cannot be modified.
 *  @param_2: bool const (* const f)(T const &, T const &)
 *      A function which takes in two references to constant T-template elements and returns a const boolean rvalue.
 *      The function, which serves as a comparator, is up to the user to implement.
 *      The function pointer cannot be modified.
 *
 *  @requirement(s):
 *      The function pointer must be non-null; else false will be returned.
 *
 *  @returns:
 *      A constant boolean rvalue.
 *      True if the passed in comparator is true for every comparison between successive elements; false otherwise.
 *      The lesser-indexed element will always be passed in first to the comparator.
 *
 *  @usage:
 *      Useful to assert that a sequence or pattern is followed by every successive element in the list.
 *      For example, can be used to assert that every successive element in a list of integers is greater than the previous.
 *      This would prove that the list of integers is sorted.
*/
template<class T> bool const Iterators<T>::comparator(std::vector<T> const & inputs, bool const (* const f)(T const &, T const &)) {
    if (!f) return false;

    typename std::vector<T>::const_iterator const_itr(inputs.begin());
    T const * t(&(*const_itr));
    ++const_itr;

    for (; const_itr!=inputs.end(); ++const_itr) {
        if (!f(*t,*const_itr)) return false;
        t = &(*const_itr);
    }
    
    return true;
}

/*
 *  @param_1: std::vector<T> const &
 *      A reference to the constant T-template inputs being searched through.
 *      These inputs cannot be modified.
 *  @param_2: bool const (* const f)(T const &)
 *      A function which takes in a reference to a constant T-template element and returns a const boolean rvalue.
 *      The function, which serves as a truth-validator, is up to the user to implement.
 *      The function pointer cannot be modified.
 *
 *  @requirement(s):
 *      The function pointer must be non-null; else false will be returned.
 *
 *  @returns:
 *      A constant boolean rvalue.
 *      True if the passed in function returns true for at least one element; false otherwise.
 *
 *  @usage:
 *      Useful to assert if a condition is met by at least one element in @param_1.
 *      For example, can be used to assert at least one element in a list of integers is even.
*/
template<class T> bool const Iterators<T>::ormap(std::vector<T> const & inputs, bool const (* const f)(T const &)) {
    if (!f) return false;

    typename std::vector<T>::const_iterator const_itr(inputs.begin());
    for (; const_itr!=inputs.end(); ++const_itr) if (f(*const_itr)) return true;

    return false;
}

/*
 *  @param_1: std::vector<T> const &
 *      A reference to the constant T-template inputs being searched through.
 *      These inputs cannot be modified.
 *  @param_2: bool const (* const f)(T const &)
 *      A function which takes in a reference to a constant T-template element and returns a const boolean rvalue.
 *      The function, which serves as a truth-validator, is up to the user to implement.
 *      The function pointer cannot be modified.
 *
 *  @requirement(s):
 *      The function pointer must be non-null; else false will be returned.
 *
 *  @returns:
 *      A constant boolean rvalue.
 *      True if the passed in function returns true for every element in @param_1; false otherwise.
 *
 *  @usage:
 *      Useful to assert if a condition is met by every element in @param_1.
 *      For example, can be used to assert every element in a list of integers is even.
*/
template<class T> bool const Iterators<T>::andmap(std::vector<T> const & inputs, bool const (* const f)(T const &)) {
    if (!f) return false;

    typename std::vector<T>::const_iterator const_itr(inputs.begin());
    for (; const_itr!=inputs.end(); ++const_itr) if (!f(*const_itr)) return false;

    return true;
}

// template<class T> std::vector<T const *> * const Iterators<T>::filter(std::vector<T> const & inputs, bool const (* const f)(T const &)) {
//     if (!f) return nullptr;

//     std::vector<T const *> * const ret = new std::vector<T const *>();
//     typename std::vector<T>::const_iterator const_itr(inputs.begin());

//     for (; const_itr!=inputs.end(); ++const_itr) if (f(*const_itr)) ret->push_back(&(*const_itr));

//     return ret->size() ? ret : nullptr;
// }

/*
 *  @param_1: std::vector<T> const &
 *      A reference to the constant T-template inputs being searched through.
 *      These inputs cannot be modified.
 *  @param_2: bool const (* const f)(T const &)
 *      A function which takes in a reference to a constant T-template element and returns a const boolean rvalue.
 *      The function, which serves as a filter, is up to the user to implement.
 *      The function pointer cannot be modified.
 *
 *  @requirement(s):
 *      The function pointer must be non-null; else a nullptr will be returned.
 *
 *  @returns:
 *      An rvalue constant pointer to a T-template vector.
 *      A new list is constructed containing every element in @param_1 which returned true after being passed into @param_2.
 *      Note that a new T-template vector is created and the copy-constructor will have to be executed everytime a new T-template element needs to be added.
 *      This may impact performance if the copy-constructor is a costly operation.
 *
 *  @usage:
 *      Useful to filter out certain elements in a given list that don't meet a given requirement.
 *      For example, can be used to filter out all of the non-even numbers in a list of integers, leaving a list of only even integers.
*/
template<class T> std::vector<T> * const Iterators<T>::filter(std::vector<T> const & inputs, bool const (* const f)(T const &)) {
    if (!f) return nullptr;

    std::vector<T> * const ret = new std::vector<T>();
    typename std::vector<T>::const_iterator const_itr(inputs.begin());
    for (; const_itr!=inputs.end(); ++const_itr) if (f(*const_itr)) ret->push_back(*const_itr);

    return ret->size() ? ret : nullptr;
}

/*
 *  @param_1: std::vector<T> const &
 *      A reference to the constant T-template inputs being searched through.
 *      These inputs cannot be modified.
 *  @param_2: U const (* const f)(T const &)
 *      A function which takes in a reference to a constant T-template element and returns an rvalue const U-template value.
 *      The function, which serves as a filter, is up to the user to implement.
 *      The function pointer cannot be modified.
 *
 *  @requirement(s):
 *      The function pointer must be non-null; else a nullptr will be returned.
 *
 *  @returns:
 *      An rvalue constant pointer to a T-template vector.
 *      A new list is constructed containing every element in @param_1 mapped to their new output after being invoked as an argument for @param_2.
 *      Note that a new U-template vector is created and the copy-constructor will have to be invoked for every T-template element that exists in @param_1.
 *      This may impact performance if the U-template copy-constructor is a costly operation.
 *
 *  @usage:
 *      Used to map certain elements from the pre-image to the image.
 *      For example, can be used to map a list of integers to their squares.
 *      Can also be used to map between different types/sets; i.e. integers -> strings, etc.
*/
template<class T> template<class U> std::vector<U> * const Iterators<T>::map(std::vector<T> const & inputs, U const (* const f)(T const &)) {
    if (!f) return nullptr;

    int const size = inputs.size();
    std::vector<U> * const ret = new std::vector<U>(size);
    typename std::vector<U>::iterator ret_itr(ret->begin());
    typename std::vector<T>::const_iterator const_itr(inputs.begin());

    for (; const_itr!=inputs.end(); ++const_itr, ++ret_itr) (*ret_itr) = f(*const_itr);

    return ret;
}

/*
 *  @param_1: std::vector<T> const &
 *      A reference to the constant T-template inputs being searched through.
 *      These inputs cannot be modified.
 *  @param_2: void (* const f)(T const &)
 *      A function which takes in a reference to a constant T-template element and returns void.
 *      The function is up to the user to implement.
 *      The function pointer cannot be modified.
 *
 *  @requirement(s):
 *      The function pointer must be non-null; else execution will be return without any application being performed.
 *
 *  @returns:
 *      Void.
 *
 *  @usage:
 *      Used to perform an operation/application on a list of numbers which doesn't require a return value.
 *      For example, can be used to print every element in the list.
*/
template<class T> void Iterators<T>::apply(std::vector<T> const & inputs, void (* const f)(T const &)) {
    if (!f) return;

    typename std::vector<T>::const_iterator const_itr(inputs.begin());
    for (; const_itr!=inputs.end(); ++const_itr) f(*const_itr);

    return;
}

/*
 *  @param_1:
 *  @param_2:
 *
 *  @requirement(s):
 *
 *  @returns:
 *
 *  @usage:
*/
template<class T> T const & Iterators<T>::get(std::vector<T> const & inputs, int const i) {
    int const x((i >= 0) ? POSITIVE : NEGATIVE);
    int const size(inputs.size());
    
    switch (x) {
        case NEGATIVE: {
            int const i_mod((-i-1) % (size+1));
            typename std::vector<T>::const_reverse_iterator r_itr(inputs.rbegin());
            std::advance(r_itr,i_mod);
            return (*r_itr);
        }
        case POSITIVE: {
            int const i_mod(i % (size+1));
            typename std::vector<T>::const_iterator itr(inputs.begin());
            std::advance(itr,i_mod);
            return (*itr);
        }
    }
}

/*
 *  @param_1: std::vector<T> &
 *      A reference to the constant T-template inputs being searched through.
 *      The list can be modified, although the elements inside the list themselves cannot be.
 *  @param_2: T const &
 *      The element to insert into @param_1.
 *      This element cannot be modified.
 *  @param_3: int const
 *      The index at which to insert the element into the list.
 *      Can be any positive or negative integer.
 *      This index cannot be modified.
 *
 *  @requirement(s):
 *      n/a.
 *
 *  @returns:
 *      Void.
 *
 *  @usage:
 *      Used to insert a T-template into a list.
 *      @param_3 can be any index, although the list is finite-sized.
 *      This is due to the index being modulated before being used.
 *      Negative indices are also allowed.
 *      An index of -1 indicates to insert at the very last position, -2 at the second last position, etc.
*/
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

/*
 *  @param_1: std::vector<T> &
 *      A reference to the constant T-template inputs being searched through.
 *      The list can be modified, although the elements inside the list themselves cannot be.
 *  @param_2: T const &
 *      The element to insert into @param_1.
 *      This element cannot be modified.
 *  @param_3: int const
 *      The index at which to insert the element into the list.
 *      Can be any positive or negative integer.
 *      This index cannot be modified.
 *
 *  @requirement(s):
 *      n/a.
 *
 *  @returns:
 *      An rvalue constant boolean.
 *      Returns true if the element was successfully inserted; false otherwise.
 *
 *  @usage:
 *      Used to insert a T-template into a list, if and only if it does not exist in the list already.
 *      If the element already exists, execution will terminate and false will be returned.
 *      Comparison is made by calling the T.operator==(T const &) method.
 *      @param_3 can be any index, although the list is finite-sized.
 *      This is due to the index being modulated before being used.
 *      Negative indices are also allowed.
 *      An index of -1 indicates to insert at the very last position, -2 at the second last position, etc.
*/
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

/*
 *  @param_1: std::vector<T> &
 *      A reference to the constant T-template inputs being searched through.
 *      The list can be modified, although the elements inside the list themselves cannot be.
 *  @param_2: T const &
 *      The element to insert into @param_1.
 *      This element cannot be modified.
 *
 *  @requirement(s):
 *      n/a.
 *
 *  @returns:
 *      Void.
 *
 *  @usage:
 *      Used to remove all the elements in @param_1 that equal @param_2.
 *      In order to make the comparison, is T.operator==(T const &) is invoked.
*/
template<class T> bool const Iterators<T>::remove(std::vector<T> & inputs, T const & t) {
    typename std::vector<T>::iterator ender(inputs.end());
    typename std::vector<T>::iterator temp(std::remove(inputs.begin(),ender,t));

    if (temp != ender) {
        inputs.erase(temp,ender);
        return true;
    }

    return false;
}

/*
 *  @param_1: std::vector<T> &
 *      A reference to the constant T-template inputs being searched through.
 *      The list can be modified, although the elements inside the list themselves cannot be.
 *  @param_2: void (* const f)(T &, T const &)
 *      A constant pointer to a function which takes two objects of type T and performs an operation on them and stores it in the first object.
 *
 *  @requirement(s):
 *      n/a.
 *
 *  @returns:
 *      An rvalue constant pointer to an object of type T.
 *
 *  @usage:
 *      Useful to compute an aggregated expression from a list of T-templated objects.
 *      For example, can be used to compute the sum of a list of integers.
*/
template<class T> T * const Iterators<T>::accumulate(std::vector<T> const & inputs, void (* const f)(T &, T const &)) {
    if ((!f) || (inputs.size() <= 1)) return nullptr;

    typename std::vector<T>::const_iterator const_itr(inputs.begin());
    T * t = new T(*const_itr);
    ++const_itr;
    for (; const_itr!=inputs.end(); ++const_itr) f(*t,*const_itr);

    return *t;
}

/*
 *  @param_1: std::vector<T *> const &
 *      A constant reference to a std::vector of pointers to objects of type T.
 *      The list cannot be modified.
 *
 *  @requirement(s):
 *      n/a.
 *
 *  @returns:
 *      A constant rvalue pointer to a newly constructed list of objects of type T.
 *      This list is exactly the same as the inputted list, but each pointer has been dereferenced.
 *      Note that, since the pointers have to be dereferenced, the copy-constructor has to be invoked n-number of times, where n is the size of the input list.
 *
 *  @usage:
 *      Used to dereference a list of pointers to T-type objects to a list of T-type objects.
*/
template<class T> std::vector<T> * const Iterators<T>::dereference(std::vector<T *> const & inputs) {
    std::vector<T> * const ret = new std::vector<T>();
    typename std::vector<T *>::const_iterator const_itr(inputs.begin());

    for (; const_itr!=inputs.end(); ++const_itr) ret->push_back(**const_itr);

    return ret;
}





template<class T> template<class U> bool const Iterators<T>::contains(std::vector<T> const & inputs, U const & u, U const (* const f)(T const &)) {
    std::vector<U> * const transformed = Iterators<T>::map<U>(inputs,f);
    return Iterators<U *>::contains(*transformed,u);
}
/*
 *  @param_1: std::vector<T> const &
 *      A constant reference to a list of T-templated inputs.
 *      This list cannot be modified.
 *  @param_2: U const &
 *      A constant element of type U.
 *      This element cannot be modified.
 *  @param_3: U const (* const f)(T const &)
 *      A constant pointer to a function that takes in an object of type T and returns an object of type U.
 *      
 *
 *  @requirement(s):
 *      n/a.
 *
 *  @returns:
 *      An rvalue pointer to a new T-templated std::vector.
 *      The new std::vector will contain all elements except the elements in @param_1 that, once passed into a function, returned a value that was equal to @param_2.
 *      Note that, since a new list is being constructed, the copy constructor has to be invoked for every added element for whatever data type was passed in.
 *
 *  @usage:
 *      The comparison of the returned object and @param_2 is done using T.operator==(T const &).
 *      For example, consider an object data type, A, that contains a pointer to another object data type, B (where B could be A).
 *      A use case could be to remove all the A objects inside of a std::vector that contain a pointer to a particular B instance.
 *      The list of A objects can be passed in as @param_1, the B object pointer as @param_2, and a function that can properly dereference an A object to retrieve its B pointer as @param_3.
 *      After evaluation of this function, all the A objects in @param_1 that point @param_2 would be removed.
*/
template<class T> template<class U> std::vector<T> * const Iterators<T>::remove(std::vector<T> const & inputs, U const & u, U const (* const f)(T const &)) {
    // if (!f) return;

    // std::vector<T *> * const ret = new std::vector<T *>();
    // typename std::vector<T>::const_iterator
    

    // typename std::vector<T>::iterator itr(inputs.begin());
    // for (; itr!=inputs.end(); ++itr) if (u == *f(*itr)) {
    //     inputs.erase(itr);
    //     --itr;
    // }

    // return;
}