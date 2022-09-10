#' Opens TC-08 unit for synchronous-mode operations
#' @description Opens the next available closed TC-08 unit.
#' @details Asks for the last error using a zero unit handle if opening fails.
#'   Handles only represent open units so no handle exists for closed units.
#' @return Handle of opened TC-08 unit or \code{NULL} if no more closed units
#'   available for opening.
#' @examples
#' \dontrun{
#' tryCatch(usb_tc08_open(), error = function(e) e)
#' }
#' @export
usb_tc08_open <- function() {
  handle <- open_unit_()
  if (handle < 0L) stop(error_(get_last_error_(0L)))
  if (handle > 0L) usb_tc08_unit(handle)
}

usb_tc08_unit <- function(handle) structure(handle, class = "usb_tc08_unit")

#' Closes TC-08 unit
#' @param x Open TC-08 unit.
#' @export
usb_tc08_close <- function(x, ...) UseMethod("close", x)

close.usb_tc08_unit <- function(x) close_unit_(x)

#' Gets last error of TC-08 unit
#' @param x Open TC-08 unit.
#' @export
usb_tc08_get_last_error <- function(x, ...) UseMethod("get_last_error", x)

get_last_error.usb_tc08_unit <- function(x) get_last_error_(x)
