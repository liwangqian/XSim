#ifndef TEST_SIM_BLOCKS_HPP_INCLUDED
#define TEST_SIM_BLOCKS_HPP_INCLUDED

using namespace std;

void test_sim_blocks()
{
    xsim::SimBlockBase bs("bs");
    bs.AddInputPort(1,2);
    bs.AddInputPort(2,3);
    bs.AddInputPort(2,3);
    bs.AddOutputPort(1,1);
    bs.AddOutputPort(1,1);

    cout << bs.GetObjectName() << endl;
    cout << bs.GetInputPortNum() << endl;
    cout << bs.GetOutputPortNum() << endl;
    //cout << *bs.GetInitState() << endl;

    cout << boolalpha << bs.IsStateless() << endl;

    bs.SetInitState({1,2,3,4});

    cout << boolalpha << bs.IsStateless() << endl;

    xsim::SimBlockBase bs1("bs1");

    bs.AddInputPort(1,1);

    Connect(bs, 1, bs1, 0);
    Disconnect(bs, 1, bs1, 0);
}

#endif // TEST_SIM_BLOCKS_HPP_INCLUDED
