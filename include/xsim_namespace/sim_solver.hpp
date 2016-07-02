#ifndef SIM_SOLVER_HPP_INCLUDED
#define SIM_SOLVER_HPP_INCLUDED

enum class solver_t
{
    explicit_euler = 0,
    modified_midpoint,
    runge_kutta4_classic,
    runge_kutta_cash_karp54_classic,
    runge_kutta_dopri5,
    //runge_kutta_cash_karp54,

    user_defined_solver = 100,
};

std::ostream& operator<<(std::ostream& os, const solver_t type);

class SimSolver
{
    struct euler;
    struct modified_midpoint;
    struct runge_kutta4_classic;
    struct runge_kutta_cash_karp54_classic;
    struct runge_kutta_dopri5;
    //struct runge_kutta_cash_karp54;

public:
    static solver_proto GetSolverProto(const solver_t type);
};

#endif // SIM_SOLVER_HPP_INCLUDED
