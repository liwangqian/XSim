#ifndef SIM_IOBLOCK_IMPL_HPP_INCLUDED
#define SIM_IOBLOCK_IMPL_HPP_INCLUDED

struct SimIOBlock::SimIOBlockPrivate
{
    typedef std::vector<SimPortBase*>       port_vector;
    typedef std::bitset<XSIM_MAX_SUBOBJS>   port_state;

    port_vector inPorts;
    port_vector outPorts;

    port_state  inPortState; /*! 输入端口的数据状态 */
};

/** @brief (one liner)
  *
  * (documentation goes here)
  */
 SimIOBlock::SimIOBlock(const string_t& name, SimBase* parent)
 : SimBase(name, parent)
{
    Init();
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void SimIOBlock::AddOutputPort(u32_t dr, u32_t dc)
{
    const u32_t id = d_ptr->outPorts.size();

    xsim_extra_debug_sigprint_this(this);
    xsim_extra_debug_sigprint(id);

    d_ptr->outPorts.push_back(new SimOutputPort(id, dr, dc, this));
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void SimIOBlock::AddInputPort(u32_t dr, u32_t dc)
{
    const u32_t id = d_ptr->inPorts.size();
    xsim_extra_debug_sigprint_this(this);
    xsim_extra_debug_sigprint(id);
    d_ptr->inPorts.push_back(new SimInputPort(id, dr, dc, this));
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void SimIOBlock::Init()
{
    d_ptr = std::make_shared<SimIOBlockPrivate>();
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
SimPortBase* SimIOBlock::GetOutputPort(u32_t id)
{
    if (id < d_ptr->outPorts.size())
    {
        return d_ptr->outPorts[id];
    }
    else
    {
        return nullptr;
    }
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
SimPortBase* SimIOBlock::GetInputPort(u32_t id)
{
    if (id < d_ptr->inPorts.size())
    {
        return d_ptr->inPorts[id];
    }
    else
    {
        return nullptr;
    }
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
u32_t SimIOBlock::GetInputPortNum() const
{
    return d_ptr->inPorts.size();
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
u32_t SimIOBlock::GetOutputPortNum() const
{
    return d_ptr->outPorts.size();
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void SimIOBlock::ResetInPortReadyState()
{
    d_ptr->inPortState.reset();
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void SimIOBlock::SetInPortReady(u32_t id, bool ready)
{
    if (ready)
        d_ptr->inPortState.set(id);
    else
        d_ptr->inPortState.reset(id);
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
bool SimIOBlock::IsReady() const
{
    return d_ptr->inPortState.count() == GetInputPortNum();
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
u32_t SimIOBlock::FindOutputPort(const SimPortBase* port) const
{
    u32_t index = 0;
    for (auto ip : d_ptr->outPorts)
    {
        if (ip == port)
        {
            return index;
        }
        index++;
    }

    return XSIM_INDEX_INVALID;
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
u32_t SimIOBlock::FindInputPort(const SimPortBase* port) const
{
    u32_t index = 0;
    for (auto ip : d_ptr->inPorts)
    {
        if (ip == port)
        {
            return index;
        }
        index++;
    }

    return XSIM_INDEX_INVALID;
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void SimIOBlock::WriteData(u32_t id, const data_t& d)
{
    d_ptr->outPorts[id]->WriteData(d);
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void SimIOBlock::ReadData(u32_t id, data_t& d)
{
    d_ptr->inPorts[id]->ReadData(d);
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
const data_t & SimIOBlock::GetInBuffer(u32_t id) const
{
    return static_cast<SimInputPort*>(d_ptr->inPorts[id])->GetInBuffer();
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
data_t & SimIOBlock::GetOutBuffer(u32_t id)
{
    //using namespace std;
    //cout << static_cast<SimOutputPort*>(d_ptr->outPorts[id])->GetOutBuffer() << endl;
    return static_cast<SimOutputPort*>(d_ptr->outPorts[id])->GetOutBuffer();
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void SimIOBlock::NotifyOutputReady(u32_t id) const
{
    static_cast<SimOutputPort*>(d_ptr->outPorts[id])->NotifyReady();
}



#endif // SIM_IOBLOCK_IMPL_HPP_INCLUDED
