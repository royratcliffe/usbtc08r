#include "code.h"

[[cpp11::register]] int16_t open_() {
  return usb_tc08_open_unit();
}

[[cpp11::register]] int16_t open_async_() {
  return usb_tc08_open_unit_async();
}

[[cpp11::register]] cpp11::writable::integers open_progress_() {
  int16_t handle, percent;
  int16_t progress = usb_tc08_open_unit_progress(&handle, &percent);
  return cpp11::writable::integers{progress, handle, percent};
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
