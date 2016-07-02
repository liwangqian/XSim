#ifndef SIM_IOBLOCK_HPP_INCLUDED
#define SIM_IOBLOCK_HPP_INCLUDED

class SimIOBlock : public SimBase
{
    XSIM_NONCOPYABLE_CLASS(SimIOBlock)

    struct SimIOBlockPrivate;
    std::shared_ptr<SimIOBlockPrivate> d_ptr;

    void    Init();

protected:
    explicit SimIOBlock(const string_t& name, SimBase* parent = nullptr);

    void    NotifyOutputReady(u32_t id) const;
    void    SetInPortReady(u32_t id, bool ready = true);
    void    ResetInPortReadyState();
    bool    IsReady() const;

    void    ReadData (u32_t id, data_t& d);
    void    WriteData(u32_t id, const data_t& d);

public:
    void    AddInputPort(u32_t dr, u32_t dc);
    void    AddOutputPort(u32_t dr, u32_t dc);

    u32_t   GetInputPortNum() const;
    u32_t   GetOutputPortNum() const;

protected:
    SimPortBase*    GetInputPort(u32_t id);
    SimPortBase*    GetOutputPort(u32_t id);
    u32_t           FindInputPort(const SimPortBase* port) const;
    u32_t           FindOutputPort(const SimPortBase* port) const;

    data_t&         GetOutBuffer(u32_t id);
    const data_t&   GetInBuffer (u32_t id) const;
};

#endif // SIM_IOBLOCK_HPP_INCLUDED
