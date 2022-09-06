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
  handles
}
