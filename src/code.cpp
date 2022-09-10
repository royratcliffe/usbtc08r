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

/*
 * The length argument is the maximum length of the timed-temperature buffer,
 * not the actual; it acts as the reserve capacity, up to but not exceeding.
 * Ignore the sign by assuming positive lengths only, design-by-contract style.
 */
static cpp11::data_frame get_temp(int32_t (*get_temp)(int16_t, float *, int32_t *, int32_t, int16_t *, int16_t, int16_t, int16_t),
                                  int16_t handle, int32_t length, int16_t channel, int16_t units, int16_t fill) {
  int16_t overflow;
  auto temp_buffer = new float[length];
  auto time_buffer = new int32_t[length];
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
