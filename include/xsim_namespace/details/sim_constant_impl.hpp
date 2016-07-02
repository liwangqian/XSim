#ifndef SIM_CONSTANT_IMPL_HPP_INCLUDED
#define SIM_CONSTANT_IMPL_HPP_INCLUDED

/** @brief (one liner)
  *
  * (documentation goes here)
  */
 SimConstant::SimConstant(const double_t cd, SimBase* parent)
 : SimBlockBase("Constant", parent)
{
    AddOutputPort(1, 1);

    GetOutBuffer(0)(0,0) = cd;
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
 SimConstant::SimConstant(const data_t& cd, SimBase* parent)
 : SimBlockBase("Constant", parent)
{
    AddOutputPort(cd.n_rows, cd.n_cols);

    GetOutBuffer(0) = cd;
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void SimConstant::Output(const Simulation& sim)
{
    NotifyOutputReady(0);
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void SimConstant::Initialization(const Simulation& sim)
{
    NotifyOutputReady(0);
}


#endif // SIM_CONSTANT_IMPL_HPP_INCLUDED
