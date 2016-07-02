#ifndef SIM_PORTS_HPP_INCLUDED
#define SIM_PORTS_HPP_INCLUDED

class SimPortBase : public SimBase , public SimIODevice
{
    XSIM_NONCOPYABLE_CLASS(SimPortBase)

private:
    struct SimPortBasePrivate;
    std::shared_ptr<SimPortBasePrivate> d_ptr;

    void Init(u32_t id, u32_t dr, u32_t dc);

protected:
    virtual ~SimPortBase();
    SimPortBase(u32_t id, u32_t dr, u32_t dc = 1, const string_t& name = string_t(), SimBase* parent = 0);

    virtual void ConnectTo(SimPortBase& port);
    virtual void DisconnectFrom(SimPortBase& port);

    friend void Connect(SimPortBase& src, SimPortBase& dst);
    friend void Disconnect(SimPortBase& src, SimPortBase& dst);

public:
    u32_t GetPortDim1() const;
    u32_t GetPortDim2() const;

    void  SetPortDim(u32_t dr, u32_t dc);
};

class SimInputPort : public SimPortBase
{
    XSIM_NONCOPYABLE_CLASS(SimInputPort)

private:
    struct SimInputPortPrivate;
    std::shared_ptr<SimInputPortPrivate> d_ptr;

    void    Init();

protected:
    void    ConnectTo(SimPortBase& port);
    void    DisconnectFrom(SimPortBase& port);

public:
    ~SimInputPort();
    SimInputPort(u32_t id, u32_t dr, u32_t dc = 1, SimBase* parent = 0);

    bool    ReadyRead() const ;
    void    ReadData(data_t& data);
    void    SetReadyRead(bool ready = true);

    bool    Connected() const;

protected:
    void    NotifyReady();
    const data_t& GetInBuffer() const;

    friend class SimIOBlock;
};

class SimOutputPort : public SimPortBase
{
    XSIM_NONCOPYABLE_CLASS(SimOutputPort)

private:
    struct SimOutputPortPrivate;
    std::shared_ptr<SimOutputPortPrivate> d_ptr;

    void    Init(u32_t dr, u32_t dc);

protected:
    void    ConnectTo(SimPortBase& port);
    void    DisconnectFrom(SimPortBase& port);

public:
    ~SimOutputPort();
    SimOutputPort(u32_t id, u32_t dr, u32_t dc = 1, SimBase* parent = 0);

    bool    ReadyWrite();
    void    WriteData(const data_t& data);
    void    ReadData(data_t& d);

protected:
    //!将WriteData拆成下面两步，提供给SimIOBlock调用，减少拷贝动作，提升效率
    void    NotifyReady();
    data_t& GetOutBuffer();

    friend class SimIOBlock;
    friend class SimInputPort;
};

class SimNetIOPort : public SimPortBase
{
    XSIM_NONCOPYABLE_CLASS(SimNetIOPort)

private:
    struct SimNetIOPortPrivate;
    std::shared_ptr<SimNetIOPortPrivate> d_ptr;

    void    Init();

public:
    ~SimNetIOPort();
    SimNetIOPort(u32_t id, u32_t dr, u32_t dc = 1, SimBase* parent = 0);

    bool    ReadyRead();
    bool    ReadyWrite();

    void    ReadData(data_t& d);
    void    WriteData(const data_t& d);
};

void Connect(SimPortBase& src, SimPortBase& dst);
void Disconnect(SimPortBase& src, SimPortBase& dst);

#endif // SIM_PORTS_HPP_INCLUDED
