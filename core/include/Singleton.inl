template <class Derived>
Derived& Singleton<Derived>::instance() {
    if (Singleton<Derived>::instance_ == nullptr) Singleton<Derived>::instance_ = new Derived();
    return *Singleton<Derived>::instance_;
}

template <class Derived>
Derived* Singleton<Derived>::instance_ = nullptr;