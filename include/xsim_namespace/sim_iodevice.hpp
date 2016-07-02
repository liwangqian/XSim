#ifndef SIM_IODEVICE_HPP_INCLUDED
#define SIM_IODEVICE_HPP_INCLUDED

class SimIODevice
{
    XSIM_NONCOPYABLE_CLASS(SimIODevice)

protected:
    virtual ~SimIODevice();
    SimIODevice() = default;

public:
    virtual bool    ReadyRead() const ;
    virtual bool    ReadyWrite() const ;
    virtual void    ReadData(data_t& data);
    virtual void    WriteData(const data_t& data);
    virtual void    NotifyReady();

    virtual void    SetReadyRead(bool ready = true);
    virtual void    SetReadyWrite(bool ready = true);
};

#endif // SIM_IODEVICE_HPP_INCLUDED
