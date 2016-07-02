#ifndef SIM_MULTIPLY_HPP_INCLUDED
#define SIM_MULTIPLY_HPP_INCLUDED

class SimMultiply : public SimBlockBase
{
public:
    enum MulType
    {
        SCALAR,     //dot product
        VECTOR,     //vector product
    };

public:
    SimMultiply(u32_t n_inport, MulType mul_type, SimBase* parent);

protected:
    void Init(u32_t n_inport);
    void Output(const Simulation& sim);

private:
    void DotMul(const Simulation &sim);
    void VecMul(const Simulation &sim);

private:
    MulType _mul_type;
};


#endif // SIM_MULTIPLY_HPP_INCLUDED
