#ifndef XSIM_HPP_INCLUDED
#define XSIM_HPP_INCLUDED

#include <iostream>
#include <memory>
#include <vector>
#include <list>
#include <functional>
#include <bitset>

#include "armadillo"
#include "boost/numeric/odeint.hpp"

namespace xsim{

#include "xsim_namespace/sim_types.hpp"

}

//don't put in xsim namespace
#include "xsim_config.hpp"

namespace xsim{

//utility
#include "xsim_namespace/sim_version.hpp"
#include "xsim_namespace/sim_macros.hpp"
#include "xsim_namespace/sim_debug.hpp"
#include "xsim_namespace/sim_forward.hpp"
#include "xsim_namespace/sim_solver.hpp"

//definition
#include "xsim_namespace/sim_base.hpp"
#include "xsim_namespace/sim_iodevice.hpp"
#include "xsim_namespace/sim_ports.hpp"
#include "xsim_namespace/sim_ioblock.hpp"
#include "xsim_namespace/sim_singlerateblock.hpp"
#include "xsim_namespace/sim_blockbase.hpp"

//functions
#include "xsim_namespace/sim_constant.hpp"
#include "xsim_namespace/sim_observer.hpp"
#include "xsim_namespace/sim_addition.hpp"
#include "xsim_namespace/sim_multiply.hpp"

#include "xsim_namespace/sim_simulation.hpp"

//implement
#include "xsim_namespace/details/sim_solver_impl.hpp"
#include "xsim_namespace/details/sim_base_impl.hpp"
#include "xsim_namespace/details/sim_iodevice_impl.hpp"
#include "xsim_namespace/details/sim_ports_impl.hpp"
#include "xsim_namespace/details/sim_ioblock_impl.hpp"
#include "xsim_namespace/details/sim_singlerateblock_impl.hpp"
#include "xsim_namespace/details/sim_blockbase_impl.hpp"

//functions
#include "xsim_namespace/details/sim_constant_impl.hpp"
#include "xsim_namespace/details/sim_observer_impl.hpp"
#include "xsim_namespace/details/sim_addition_impl.hpp"
#include "xsim_namespace/details/sim_multiply_impl.hpp"

#include "xsim_namespace/details/sim_simulation_impl.hpp"

}

#endif // XSIM_HPP_INCLUDED
