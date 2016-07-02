#ifndef SIM_IODEVICE_IMPL_HPP_INCLUDED
#define SIM_IODEVICE_IMPL_HPP_INCLUDED

SimIODevice::~SimIODevice()
{

}

bool SimIODevice::ReadyRead() const
{
    return false;
}

bool SimIODevice::ReadyWrite() const
{
    return false;
}

void SimIODevice::ReadData(data_t& /*d*/)
{

}

void SimIODevice::WriteData(const data_t& /*d*/)
{

}

void SimIODevice::NotifyReady()
{

}

void SimIODevice::SetReadyRead(bool ready)
{

}

void SimIODevice::SetReadyWrite(bool ready)
{

}

#endif // SIM_IODEVICE_IMPL_HPP_INCLUDED
