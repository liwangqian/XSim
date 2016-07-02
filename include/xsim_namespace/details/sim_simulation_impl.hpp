#ifndef SIM_SIMULATION_IMPL_HPP_INCLUDED
#define SIM_SIMULATION_IMPL_HPP_INCLUDED

struct Simulation::SimulationPrivate
{
    double_t        t_curr;   //current simulation time.
    double_t        t_step;   //the simulation time step.
    double_t        t_start;  //the start time of the simulation.
    double_t        t_stop;   //the stop time of the simulation.

    double_t        err_abs;
    double_t        err_rel;

    solver_t        sol_type;
    solver_proto    solver;

    std::vector<SimBlockBase*>  sorted_blocks;
};

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void Simulation::Init()
{
    d_ptr = std::make_shared<SimulationPrivate>();

    d_ptr->t_curr  = 0.0f;
    d_ptr->t_step  = 1.0f;
    d_ptr->t_start = 0.0f;
    d_ptr->t_stop  = 0.0f;

    d_ptr->err_abs = XSIM_EPS;
    d_ptr->err_rel = XSIM_EPS;

    d_ptr->sol_type= solver_t::runge_kutta_dopri5;
    d_ptr->solver  = SimSolver::GetSolverProto(d_ptr->sol_type);
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void Simulation::PreStart()
{
    SimBase::object_array children = GetChildren();
    for (auto block : children)
    {
        static_cast<SimBlockBase*>(block)->Start(*this);
    }
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void Simulation::PreInitialization()
{
    SimBase::object_array children = GetChildren();
    for (auto child : children)
    {
        static_cast<SimBlockBase*>(child)->Initialization(*this);
    }
}



/** @brief (one liner)
  *
  * (documentation goes here)
  */
void Simulation::SortBlocks()
{
    SimBase::object_array       usBlocks(GetChildren());
    std::vector<SimBlockBase*>  sortedBlocks;
    const u32_t                 blockCnt = usBlocks.size();

    if (blockCnt == 0)
    {
        return;
    }

    d_ptr->t_curr = d_ptr->t_start;
    while (true)
    {
        const u32_t sortedCnt = sortedBlocks.size();

        for (u32_t index = 0; index < blockCnt; ++index)
        {
            SimBlockBase* blockBase = static_cast<SimBlockBase*>(usBlocks[index]);
            if (blockBase == nullptr)
            {
                continue;
            }

            if (blockBase->IsReady())
            {
                sortedBlocks.push_back(blockBase);
                usBlocks[index] = nullptr;

                if (blockBase->GetOutputPortNum() != 0)
                {
                    blockBase->Output(*this);
                }
            }
        }

        //!所有模块都排序完成
        if (blockCnt == sortedBlocks.size())
        {
            break;
        }

        //!一趟下来，没有新的模块被处理，认为有MathLoop
        xsim_extra_debug_check
        (
            sortedCnt == sortedBlocks.size(),
            "[SortBlocks] Mathloop exist!"
        );
    }

    d_ptr->sorted_blocks = std::move(sortedBlocks);
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void Simulation::Initialization()
{
    for (auto block : d_ptr->sorted_blocks)
    {
        block->Initialization(*this);
    }
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void Simulation::Start()
{
    for (auto block : d_ptr->sorted_blocks)
    {
        block->Start(*this);
    }
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void Simulation::Terminate()
{
    for (auto block : d_ptr->sorted_blocks)
    {
        block->Terminate(*this);
    }
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void Simulation::DoStep()
{
    for (auto block : d_ptr->sorted_blocks)
    {
        block->DoStep(*this);
    }
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void Simulation::Output()
{
    for (auto block : d_ptr->sorted_blocks)
    {
        block->Output(*this);
    }
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
 Simulation::Simulation(const string_t& name)
 : SimBase(name)
{
    Init();
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
double_t Simulation::GetSimTimeCurr() const
{
    return d_ptr->t_curr;
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
double_t Simulation::GetSimTimeStep() const
{
    return d_ptr->t_step;
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
double_t Simulation::GetSimTimeStart() const
{
    return d_ptr->t_start;
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
double_t Simulation::GetSimTimeStop() const
{
    return d_ptr->t_stop;
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
const solver_proto & Simulation::GetSolver() const
{
    return d_ptr->solver;
}



/** @brief (one liner)
  *
  * (documentation goes here)
  */
bool Simulation::SetSimTimeInfo(double_t start, double_t stop, double_t step)
{
    //check
    if((start >= 0.0f) &&
       (start <= stop) &&
       (step  >  0.0f))
    {
        d_ptr->t_start = start;
        d_ptr->t_stop  = stop;
        d_ptr->t_step  = step;

        return true;
    };

    //assign
    xsim_extra_debug_print("[SetSimTimeInfo] Invalid parameters!");

    return false;
}

bool Simulation::SetSimStepTime(double_t dt)
{
    if (dt > 0.0f)
    {
        d_ptr->t_step = dt;
    }
    return true;
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
double_t Simulation::GetSolverAbsError() const
{
    return d_ptr->err_abs;
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
double_t Simulation::GetSolverRelError() const
{
    return d_ptr->err_rel;
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
solver_t Simulation::GetSolverType() const
{
    return d_ptr->sol_type;
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
bool Simulation::SetSolver(const solver_t type)
{
    d_ptr->sol_type = type;
    d_ptr->solver   = SimSolver::GetSolverProto(type);
    return true;
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
bool Simulation::SetUserSolver(const solver_proto& solver)
{
    d_ptr->sol_type = solver_t::user_defined_solver;
    d_ptr->solver   = solver;

    return true;
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
bool Simulation::Run()
{
    /* diagram:
     * 1) initialization(): travel through the blocks map and call the blocks' initialization() method;
     * 2) start(): travel through the blocks map and call the blocks' start() method;
     * 3) output(): travel through the blocks map and call the blocks' output() method to update the outputs;
     * 4) do_step(): travel through the blocks map and call the blocks' do_step() method to update states;
     * 5) repeat the 3) and 4) in every simulation step, until the stop time reached;
     * 6) terminate(): travel through the blocks map and call the blocks' terminate() method;
     */

    PreInitialization();

    PreStart();

    //执行一次模块排序，后面就可以顺序执行了
    SortBlocks();

    Initialization();

    Start();

    //enter the simulation loop
    d_ptr->t_curr = d_ptr->t_start;
    while(d_ptr->t_curr <= d_ptr->t_stop)
    {
        Output(); //update the blocks outputs
        DoStep();//compute the new states for current simulation time.

        //go to next step
        d_ptr->t_curr += d_ptr->t_step;
    }

    if ((d_ptr->t_step - (d_ptr->t_curr - d_ptr->t_stop)) < 1.0e-12)
    {
        d_ptr->t_curr = d_ptr->t_stop;
        Output();
    }

    Terminate();


    return true;
}



#endif // SIM_SIMULATION_IMPL_HPP_INCLUDED
