#ifndef SIM_CONSTANT_HPP_INCLUDED
#define SIM_CONSTANT_HPP_INCLUDED

class SimConstant : public SimBlockBase
{
protected:
    void Output(const Simulation& sim);
    void Initialization(const Simulation& sim);

public:
    SimConstant(const data_t&  cd, SimBase* parent);
    SimConstant(const double_t cd, SimBase* parent);

};

#endif // SIM_CONSTANT_HPP_INCLUDED
