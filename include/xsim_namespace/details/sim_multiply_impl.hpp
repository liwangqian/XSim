#ifndef SIM_MULTIPLY_IMPL_HPP_INCLUDED
#define SIM_MULTIPLY_IMPL_HPP_INCLUDED

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void SimMultiply::VecMul(const Simulation& sim)
{
    data_t& out = GetOutBuffer(0);

    const u32_t n_inputs = GetInputPortNum();

    switch (n_inputs)
    {
        case 2: out = GetInBuffer(0) * GetInBuffer(1); break;
        case 3: out = GetInBuffer(0) * GetInBuffer(1) * GetInBuffer(2); break;
        case 4: out = GetInBuffer(0) * GetInBuffer(1) * GetInBuffer(2) * GetInBuffer(3); break;
        case 5: out = GetInBuffer(0) * GetInBuffer(1) * GetInBuffer(2) * GetInBuffer(3) * GetInBuffer(4); break;
        case 6: out = GetInBuffer(0) * GetInBuffer(1) * GetInBuffer(2) * GetInBuffer(3) * GetInBuffer(4) * GetInBuffer(5); break;
        case 7: out = GetInBuffer(0) * GetInBuffer(1) * GetInBuffer(2) * GetInBuffer(3) * GetInBuffer(4) * GetInBuffer(5) * GetInBuffer(6); break;
        default:
            out = GetInBuffer(0) * GetInBuffer(1);
            for (u32_t i = 2; i < n_inputs; ++i)
            {
                out *= GetInBuffer(i);
            }
            break;
    }
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void SimMultiply::DotMul(const Simulation& sim)
{
    data_t& out = GetOutBuffer(0);

    const u32_t n_inputs = GetInputPortNum();

    switch (n_inputs)
    {
        case 2: out = GetInBuffer(0) % GetInBuffer(1); break;
        case 3: out = GetInBuffer(0) % GetInBuffer(1) % GetInBuffer(2); break;
        case 4: out = GetInBuffer(0) % GetInBuffer(1) % GetInBuffer(2) % GetInBuffer(3); break;
        case 5: out = GetInBuffer(0) % GetInBuffer(1) % GetInBuffer(2) % GetInBuffer(3) % GetInBuffer(4); break;
        case 6: out = GetInBuffer(0) % GetInBuffer(1) % GetInBuffer(2) % GetInBuffer(3) % GetInBuffer(4) % GetInBuffer(5); break;
        case 7: out = GetInBuffer(0) % GetInBuffer(1) % GetInBuffer(2) % GetInBuffer(3) % GetInBuffer(4) % GetInBuffer(5) % GetInBuffer(6); break;
        default:
            out = GetInBuffer(0) % GetInBuffer(1);
            for (u32_t i = 2; i < n_inputs; ++i)
            {
                out %= GetInBuffer(i);
            }
            break;
    }
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void SimMultiply::Output(const Simulation& sim)
{
    if (_mul_type == SCALAR)
    {
        DotMul(sim);
    }
    else
    {
        VecMul(sim);
    }

    NotifyOutputReady(0);
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void SimMultiply::Init(u32_t n_inport)
{
    AddOutputPort(0, 0);
    for (u32_t i = 0; i < n_inport; ++i)
    {
        AddInputPort(0, 0);
    }
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
 SimMultiply::SimMultiply(u32_t n_inport, MulType mul_type, SimBase* parent)
 : SimBlockBase("Multiply", parent)
 , _mul_type(mul_type)
{
    if (n_inport < 2)
    {
        n_inport = 2;
    }

    Init(n_inport);
}



#endif // SIM_MULTIPLY_IMPL_HPP_INCLUDED
