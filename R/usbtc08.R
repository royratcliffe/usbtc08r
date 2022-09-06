#' @export
channel.usbtc08 <- function(x, channel, tc_type) {
  for (y in channel) set_channel(x, y, tc_type)
}

#' @export
tc_type.usbtc08 <- function(x, ...) {
  args <- list(...)
  tc_type <- names(args)
  for (i in seq_along(args)) {
    for (channel in args[[i]]) {
      set_channel(x, channel, tc_type[i])
    }
  }
}

#' @export
last_error.usbtc08 <- function(x) {
  last <- get_last_error(x)
  arr <- ERROR
  ind <- which(arr == last)
  ifelse(length(ind) == 1L, names(arr[ind]), last)
}
