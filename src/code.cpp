#include "code.h"

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

[[cpp11::register]] int16_t set_channel_(int16_t handle, int16_t channel, int8_t tc_type) {
  return usb_tc08_set_channel(handle, channel, tc_type);
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
                                  int16_t handle, int32_t length, int16_t channel, int16_t units, int16_t fill) {
  int16_t overflow;
  auto temp_buffer = new float[length];
  auto time_buffer = new T[length];
  auto nrow = get_temp(handle, temp_buffer, time_buffer, length, &overflow, channel, units, fill);
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
  x.attr("overflow") = overflow;
  return x;
}

[[cpp11::register]] cpp11::data_frame get_temp_(int16_t handle, int32_t length, int16_t channel, int16_t units, int16_t fill) {
  return get_temp(usb_tc08_get_temp, handle, length, channel, units, fill);
}

[[cpp11::register]] cpp11::data_frame get_temp_deskew_(int16_t handle, int32_t length, int16_t channel, int16_t units, int16_t fill) {
  return get_temp(usb_tc08_get_temp_deskew, handle, length, channel, units, fill);
}

[[cpp11::register]] int16_t close_(int16_t handle) {
  return usb_tc08_close_unit(handle);
}

[[cpp11::register]] int16_t get_last_error_(int16_t handle) {
  return usb_tc08_get_last_error(handle);
}

[[cpp11::register]] std::string error_(int16_t error) {
  switch (error) {
  case USBTC08_ERROR_OK: return "ok";
  }
  return std::to_string(error);
}
