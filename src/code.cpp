#include "code.h"

#include <map>

static int16_t units_(std::string x) {
  static const std::map<std::string, int16_t> units{
    {"centigrade", USBTC08_UNITS_CENTIGRADE},
    {"fahrenheit", USBTC08_UNITS_FAHRENHEIT},
    {"kelvin", USBTC08_UNITS_KELVIN},
    {"rankine", USBTC08_UNITS_RANKINE}
  };
  auto i = units.find(x);
  if (i == units.end()) cpp11::stop("invalid string `%s` value for units", x.c_str());
  return i->second;
}

/*
 * Note the typing mistake `USBTC08_EROOR_PICOPP_TOO_OLD` for an error code.
 */
[[cpp11::register]] std::string error_(int16_t x) {
  static const std::map<int16_t, std::string> error{
    {USBTC08_ERROR_OK, "ok"},
    {USBTC08_ERROR_OS_NOT_SUPPORTED, "os_not_supported"},
    {USBTC08_ERROR_NO_CHANNELS_SET, "no_channels_set"},
    {USBTC08_ERROR_INVALID_PARAMETER, "invalid_parameter"},
    {USBTC08_ERROR_VARIANT_NOT_SUPPORTED, "variant_not_supported"},
    {USBTC08_ERROR_INCORRECT_MODE, "incorrect_mode"},
    {USBTC08_ERROR_ENUMERATION_INCOMPLETE, "enumeration_incomplete"},
    {USBTC08_ERROR_NOT_RESPONDING, "not_responding"},
    {USBTC08_ERROR_FW_FAIL, "fw_fail"},
    {USBTC08_ERROR_CONFIG_FAIL, "config_fail"},
    {USBTC08_ERROR_NOT_FOUND, "not_found"},
    {USBTC08_ERROR_THREAD_FAIL, "thread_fail"},
    {USBTC08_ERROR_PIPE_INFO_FAIL, "pipe_info_fail"},
    {USBTC08_ERROR_NOT_CALIBRATED, "not_calibrated"},
    {USBTC08_EROOR_PICOPP_TOO_OLD, "picopp_too_old"},
    {USBTC08_ERROR_COMMUNICATION, "communication"}
  };
  auto i = error.find(x);
  if (i == error.end()) cpp11::stop("invalid integer `%d` value for error", x);
  return i->second;
}

/*
 * Some interface functions answer negative integer values for logical success
 * or failure results.
 */
static bool logical_(int x) {
  if (x < 0) cpp11::stop("invalid integer `%d` value for logical", x);
  return x > 0;
}

[[cpp11::register]] int16_t open_() {
  return usb_tc08_open_unit();
}

[[cpp11::register]] int16_t open_async_() {
  return usb_tc08_open_unit_async();
}

[[cpp11::register]] cpp11::integers open_progress_() {
  int16_t handle, percent;
  cpp11::writable::integers x{usb_tc08_open_unit_progress(&handle, &percent)};
  x.attr("handle") = handle;
  x.attr("percent") = percent;
  return x;
}

/*
 * Uses type `char` rather than `int8_t` because `cpp11` with therefore perform
 * a character vector transformation automatically; no need for an enumeration
 * look up, especially so since the Windows header does **not** define the
 * thermocouple types.
 */
[[cpp11::register]] bool set_channel_(int16_t handle, int16_t channel, char tc_type) {
  return logical_(usb_tc08_set_channel(handle, channel, tc_type));
}

/*
 * Yes, the return value has a 32-bit width even though it only carries a
 * Boolean type status code: 1 for success, 0 for failure.
 */
[[cpp11::register]] int32_t run_(int16_t handle, int32_t interval) {
  return usb_tc08_run(handle, interval);
}

[[cpp11::register]] int16_t stop_(int16_t handle) {
  return usb_tc08_stop(handle);
}

/*
 * The length argument is the maximum length of the timed-temperature buffers,
 * not the actual; it acts as the reserve capacity, up to but not exceeding it.
 * Ignore the sign by assuming positive lengths only, design-by-contract style.
 *
 * The order of the resulting data frame does not matter too much. Still, order
 * time in milliseconds within the first column and then the temperature as the
 * second data-frame column. This ordering follows a horizontal by vertical
 * orientation for when plotting.
 *
 * The functional template becomes necessary because the interface headers by
 * Rico Technologies introduce important differences between Linux and Windows.
 * Buffer length and millisecond times have type `int32_t` on Windows but have
 * type `long` on Linux. On 64-bit platforms however, long integers are 64 bits
 * wide. Note the following results compiled indirectly via R's `cpp11` on
 * 64-bit Linux using the standard toolchain.
 *
 *  > cpp11::cpp_eval("sizeof(int16_t)")
 *  [1] 2
 *  > cpp11::cpp_eval("sizeof(int32_t)")
 *  [1] 4
 *  > cpp11::cpp_eval("sizeof(long)")
 *  [1] 8
 */
template<typename T>
static cpp11::data_frame get_temp(T (*get_temp)(int16_t, float *, T *, T, int16_t *, int16_t, int16_t, int16_t),
                                  int16_t handle, int32_t length, int16_t channel, std::string units, bool fill) {
  int16_t overflow;
  auto temp_buffer = new float[length];
  auto time_buffer = new T[length];
  auto nrow = get_temp(handle, temp_buffer, time_buffer, length, &overflow, channel, units_(units), fill);
  using namespace cpp11;
  writable::integers time;
  writable::doubles temp;
  for (auto row = 0; row < nrow; ++row) {
    time.push_back(time_buffer[row]);
    temp.push_back(temp_buffer[row]);
  }
  delete[] temp_buffer;
  delete[] time_buffer;
  writable::data_frame x{
    "time"_nm = time, "temp"_nm = temp
  };
  x.attr("overflow") = cpp11::writable::logicals{overflow};
  return x;
}

[[cpp11::register]] cpp11::data_frame get_temp_(int16_t handle, int32_t length, int16_t channel, std::string units, bool fill) {
  return get_temp(usb_tc08_get_temp, handle, length, channel, units, fill);
}

[[cpp11::register]] cpp11::data_frame get_temp_deskew_(int16_t handle, int32_t length, int16_t channel, std::string units, bool fill) {
  return get_temp(usb_tc08_get_temp_deskew, handle, length, channel, units, fill);
}

/*
 * Converts the result to a logical vector, single scalar element, describing
 * success or failure. Any non-zero value becomes `TRUE` in R, only zero returns
 * `FALSE` for failure.
 */
[[cpp11::register]] cpp11::logicals get_single_(int16_t handle, std::string units) {
  int16_t overflow;
  float temp_buffer[9];
  cpp11::writable::logicals x{logical_(usb_tc08_get_single(handle, temp_buffer, &overflow, units_(units)))};
  if (!cpp11::r_bool(x[0])) cpp11::stop(error_(usb_tc08_get_last_error(handle)));
  x.attr("temp") = cpp11::writable::doubles(temp_buffer, temp_buffer + sizeof(temp_buffer)/sizeof(temp_buffer[0]));
  x.attr("overflow") = overflow;
  return x;
}

[[cpp11::register]] int16_t close_(int16_t handle) {
  return usb_tc08_close_unit(handle);
}

[[cpp11::register]] int16_t get_last_error_(int16_t handle) {
  return usb_tc08_get_last_error(handle);
}
