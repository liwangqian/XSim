#ifndef SIM_DEBUG_HPP_INCLUDED
#define SIM_DEBUG_HPP_INCLUDED

#if defined(XSIM_EXTRA_DEBUG)

    #define xsim_extra_debug_sigprint       arma::arma_sigprint(ARMA_FNSIG); arma::arma_bktprint
    #define xsim_extra_debug_sigprint_this  arma::arma_sigprint(ARMA_FNSIG); arma::arma_thisprint
    #define xsim_extra_debug_print          arma::arma_print
    #define xsim_extra_debug_warn           arma::arma_warn
    #define xsim_extra_debug_check          arma::arma_check

#else

    #define xsim_extra_debug_sigprint        true ? (void)0 : arma::arma_bktprint
    #define xsim_extra_debug_sigprint_this   true ? (void)0 : arma::arma_thisprint
    #define xsim_extra_debug_print           true ? (void)0 : arma::arma_print
    #define xsim_extra_debug_warn            true ? (void)0 : arma::arma_warn
    #define xsim_extra_debug_check           true ? (void)0 : arma::arma_check

#endif // defined

#endif // SIM_DEBUG_HPP_INCLUDED
