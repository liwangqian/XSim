#ifndef SIM_OBSERVER_HPP_INCLUDED
#define SIM_OBSERVER_HPP_INCLUDED

class SimObserver : public SimBlockBase
{
public:
    typedef std::function<void(const double_t, const data_t&)> Functor;

public:
    SimObserver(SimBase *parent);
    SimObserver(const Functor& fn, SimBase *parent);
    SimObserver(const char* fileName, SimBase* parent);

protected:
    void Output(const Simulation& sim);

private:
    Functor _fn;
};

#endif // SIM_OBSERVER_HPP_INCLUDED
