library(usbtc08r)
library(redux)

usb_tc08_open_async()
tc08 <- usb_tc08_open_async_complete()
apply(expand.grid(unit = tc08, channel = 1:8), 1L, function(x)
  usb_tc08_set_channel(x$unit, x$channel, "K"))
lapply(tc08, usb_tc08_run, 1000L)

# Continuously acquire de-skewed temperature samples from channels 0 through 8,
# inclusive. The following expression expands all the units and all their
# channels to a list of timed-temperature data frames.
#
#     apply(expand.grid(unit = tc08, channel = 0:8), 1L, function(x, length, ...)
#       usb_tc08_get_temp_deskew(x$unit, length, x$channel, ...), 10L, "centigrade", FALSE)
#
# Note: using the unit handle as an index makes an important assumption about
# the ordering of units; they must always receive the same handle between
# restarts, otherwise unit 1 could become unit 2 at some later point in time.
#
# While this runs, you can use the following commands such as the following to
# read arbitrary temperature streams.
#
#     redux::hiredis()$command(list("XREAD", "STREAMS", "pico:tc08:1:1", "0"))
#
# Run from R Studio as a background job using:
#
#     rstudioapi::jobRunScript(system.file("demo", "redux.R", package = "usbtc08r"))
#
# One more thing to note: grid expanding the unit-channel permutations delivers
# a list of data frames tagged with unit handle and channel attributes. One or
# more resulting data frames may be empty, not null but a valid frame with no
# rows; e.g. `apply(data.frame(a = NULL, b = NULL), 1L, identity)` answers
# `logical(0)`, a zero-length logical vector.
#
# Sleeps if all channels answer nothing but not if at least one channel provides
# some data frame. The device exhibits all-or-nothing behaviour typically: all
# the channels buffer the same number of temperatures. The demo here filters the
# captured temperature frames for empty rows. The demo sleeps for 100
# milliseconds only when all frames prove empty.
unit.chan <- expand.grid(unit = tc08, channel = 0:8)
xadd_time_temp <- function(r, key, row)
  r$command(list("XADD", key, "*", "time", row["time"], "temp", row["temp"]))
r <- hiredis()
repeat {
  time.temps <- Filter(function(df)
    nrow(df) != 0L, apply(unit.chan, 1L, function(x, length, ...)
      usb_tc08_get_temp_deskew(x$unit, length, x$channel, ...),
      10L, "centigrade", FALSE, simplify = FALSE))
  if (length(lapply(time.temps, function(df) {
    key <- sprintf("pico:tc08:%d:%d", attr(df, "handle"), attr(df, "channel"))
    apply(df, 1L, function(row) xadd_time_temp(r, key, row))
  })) == 0L) Sys.sleep(0.1)
}
