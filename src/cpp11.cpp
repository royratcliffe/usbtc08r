// Generated by cpp11: do not edit by hand
// clang-format off


#include "cpp11/declarations.hpp"
#include <R_ext/Visibility.h>

// code.cpp
int16_t open_();
extern "C" SEXP _usbtc08r_open_() {
  BEGIN_CPP11
    return cpp11::as_sexp(open_());
  END_CPP11
}
// code.cpp
int16_t open_async_();
extern "C" SEXP _usbtc08r_open_async_() {
  BEGIN_CPP11
    return cpp11::as_sexp(open_async_());
  END_CPP11
}
// code.cpp
cpp11::integers open_progress_();
extern "C" SEXP _usbtc08r_open_progress_() {
  BEGIN_CPP11
    return cpp11::as_sexp(open_progress_());
  END_CPP11
}
// code.cpp
int16_t set_channel_(int16_t handle, int16_t channel, int8_t tc_type);
extern "C" SEXP _usbtc08r_set_channel_(SEXP handle, SEXP channel, SEXP tc_type) {
  BEGIN_CPP11
    return cpp11::as_sexp(set_channel_(cpp11::as_cpp<cpp11::decay_t<int16_t>>(handle), cpp11::as_cpp<cpp11::decay_t<int16_t>>(channel), cpp11::as_cpp<cpp11::decay_t<int8_t>>(tc_type)));
  END_CPP11
}
// code.cpp
int32_t run_(int16_t handle, int32_t interval);
extern "C" SEXP _usbtc08r_run_(SEXP handle, SEXP interval) {
  BEGIN_CPP11
    return cpp11::as_sexp(run_(cpp11::as_cpp<cpp11::decay_t<int16_t>>(handle), cpp11::as_cpp<cpp11::decay_t<int32_t>>(interval)));
  END_CPP11
}
// code.cpp
cpp11::data_frame get_temp_(int16_t handle, int32_t length, int16_t channel, int16_t units, int16_t fill);
extern "C" SEXP _usbtc08r_get_temp_(SEXP handle, SEXP length, SEXP channel, SEXP units, SEXP fill) {
  BEGIN_CPP11
    return cpp11::as_sexp(get_temp_(cpp11::as_cpp<cpp11::decay_t<int16_t>>(handle), cpp11::as_cpp<cpp11::decay_t<int32_t>>(length), cpp11::as_cpp<cpp11::decay_t<int16_t>>(channel), cpp11::as_cpp<cpp11::decay_t<int16_t>>(units), cpp11::as_cpp<cpp11::decay_t<int16_t>>(fill)));
  END_CPP11
}
// code.cpp
cpp11::data_frame get_temp_deskew_(int16_t handle, int32_t length, int16_t channel, int16_t units, int16_t fill);
extern "C" SEXP _usbtc08r_get_temp_deskew_(SEXP handle, SEXP length, SEXP channel, SEXP units, SEXP fill) {
  BEGIN_CPP11
    return cpp11::as_sexp(get_temp_deskew_(cpp11::as_cpp<cpp11::decay_t<int16_t>>(handle), cpp11::as_cpp<cpp11::decay_t<int32_t>>(length), cpp11::as_cpp<cpp11::decay_t<int16_t>>(channel), cpp11::as_cpp<cpp11::decay_t<int16_t>>(units), cpp11::as_cpp<cpp11::decay_t<int16_t>>(fill)));
  END_CPP11
}
// code.cpp
int16_t close_(int16_t handle);
extern "C" SEXP _usbtc08r_close_(SEXP handle) {
  BEGIN_CPP11
    return cpp11::as_sexp(close_(cpp11::as_cpp<cpp11::decay_t<int16_t>>(handle)));
  END_CPP11
}
// code.cpp
int16_t get_last_error_(int16_t handle);
extern "C" SEXP _usbtc08r_get_last_error_(SEXP handle) {
  BEGIN_CPP11
    return cpp11::as_sexp(get_last_error_(cpp11::as_cpp<cpp11::decay_t<int16_t>>(handle)));
  END_CPP11
}
// code.cpp
std::string error_(int16_t error);
extern "C" SEXP _usbtc08r_error_(SEXP error) {
  BEGIN_CPP11
    return cpp11::as_sexp(error_(cpp11::as_cpp<cpp11::decay_t<int16_t>>(error)));
  END_CPP11
}

extern "C" {
/* .Call calls */
extern SEXP run_testthat_tests(SEXP);

static const R_CallMethodDef CallEntries[] = {
    {"_usbtc08r_close_",           (DL_FUNC) &_usbtc08r_close_,           1},
    {"_usbtc08r_error_",           (DL_FUNC) &_usbtc08r_error_,           1},
    {"_usbtc08r_get_last_error_",  (DL_FUNC) &_usbtc08r_get_last_error_,  1},
    {"_usbtc08r_get_temp_",        (DL_FUNC) &_usbtc08r_get_temp_,        5},
    {"_usbtc08r_get_temp_deskew_", (DL_FUNC) &_usbtc08r_get_temp_deskew_, 5},
    {"_usbtc08r_open_",            (DL_FUNC) &_usbtc08r_open_,            0},
    {"_usbtc08r_open_async_",      (DL_FUNC) &_usbtc08r_open_async_,      0},
    {"_usbtc08r_open_progress_",   (DL_FUNC) &_usbtc08r_open_progress_,   0},
    {"_usbtc08r_run_",             (DL_FUNC) &_usbtc08r_run_,             2},
    {"_usbtc08r_set_channel_",     (DL_FUNC) &_usbtc08r_set_channel_,     3},
    {"run_testthat_tests",         (DL_FUNC) &run_testthat_tests,         1},
    {NULL, NULL, 0}
};
}

extern "C" attribute_visible void R_init_usbtc08r(DllInfo* dll){
  R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);
  R_forceSymbols(dll, TRUE);
}
