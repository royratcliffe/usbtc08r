# Generated by cpp11: do not edit by hand

units_ <- function(x) {
  .Call(`_usbtc08r_units_`, x)
}

progress_ <- function(x) {
  .Call(`_usbtc08r_progress_`, x)
}

error_ <- function(x) {
  .Call(`_usbtc08r_error_`, x)
}

logical_ <- function(x) {
  .Call(`_usbtc08r_logical_`, x)
}

open_ <- function() {
  .Call(`_usbtc08r_open_`)
}

open_async_ <- function() {
  .Call(`_usbtc08r_open_async_`)
}

open_progress_ <- function() {
  .Call(`_usbtc08r_open_progress_`)
}

set_channel_ <- function(handle, channel, tc_type) {
  .Call(`_usbtc08r_set_channel_`, handle, channel, tc_type)
}

run_ <- function(handle, interval) {
  .Call(`_usbtc08r_run_`, handle, interval)
}

stop_ <- function(handle) {
  .Call(`_usbtc08r_stop_`, handle)
}

get_temp_ <- function(handle, length, channel, units, fill) {
  .Call(`_usbtc08r_get_temp_`, handle, length, channel, units, fill)
}

get_temp_deskew_ <- function(handle, length, channel, units, fill) {
  .Call(`_usbtc08r_get_temp_deskew_`, handle, length, channel, units, fill)
}

get_single_ <- function(handle, units) {
  .Call(`_usbtc08r_get_single_`, handle, units)
}

close_ <- function(handle) {
  .Call(`_usbtc08r_close_`, handle)
}

get_last_error_ <- function(handle) {
  .Call(`_usbtc08r_get_last_error_`, handle)
}
