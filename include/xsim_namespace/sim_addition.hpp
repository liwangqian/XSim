#ifndef SIM_ADDITION_HPP_INCLUDED
#define SIM_ADDITION_HPP_INCLUDED

class SimAddition : public SimBlockBase
{
public:
    SimAddition(u32_t n_inport, SimBase* parent);

protected:
    void Init(u32_t n);
    void Output(const Simulation& sim);
};

#endif // SIM_ADDITION_HPP_INCLUDED
