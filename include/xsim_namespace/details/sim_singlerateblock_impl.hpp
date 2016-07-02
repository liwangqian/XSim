#ifndef SIM_SINGLERATEBLOCK_IMPL_HPP_INCLUDED
#define SIM_SINGLERATEBLOCK_IMPL_HPP_INCLUDED

struct SimSingleRateBlock::SimSingleRateBlockPrivate
{
    double_t    sampleTime;
    double_t    offset;
};

/** @brief (one liner)
  *
  * (documentation goes here)
  */
double_t SimSingleRateBlock::GetSampleTimeOffset() const
{
    return d_ptr->offset;
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
double_t SimSingleRateBlock::GetSampleTime() const
{
    return d_ptr->sampleTime;
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
bool SimSingleRateBlock::SetSampleTimeOffset(double_t offset)
{
    const double_t mag = d_ptr->sampleTime / offset;
    const bool     isValid = (mag - (int)mag) < XSIM_EPS;
    if ((offset >= 0.0) && (offset < d_ptr->sampleTime) && (isValid == true))
    {
        d_ptr->offset = offset;
        return true;
    }

    return false;
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
bool SimSingleRateBlock::SetSampleTime(double_t Ts)
{
    if (Ts >= 0.0)
    {
        d_ptr->sampleTime = Ts;
        return true;
    }

    return false;
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
SimSingleRateBlock::SimSingleRateBlock(double_t Ts, double_t offset, const string_t& name, SimBase* parent)
: SimIOBlock(name, parent)
{
    Init();
}

 /** @brief (one liner)
   *
   * (documentation goes here)
   */
 void SimSingleRateBlock::Init()
 {
    d_ptr = std::make_shared<SimSingleRateBlockPrivate>();
    d_ptr->sampleTime = 0.0;
    d_ptr->offset     = 0.0;
 }

 /** @brief (one liner)
   *
   * (documentation goes here)
   */
 bool SimSingleRateBlock::IsContinuous() const
 {
    return (d_ptr->sampleTime - 0.0) < XSIM_EPS;
 }


#endif // SIM_SINGLERATEBLOCK_IMPL_HPP_INCLUDED
