#ifndef XSIM_CONFIG_HPP_INCLUDED
#define XSIM_CONFIG_HPP_INCLUDED

//needed for use of odeint library
namespace boost { namespace numeric { namespace odeint {

template<>
struct is_resizeable< xsim::state_t >
{
    typedef boost::true_type type;
    static const bool value = type::value;
};

}}}

#endif // XSIM_CONFIG_HPP_INCLUDED
