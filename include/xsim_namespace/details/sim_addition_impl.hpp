#ifndef SIM_ADDITION_IMPL_HPP_INCLUDED
#define SIM_ADDITION_IMPL_HPP_INCLUDED

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void SimAddition::Output(const Simulation& sim)
{
    data_t& out = GetOutBuffer(0);

    const u32_t n = GetInputPortNum();
    switch (n)
    {
        case 2: out = GetInBuffer(0) + GetInBuffer(1); break;
        case 3: out = GetInBuffer(0) + GetInBuffer(1) + GetInBuffer(2); break;
        case 4: out = GetInBuffer(0) + GetInBuffer(1) + GetInBuffer(2) + GetInBuffer(3); break;
        case 5: out = GetInBuffer(0) + GetInBuffer(1) + GetInBuffer(2) + GetInBuffer(3) + GetInBuffer(4); break;
        case 6: out = GetInBuffer(0) + GetInBuffer(1) + GetInBuffer(2) + GetInBuffer(3) + GetInBuffer(4) + GetInBuffer(5); break;
        case 7: out = GetInBuffer(0) + GetInBuffer(1) + GetInBuffer(2) + GetInBuffer(3) + GetInBuffer(4) + GetInBuffer(5) + GetInBuffer(6); break;
        default:
            out = GetInBuffer(0) + GetInBuffer(1);
            for (u32_t i = 2; i < n; ++i)
            {
                out += GetInBuffer(i);
            }
            break;
    }

    NotifyOutputReady(0);
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void SimAddition::Init(u32_t n)
{
    AddOutputPort(0, 0);
    for (u32_t i = 0; i < n; ++i)
    {
        AddInputPort(0, 0);
    }
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
 SimAddition::SimAddition(u32_t n_inport, SimBase* parent)
 : SimBlockBase("Addition", parent)
{
    if (n_inport < 2)
    {
        n_inport = 2;
    }

    Init(n_inport);
}



#endif // SIM_ADDITION_IMPL_HPP_INCLUDED
