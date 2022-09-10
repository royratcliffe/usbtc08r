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
  handle <- open_()
  if (handle < 0L) stop(error_(get_last_error_(0L)))
  if (handle > 0L) structure(handle, class = c("sync_tc08", "tc08"))
}

#' Starts opening TC-08 units asynchronously
#' @description Asynchronously opens all as-yet-unopened TC-08 units.
#' @details The underlying driver must return 1 as success. All other return
#'   values trigger an exception, even if not zero. Negative return values occur
#'   if another attempt to start the asynchronous opening procedure happens.
#'   Open only once.
#' @export
usb_tc08_open_async <- function()
  if (open_async_() != 1L) stop(error_(get_last_error_(0L)))

#' Progressively opens TC-08 units for asynchronous-mode operations
#' @export
usb_tc08_open_progress <- function() {
  progress <- open_progress_()
  if (progress < 0L) stop(error_(get_last_error_(0L)))
  handle <- attr(progress, "handle")
  if (handle > 0L) structure(handle, class = c("async_tc08", "tc08"))
}

#' Sets a channel thermocouple type
#' @param x TC-08 unit, synchronous or asynchronous mode.
#' @param channel Channel to set.
#' @param tc_type Type of thermocouple. Must be an integer, not a character.
#' @export
usb_tc08_set_channel <- function(x, ...) UseMethod("usb_tc08_set_channel", x)

#' @export
usb_tc08_set_channel.tc08 <- function(x, ...) set_channel_(x, ...)

#' Closes TC-08 unit
#' @param x Open TC-08 unit.
#' @export
usb_tc08_close <- function(x) UseMethod("usb_tc08_close", x)

#' @export
usb_tc08_close.tc08 <- function(x) close_(x)

#' Gets last error of TC-08 unit
#' @param x Open TC-08 unit.
#' @export
usb_tc08_get_last_error <- function(x) UseMethod("usb_tc08_get_last_error", x)

#' @export
usb_tc08_get_last_error.tc08 <- function(x) get_last_error_(x)
