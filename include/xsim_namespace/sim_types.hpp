#ifndef SIM_TYPES_HPP_INCLUDED
#define SIM_TYPES_HPP_INCLUDED

typedef unsigned char       u8_t;
typedef unsigned short      u16_t;
typedef unsigned int        u32_t;
typedef unsigned long long  u64_t;

typedef signed char         i8_t;
typedef signed short        i16_t;
typedef signed int          i32_t;
typedef signed long long    i64_t;

typedef float               float_t;
typedef double              double_t;

typedef double_t            real_t;
typedef u32_t               size_t;
typedef u32_t               offset_t;

typedef std::string         string_t;

typedef arma::Mat<double_t> data_t;
typedef arma::Col<double_t> state_t;

typedef std::function<void(const state_t&, state_t&, const double_t)> system_t;
typedef std::function<void(const system_t&, state_t&, const double_t, const double_t)> solver_proto;

#endif // SIM_TYPES_HPP_INCLUDED
