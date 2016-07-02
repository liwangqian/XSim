#ifndef SIM_SOLVER_IMPL_HPP_INCLUDED
#define SIM_SOLVER_IMPL_HPP_INCLUDED

std::ostream& operator<<(std::ostream& os, const solver_t type)
{
    switch (type)
    {
        case solver_t::explicit_euler:
            os << "explicit_euler";
            break;
        case solver_t::modified_midpoint:
            os << "modified_midpoint";
            break;
        case solver_t::runge_kutta4_classic:
            os << "runge_kutta4_classic";
            break;
        case solver_t::runge_kutta_cash_karp54_classic:
            os << "runge_kutta_cash_karp54_classic";
            break;
        case solver_t::runge_kutta_dopri5:
            os << "runge_kutta_dopri5";
            break;
        default:
            os << "user_defined_solver";
            break;
    }

    return os;
}

#define XSIM_DEFINE_SOLVER(solver_name) \
struct SimSolver::solver_name\
{ \
    typedef boost::numeric::odeint::solver_name<state_t> type; \
    type    solver; \
    \
    void operator()(const system_t& sys, state_t& x, double_t t, double_t dt)\
    { \
        solver.do_step(std::ref(sys), x, t, dt); \
    } \
    \
}

XSIM_DEFINE_SOLVER(euler);
XSIM_DEFINE_SOLVER(modified_midpoint);
XSIM_DEFINE_SOLVER(runge_kutta4_classic);
XSIM_DEFINE_SOLVER(runge_kutta_cash_karp54_classic);
XSIM_DEFINE_SOLVER(runge_kutta_dopri5);
//XSIM_DEFINE_SOLVER(runge_kutta_cash_karp54);

solver_proto SimSolver::GetSolverProto(const solver_t type)
{
    switch (type)
    {
        case solver_t::explicit_euler:
            return euler();
        case solver_t::modified_midpoint:
            return modified_midpoint();
        case solver_t::runge_kutta4_classic:
            return runge_kutta4_classic();
        case solver_t::runge_kutta_cash_karp54_classic:
            return runge_kutta_cash_karp54_classic();
        case solver_t::runge_kutta_dopri5:
            return runge_kutta_dopri5();
        /*
        case solver_t::runge_kutta_cash_karp54:
            return runge_kutta_cash_karp54();
        */
        default:
            return euler();

    }
}



#endif // SIM_SOLVER_IMPL_HPP_INCLUDED
