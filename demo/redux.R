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
r <- hiredis()
repeat {
  for (df in apply(expand.grid(unit = tc08, channel = 0:8), 1L, function(x, length, ...)
    usb_tc08_get_temp_deskew(x$unit, length, x$channel, ...), 10L, "centigrade", FALSE)) {
    if (nrow(df) != 0L) {
      key <- sprintf("pico:tc08:%d:%d", attr(df, "handle"), attr(df, "channel"))
      for (row in 1:nrow(df)) {
        r$command(list("XADD", key, "*", "time", df[row, "time"], "temp", df[row, "temp"]))
      }
    }
  }
}
