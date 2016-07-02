#ifndef SIM_PORTS_IMPL_HPP_INCLUDED
#define SIM_PORTS_IMPL_HPP_INCLUDED

struct SimPortBase::SimPortBasePrivate
{
    u32_t   id;
    u32_t   dr;
    u32_t   dc;
};

/** @brief (one liner)
  *
  * (documentation goes here)
  */
 SimPortBase::SimPortBase(u32_t id, u32_t dr, u32_t dc, const string_t& name, SimBase* parent)
 : SimBase(name, parent), SimIODevice()
{
    Init(id, dr, dc);
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
 SimPortBase::~SimPortBase()
{
    xsim_extra_debug_sigprint_this(this);
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
u32_t SimPortBase::GetPortDim2() const
{
    return d_ptr->dc;
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
u32_t SimPortBase::GetPortDim1() const
{
    return d_ptr->dr;
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void SimPortBase::SetPortDim(u32_t dr, u32_t dc)
{
    d_ptr->dr = dr;
    d_ptr->dc = dc;
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void SimPortBase::Init(u32_t id, u32_t dr, u32_t dc)
{
    d_ptr = std::make_shared<SimPortBasePrivate>();
    d_ptr->dr = dr;
    d_ptr->dc = dc;
    d_ptr->id = id;
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void SimPortBase::ConnectTo(SimPortBase& port)
{
    xsim_extra_debug_check
    (
       (d_ptr->dr > 0 && d_ptr->dr != port.GetPortDim1()) ||
       (d_ptr->dc > 0 && d_ptr->dc != port.GetPortDim2()),
       "[ConnectTo] port dimension mismatch!"
    );
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void SimPortBase::DisconnectFrom(SimPortBase& port)
{
}


struct SimInputPort::SimInputPortPrivate
{
    SimPortBase* connectedPort;
    bool         readyRead;
};

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void SimInputPort::SetReadyRead(bool ready)
{
    d_ptr->readyRead = ready;
    NotifyReady();
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void SimInputPort::ReadData(data_t& data)
{
    if (d_ptr->connectedPort)
        d_ptr->connectedPort->ReadData(data);

    d_ptr->readyRead = false;
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
bool SimInputPort::ReadyRead() const
{
    return d_ptr->readyRead;
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
 SimInputPort::SimInputPort(u32_t id, u32_t dr, u32_t dc, SimBase* parent)
 : SimPortBase(id, dr, dc, "", parent)
{
    xsim_extra_debug_sigprint_this(this);
    Init();
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
 SimInputPort::~SimInputPort()
{
    xsim_extra_debug_sigprint_this(this);
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void SimInputPort::NotifyReady()
{
    SimBlockBase* sb = static_cast<SimBlockBase*>(GetParent());
    if (sb != nullptr)
    {
        sb->NotifyReady(this);
    }
}
/** @brief (one liner)
  *
  * (documentation goes here)
  */
const data_t & SimInputPort::GetInBuffer() const
{
    xsim_extra_debug_check
    (
        d_ptr->connectedPort == nullptr,
        "[GetInBuffer] The port is unconnected!"
    );
    return static_cast<SimOutputPort*>(d_ptr->connectedPort)->GetOutBuffer();
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
bool SimInputPort::Connected() const
{
    return d_ptr->connectedPort != nullptr;
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void SimInputPort::Init()
{
    d_ptr = std::make_shared<SimInputPortPrivate>();
    d_ptr->readyRead = false;
    d_ptr->connectedPort = nullptr;
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void SimInputPort::DisconnectFrom(SimPortBase& port)
{
    if (d_ptr->connectedPort == &port)
    {
        d_ptr->connectedPort = nullptr;
    }
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void SimInputPort::ConnectTo(SimPortBase& port)
{
    if (d_ptr->connectedPort == &port)
    {
        return;
    }

    SimPortBase::ConnectTo(port);

    if (d_ptr->connectedPort)
    {
        Disconnect(*this, port);
    }

    d_ptr->connectedPort = &port;
}


struct SimOutputPort::SimOutputPortPrivate
{
    std::list<SimPortBase*> connectedPorts;
    data_t                  buf;
};

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void SimOutputPort::WriteData(const data_t& data)
{
    xsim_extra_debug_check
    (
        (GetPortDim1() != data.n_rows) ||
        (GetPortDim2() != data.n_cols),
        "[WriteData] Data dimension mismatch"
    );

    d_ptr->buf = data;
    NotifyReady();
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
bool SimOutputPort::ReadyWrite()
{
    return true;
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
 SimOutputPort::SimOutputPort(u32_t id, u32_t dr, u32_t dc, SimBase* parent)
 : SimPortBase(id, dr, dc, "", parent)
{
    xsim_extra_debug_sigprint_this(this);
    Init(dr, dc);
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
 SimOutputPort::~SimOutputPort()
{
    xsim_extra_debug_sigprint_this(this);
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void SimOutputPort::ReadData(data_t& d)
{
    d = d_ptr->buf;
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void SimOutputPort::NotifyReady()
{
    for (auto& x : d_ptr->connectedPorts)
    {
        x->SetReadyRead(true);
    }
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
data_t & SimOutputPort::GetOutBuffer()
{
    return d_ptr->buf;
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void SimOutputPort::Init(u32_t dr, u32_t dc)
{
    d_ptr = std::make_shared<SimOutputPortPrivate>();
    d_ptr->buf.resize(dr, dc);
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void SimOutputPort::ConnectTo(SimPortBase& port)
{
    for (auto& x : d_ptr->connectedPorts)
    {
        if (x == &port)
        {
            return;
        }
    }

    d_ptr->connectedPorts.push_back(&port);
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void SimOutputPort::DisconnectFrom(SimPortBase& port)
{
    if (&port)
    {
        d_ptr->connectedPorts.remove(&port);
    }
}

void Connect(SimPortBase& src, SimPortBase& dst)
{
    src.ConnectTo(dst);
    dst.ConnectTo(src);
}

void Disconnect(SimPortBase& src, SimPortBase& dst)
{
    src.DisconnectFrom(dst);
    dst.DisconnectFrom(src);
}

#endif // SIM_PORTS_IMPL_HPP_INCLUDED
