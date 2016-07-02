#ifndef SIM_SIMULATION_HPP_INCLUDED
#define SIM_SIMULATION_HPP_INCLUDED

class Simulation : public SimBase
{
    XSIM_NONCOPYABLE_CLASS(Simulation)

    struct SimulationPrivate;
    std::shared_ptr<SimulationPrivate>  d_ptr;

    void        Init();
    void        SortBlocks();
    bool        CheckSampleTime();
    bool        CheckConnection();
    void        PreInitialization();
    void        PreStart();

protected:
    //travel through the blocks map and calling the blocks' corresponding method.
    void        Initialization();
    void        Start();
    void        Terminate();
    void        DoStep();
    void        Output();

public:
    Simulation(const string_t& name);

    double_t    GetSimTimeCurr () const;
    double_t    GetSimTimeStep () const;
    double_t    GetSimTimeStart() const;
    double_t    GetSimTimeStop () const;

    bool        SetSimTimeInfo(double_t start, double_t stop, double_t step = 0.01f);
    bool        SetSimStepTime(double_t dt);

    double_t    GetSolverAbsError() const;
    double_t    GetSolverRelError() const;
    solver_t    GetSolverType    () const;

    const solver_proto& GetSolver() const;

    bool        SetSolver(const solver_t type);
    bool        SetUserSolver(const solver_proto& solver);

    bool        Run();
};

#endif // SIM_SIMULATION_HPP_INCLUDED
