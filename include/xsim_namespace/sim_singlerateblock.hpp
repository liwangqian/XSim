#ifndef SIM_SINGLERATEBLOCK_HPP_INCLUDED
#define SIM_SINGLERATEBLOCK_HPP_INCLUDED

class SimSingleRateBlock : public SimIOBlock
{
    XSIM_NONCOPYABLE_CLASS(SimSingleRateBlock)

    struct SimSingleRateBlockPrivate;
    std::shared_ptr<SimSingleRateBlockPrivate>  d_ptr;

    void    Init();

protected:
    SimSingleRateBlock(double_t Ts, double_t offset, const string_t& name, SimBase* parent = nullptr);

public:
    bool    SetSampleTime(double_t Ts);
    bool    SetSampleTimeOffset(double_t offset);

    double_t    GetSampleTime() const;
    double_t    GetSampleTimeOffset() const;

    bool    IsContinuous() const;
};

#endif // SIM_SINGLERATEBLOCK_HPP_INCLUDED
