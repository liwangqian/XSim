#ifndef SIM_BLOCKBASE_HPP_INCLUDED
#define SIM_BLOCKBASE_HPP_INCLUDED

class SimBlockBase : public SimSingleRateBlock
{
    XSIM_NONCOPYABLE_CLASS(SimBlockBase)

    struct SimBlockBasePrivate;
    std::shared_ptr<SimBlockBasePrivate> d_ptr;

    void    Init();

public:
    virtual ~SimBlockBase();
    SimBlockBase(const string_t& name, SimBase* parent = 0);

    bool    IsStateless() const;
    void    SetInitState(const state_t& x0);
    void    SetInitDState(const state_t& dx0);
    void    SetInitOutput(const u32_t portID, const data_t& y0);

    const state_t* GetInitState() const;
    const  data_t* GetInitOutput(const u32_t portID) const;

    void    AddInputPort(u32_t dr, u32_t dc);
    void    AddOutputPort(u32_t dr, u32_t dc);

    //!TODO: make private or protected
    void    NotifyReady(SimPortBase* port);

protected:
    void    DoStepCont(const Simulation& sim);
    void    DoStep(const Simulation& sim);

protected:
    virtual void Initialization(const Simulation& sim);
    virtual void Start(const Simulation& sim);
    virtual void Terminate(const Simulation& sim);
    virtual void Derivative(const Simulation& sim);
    virtual void Update(const Simulation& sim);
    virtual void Output(const Simulation& sim);

    friend class Simulation;
    friend void  Connect(SimBlockBase& srcBlock, u32_t oportID, SimBlockBase& dstBlock, u32_t iportID);
    friend void  Disconnect(SimBlockBase& srcBlock, u32_t oportID, SimBlockBase& dstBlock, u32_t iportID);
};

void Connect(SimBlockBase& srcBlock, u32_t oportID, SimBlockBase& dstBlock, u32_t iportID);
void Disconnect(SimBlockBase& srcBlock, u32_t oportID, SimBlockBase& dstBlock, u32_t iportID);

#endif // SIM_BLOCKBASE_HPP_INCLUDED
