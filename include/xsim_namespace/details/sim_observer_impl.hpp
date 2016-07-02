#ifndef SIM_OBSERVER_IMPL_HPP_INCLUDED
#define SIM_OBSERVER_IMPL_HPP_INCLUDED

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void DefaultObsvr(const double_t t, const data_t& data)
{
    const arma::arma_ostream_state ostream_state(std::ref(std::cout));
    const std::streamsize cell_width = arma::arma_ostream::modify_stream(std::ref(std::cout), &t, 1);
    std::cout.width(cell_width);

    arma::arma_ostream::print_elem(std::ref(std::cout), t, true);
    std::cout << arma::reshape(data, 1, data.size());

    ostream_state.restore(std::ref(std::cout));
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
struct FileWriter
{
    std::shared_ptr<std::ofstream> pos;

    FileWriter(const char* fileName)
    : pos(new std::ofstream(fileName))
    {
    }

    void operator()(const double_t t, const data_t& m)
    {
        std::ofstream& os = *pos;
        const arma::arma_ostream_state ostream_state(os);
        const std::streamsize cell_width = arma::arma_ostream::modify_stream(os, &t, 1);
        os.width(cell_width);

        arma::arma_ostream::print_elem(os, t, true);
        os << arma::reshape(m, 1, m.size());

        ostream_state.restore(os);
    }

    ~FileWriter()
    {
        pos->flush();
    }

};

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void SimObserver::Output(const Simulation& sim)
{
    _fn(sim.GetSimTimeCurr(), GetInBuffer(0));
    ResetInPortReadyState();
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
 SimObserver::SimObserver(const Functor& fn, SimBase* parent)
 : SimBlockBase("Observer", parent), _fn(fn)
{
    AddInputPort(0, 0);
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
 SimObserver::SimObserver(SimBase* parent)
 : SimBlockBase("Observer", parent), _fn(DefaultObsvr)
{
    AddInputPort(0, 0);
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
 SimObserver::SimObserver(const char* fileName, SimBase* parent)
 : SimBlockBase("Observer", parent), _fn(FileWriter(fileName))
{
    AddInputPort(0, 0);
}



#endif // SIM_OBSERVER_IMPL_HPP_INCLUDED
