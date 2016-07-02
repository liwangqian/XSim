#ifndef TEST_SIM_PORTS_HPP_INCLUDED
#define TEST_SIM_PORTS_HPP_INCLUDED

using namespace std;

void test_sim_ports()
{
    xsim::SimInputPort  iport(1, 2, 2);

    cout << iport.GetPortDim1() << endl;
    cout << iport.GetPortDim2() << endl;

    iport.SetObjectName("HHH");
    cout << iport.GetObjectName() << endl;

    xsim::SimOutputPort oport(2,2,2);

    Connect(iport, oport);

    xsim::data_t d = "1 2;3 4";
    oport.WriteData(d);

    cout << iport.ReadyRead() << endl;

    xsim::data_t x;
    iport.ReadData(x);
    cout << x << endl;
}



#endif // TEST_SIM_PORTS_HPP_INCLUDED
