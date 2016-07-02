#include <iostream>
#include <limits>
#include "test/testcases.hpp"

using namespace std;

int main()
{
    cout << "Simulation toolkit, version:\t"
         << xsim::version::FULLVERSION_STRING << endl;

    test_sim_ports();
    test_sim_blocks();
    test_sim_simulation();

    cout << XSIM_EPS << endl;

    return 0;
}
