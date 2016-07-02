#ifndef SIM_BLOCKBASE_IMPL_HPP_INCLUDED
#define SIM_BLOCKBASE_IMPL_HPP_INCLUDED

struct SimBlockBase::SimBlockBasePrivate
{
    typedef std::shared_ptr<data_t>     data_ptr;
    typedef std::vector<data_ptr>       data_vec;
    typedef std::shared_ptr<state_t>    state_ptr;

    state_ptr   x;
    state_ptr   dx;
    state_ptr   x0;
    state_ptr   dx0;

    data_vec    y0;
};

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void SimBlockBase::Output(const Simulation& sim)
{

}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void SimBlockBase::Update(const Simulation& sim)
{

}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void SimBlockBase::Derivative(const Simulation& sim)
{

}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void SimBlockBase::Terminate(const Simulation& sim)
{

}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void SimBlockBase::Start(const Simulation& sim)
{

}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void SimBlockBase::Initialization(const Simulation& sim)
{
    if ((d_ptr->x != nullptr) && (d_ptr->x0 != nullptr))
    {
        d_ptr->x = d_ptr->x0;
    }

    if ((d_ptr->dx != nullptr) && (d_ptr->dx0 != nullptr))
    {
        d_ptr->dx = d_ptr->dx0;
    }

    const u32_t ny0 = d_ptr->y0.size();
    for (u32_t id = 0; id < ny0; ++id)
    {
        SimBlockBasePrivate::data_ptr y0 = d_ptr->y0[id];
        if (y0 != nullptr)
        {
            GetOutputPort(id)->WriteData(*y0);
        }
    }
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
bool SimBlockBase::IsStateless() const
{
    return d_ptr->x == nullptr || d_ptr->x->empty();
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
const data_t* SimBlockBase::GetInitOutput(const u32_t portID) const
{
    if (portID < d_ptr->y0.size())
    {
        return d_ptr->y0[portID].get();
    }

    return nullptr;
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
const state_t* SimBlockBase::GetInitState() const
{
    return (d_ptr->x0 == nullptr) ? nullptr : d_ptr->x0.get();
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void SimBlockBase::SetInitOutput(const u32_t portID, const data_t& y0)
{
    SimPortBase* pp = GetOutputPort(portID);
    if (pp == nullptr)
    {
        return ;
    }

/*
    const bool is_dim_match = \
        (y0.n_rows == pp->GetPortDim1()) &&
        (y0.n_cols == pp->GetPortDim2());

    if (is_dim_match == true)
    {
        d_ptr->y0[portID] = std::make_shared<data_t>(y0);
    }
*/
    d_ptr->y0[portID] = std::make_shared<data_t>(y0);
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void SimBlockBase::SetInitDState(const state_t& dx0)
{
    d_ptr->dx  = std::make_shared<state_t>(dx0);
    d_ptr->dx0 = std::make_shared<state_t>(dx0);
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void SimBlockBase::SetInitState(const state_t& x0)
{
    d_ptr->x  = std::make_shared<state_t>(x0);
    d_ptr->x0 = std::make_shared<state_t>(x0);
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
 SimBlockBase::SimBlockBase(const string_t& name, SimBase* parent)
 : SimSingleRateBlock(0.0, 0.0, name, parent)
{
    xsim_extra_debug_sigprint_this(this);
    Init();
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
 SimBlockBase::~SimBlockBase()
{
    xsim_extra_debug_sigprint_this(this);
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void SimBlockBase::Init()
{
    d_ptr = std::make_shared<SimBlockBasePrivate>();
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void SimBlockBase::AddOutputPort(u32_t dr, u32_t dc)
{
    d_ptr->y0.push_back(std::make_shared<data_t>());
    SimIOBlock::AddOutputPort(dr, dc);
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void SimBlockBase::AddInputPort(u32_t dr, u32_t dc)
{
    SimIOBlock::AddInputPort(dr, dc);
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */

void SimBlockBase::NotifyReady(SimPortBase* port)
{
    if (port)
    {
        const u32_t id = FindInputPort(port);
        if (id != XSIM_INDEX_INVALID)
        {
            SetInPortReady(id, true);
        }
    }
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void SimBlockBase::DoStep(const Simulation& sim)
{
    if (IsContinuous() && !IsStateless())
    {
        DoStepCont(sim);
    }
    else
    {
        Update(sim);
    }
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void SimBlockBase::DoStepCont(const Simulation& sim)
{
    static auto system = [&](const state_t& x, state_t& dxdt, const double_t t)
    {
        *(d_ptr->dx) = dxdt;
        Derivative(sim);
    };

    sim.GetSolver()(std::ref(system), *(d_ptr->x), sim.GetSimTimeCurr(), sim.GetSimTimeStep());
}



/** @brief (one liner)
  *
  * (documentation goes here)
  */
void Connect(SimBlockBase& srcBlock, u32_t oportID, SimBlockBase& dstBlock, u32_t iportID)
{
    SimPortBase* srcPort = srcBlock.GetOutputPort(oportID);
    SimPortBase* dstPort = dstBlock.GetInputPort(iportID);
    if (srcPort && dstPort)
    {
        Connect(*srcPort, *dstPort);
    }
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void Disconnect(SimBlockBase& srcBlock, u32_t oportID, SimBlockBase& dstBlock, u32_t iportID)
{
    SimPortBase* srcPort = srcBlock.GetOutputPort(oportID);
    SimPortBase* dstPort = dstBlock.GetInputPort(iportID);
    if (srcPort && dstPort)
    {
        Disconnect(*srcPort, *dstPort);
    }
}


#endif // SIM_BLOCKBASE_IMPL_HPP_INCLUDED
