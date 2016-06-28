#ifndef SINGLETON_H
#define SINGLETON_H

template <class Derived>
class Singleton {
public:
    static Derived& instance();
private:
    static Derived* instance_;
};

#include "Singleton.inl"

#endif