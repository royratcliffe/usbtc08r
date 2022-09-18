#include <Rcpp.h>

#if defined(linux)
#include <libusbtc08-1.7/TC08Api.h>
#else
#include <usbtc08.h>
#endif

using namespace Rcpp;

//' Open Unit
//' @export
// [[Rcpp::export]]
int open_unit() {
  return usb_tc08_open_unit();
}

//' Open Unit Asynchronously
//' @export
// [[Rcpp::export]]
int open_unit_async() {
  return usb_tc08_open_unit_async();
}

//' Open Unit Progress
//' @details The handle only makes sense on completion, never on pending or failure.
//' @export
// [[Rcpp::export]]
List open_unit_progress() {
  short handle, percent_progress;
  auto x = List::create();
  switch (usb_tc08_open_unit_progress(&handle, &percent_progress)) {
  case USBTC08_PROGRESS_PENDING:
    x["progress"] = "pending";
    break;
  case USBTC08_PROGRESS_COMPLETE:
    x["progress"] = "complete";
    x["handle"] = handle;
    break;
  case USBTC08_PROGRESS_FAIL:
    x["progress"] = "fail";
  }
  x["percent"] = percent_progress;
  return x;
}

//' Close Unit
//' @export
// [[Rcpp::export]]
int close_unit(int handle) {
  return usb_tc08_close_unit(handle);
}

//' Stop Unit
//' @export
// [[Rcpp::export]]
int stop_unit(int handle) {
  return usb_tc08_stop(handle);
}

//' Get Minimum Interval in Milliseconds
//' @details Can answer zero.
//' @param handle Integer handle of unit
//' @export
// [[Rcpp::export]]
long get_minimum_interval_ms(int handle) {
  return usb_tc08_get_minimum_interval_ms(handle);
}

//' Set Channel Type
//' @param handle Unit handle
//' @param channel Selected channel
//' @param tc_type Thermocouple type, one of the follow
//'   `c("B", "E", "J", "K", "N", "R", "S", "T")`
//'   or `"X"` for voltage, space `" "` to disable channel
//' @export
// [[Rcpp::export]]
short set_channel(short handle, short channel, char tc_type) {
  return usb_tc08_set_channel(handle, channel, tc_type);
}

//' Run
//' @details Fails if no channels set.
//' @param interval_ms Sampling interval in milliseconds
//' @export
// [[Rcpp::export]]
long run(short handle, long interval_ms) {
  return usb_tc08_run(handle, interval_ms);
}

//' Get Temperature
//' @details The number of readings returned may not match the length requested, or might even be zero.
//' @export
// [[Rcpp::export]]
List get_temp(short handle, long buffer_length, short channel, short units, short fill_missing) {
  auto temp = new float[buffer_length];
  auto times_ms = new long[buffer_length];
  short overflow;
  long readings = usb_tc08_get_temp(handle, temp, times_ms, buffer_length, &overflow, channel, units, fill_missing);
  auto x = List::create(
    _["temp"] = NumericVector::import(temp, temp + readings),
    _["times_ms"] = NumericVector::import(times_ms, times_ms + readings),
    _["overflow"] = overflow,
    _["readings"] = readings
  );
  delete[] temp;
  delete[] times_ms;
  return x;
}

//' Get Single Temperature
//' @details Uses `USBTC08_CHANNEL_COUNT` rather than `USBTC08_MAX_CHANNELS` because each unit has nine channels including CJC.
//' @export
// [[Rcpp::export]]
List get_single(short handle, short units) {
  float temp[USBTC08_CHANNEL_COUNT];
  short overflow_flags;
  long success = usb_tc08_get_single(handle, temp, &overflow_flags, units);
  return List::create(
    _["temp"] = NumericVector::import(temp, temp + USBTC08_CHANNEL_COUNT),
    _["overflow_flags"] = overflow_flags,
    _["success"] = success
  );
}

//' Get Unit Information
//' @details Makes an important assumption about the driver version: the driver
//'   must null-terminate the character string. Also assumes that non-zero
//'   return indicates success and never error.
//' @param handle Integer handle of unit
//' @export
// [[Rcpp::export]]
Nullable<List> get_unit_info(int handle) {
  USBTC08_INFO info;
  info.size = sizeof(info);
  if (!usb_tc08_get_unit_info(handle, &info)) return R_NilValue;
  return List::create(
    _["driver_version"] = info.DriverVersion,
    _["picopp_version"] = info.PicoppVersion,
    _["hardware_version"] = info.HardwareVersion,
    _["variant"] = info.Variant,
    _["serial"] = info.szSerial,
    _["cal_date"] = info.szCalDate
  );
}

//' Get Last Error
//' @export
// [[Rcpp::export]]
short get_last_error(short handle) {
  return usb_tc08_get_last_error(handle);
}

// all(usbtc08r:::error() == 0:15)
// [1] TRUE
// [[Rcpp::export]]
IntegerVector error() {
  IntegerVector x {
    USBTC08_ERROR_OK,
    USBTC08_ERROR_OS_NOT_SUPPORTED,
    USBTC08_ERROR_NO_CHANNELS_SET,
    USBTC08_ERROR_INVALID_PARAMETER,
    USBTC08_ERROR_VARIANT_NOT_SUPPORTED,
    USBTC08_ERROR_INCORRECT_MODE,
    USBTC08_ERROR_ENUMERATION_INCOMPLETE,
    USBTC08_ERROR_NOT_RESPONDING,
    USBTC08_ERROR_FW_FAIL,
    USBTC08_ERROR_CONFIG_FAIL,
    USBTC08_ERROR_NOT_FOUND,
    USBTC08_ERROR_THREAD_FAIL,
    USBTC08_ERROR_PIPE_INFO_FAIL,
    USBTC08_ERROR_NOT_CALIBRATED,
    // typo
    USBTC08_EROOR_PICOPP_TOO_OLD,
    USBTC08_ERROR_COMMUNICATION,
  };
  x.names() = CharacterVector {
    "ok",
    "os_not_supported",
    "no_channels_set",
    "invalid_parameter",
    "variant_not_supported",
    "incorrect_mode",
    "enumeration_incomplete",
    "not_responding",
    "fw_fail",
    "config_fail",
    "not_found",
    "thread_fail",
    "pipe_info_fail",
    "not_calibrated",
    "picopp_too_old",
    "communication",
  };
  return x;
}
