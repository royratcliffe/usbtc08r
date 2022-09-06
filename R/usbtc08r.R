#' Open Units
#' @return Unit handle vector
#' @export
open_units <- function() {
  handles <- NULL
  repeat {
    handle <- open_unit()
    if (handle == 0L) break
    stopifnot("unit handle must be positive" = handle > 0L)
    handles <- c(handles, handle)
  }
  unit(handles)
}

#' Unit
#' @export
unit <- function(x) {
  structure(x, class = "usbtc08")
}

#' Last Error for TC-08 Unit
#' @export
last_error <- function(x, ...) {
  UseMethod("last_error", x)
}
