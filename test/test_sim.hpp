#ifndef TEST_SIM_HPP_INCLUDED
#define TEST_SIM_HPP_INCLUDED

#include "../include/xsim.hpp"
#include <fstream>
#include <sigpack/sigpack.h>


using namespace std;
using namespace xsim;
using namespace sp;

struct scope{
    struct scope_data{
        gplot gp;
        vector<double> _t;
        vector<double> _y;
    };

    shared_ptr<scope_data> _data;

    scope()
    : _data(new scope_data)
    {
        _data->gp.window("scope", 550,10,900,400);
        _data->gp.xlabel("time(sec)");
        _data->gp.ylabel("state");
    }

	void operator()(const double_t x, const data_t& y)
	{
        _data->_t.push_back(x);
        _data->_y.push_back(y(0,1));

        _data->gp.plot(_data->_t, _data->_y, "xsim");
	}
};


void test_sim_simulation()
{
    Simulation    sim("test");
    sim.SetSimTimeInfo(0.0f, 100.0f, 0.01f);

    SimConstant   c0(arma::randu(10,1), &sim);
    SimConstant   c1(arma::randu(10,1), &sim);
    SimObserver   obsv("out.dat", &sim);

    SimAddition   add(3, &sim);
    add.SetInitOutput(0, arma::randu(10,1));

    Connect(add, 0, obsv, 0);
    Connect(c0, 0, add, 0);
    Connect(c1, 0, add, 1);
    Connect(add,0, add, 2);

    SimAddition   sum(2, &sim);
    Connect(add, 0, sum, 0);
    Connect(c0, 0, sum, 1);
    Connect(sum, 0, obsv, 0);

    //sim.Run();
    //sim.Run();

    SimConstant c2(arma::randu(10, 2), &sim);
    SimConstant c3(arma::randu(2, 10), &sim);

    SimObserver obsv1(scope(), &sim);

    SimMultiply mul(2, SimMultiply::VECTOR, &sim);
    mul.SetInitOutput(0, arma::randu(10, 10));

    Connect(c2, 0, mul, 0);
    Connect(c3, 0, mul, 1);
    Connect(mul, 0, obsv1, 0);

    sim.Run();
}

#endif // TEST_SIM_HPP_INCLUDED
