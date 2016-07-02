#ifndef SIM_MACROS_HPP_INCLUDED
#define SIM_MACROS_HPP_INCLUDED

#define XSIM_NONCOPYABLE_CLASS(className)               \
    className(const className&) = delete;               \
    className& operator=(const className&) = delete;

#define XSIM_INDEX_INVALID  ((u32_t)-1)

#define XSIM_EPS    (1.0e-6)

#define XSIM_MAX_SUBOBJS    (128)

#endif // SIM_MACROS_HPP_INCLUDED
