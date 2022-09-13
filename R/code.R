#' Opens TC-08 unit for synchronous-mode operations.
#' @description Opens the next available closed TC-08 unit. Opens synchronously
#'   and therefore blocks the caller until a USB-connected TC-08 has been found
#'   and opened; a process that might take a second or two.
#' @details Asks for the last error using a zero unit handle if opening fails.
#'   Handles only represent open units so no handle exists for closed units.
#' @return Handle of opened TC-08 unit or \code{NULL} if no more closed units
#'   available for opening.
#' @examples
#' \donttest{
#' tryCatch(usb_tc08_open(), error = function(e) e)
#' }
#' @export
usb_tc08_open <- function() {
  handle <- open_()
  if (handle < 0L) stop(error_(get_last_error_(0L)))
  if (handle > 0L) structure(handle, class = c("sync_tc08", "tc08"))
}

#' Starts opening TC-08 units asynchronously.
#' @description Asynchronously opens all as-yet-unopened TC-08 units.
#'   Automatically asserts success by stopping on error.
#' @details The underlying driver must return 1 as success. All other return
#'   values trigger an exception, even if not zero. Negative return values occur
#'   if another attempt to start the asynchronous opening procedure happens.
#'   Open only once.
#' @export
#' @examples
#' \donttest{
#' library(usbtc08r)
#' usb_tc08_open_async()
#' }
usb_tc08_open_async <- function()
  if (!open_async_()) stop(error_(get_last_error_(0L)))

#' Progressively opens TC-08 units for asynchronous-mode operations.
#' @return Progress string, one of: pending or complete. Does \emph{not} return
#'   \code{"fail"} but raises an exception on failure by asking for the last
#'   error and decoding it for the exception message.
#' @export
usb_tc08_open_progress <- function() {
  progress <- open_progress_()
  if (progress == "fail") stop(error_(get_last_error_(0L)))
  handle <- attr(progress, "handle")
  attr(progress, "handle") <- NULL
  if (handle > 0L)
    attr(progress, "tc08") <- structure(handle, class = c("async_tc08", "tc08"))
  progress
}

#' Opens all TC-08 units asynchronously to completion.
#' @details Runs aggressively with \emph{no} delay between pending progress
#'   results.
#' @return List of TC-08 units opened and ready for set up and running.
usb_tc08_open_async_complete <- function() {
  tc08 <- list()
  repeat {
    progress <- usb_tc08_open_progress()
    tc08[[length(tc08) + 1L]] <- attr(progress, "tc08")
    if (progress != "pending") break
  }
  stopifnot(progress == "complete")
  tc08
}

#' Sets a channel thermocouple type.
#' @details Set up the channels \emph{before} running in asynchronous mode.
#' @param x TC-08 unit, synchronous or asynchronous mode.
#' @param channel Channel to set.
#' @param tc_type Type of thermocouple. Must be a character, not an integer.
#'   Valid types include: B, E, J, K, N, R, S, T, X or space for channels 1
#'   through 8; where X measures voltage in mV with no cold-junction
#'   compensation, space disables a channel.
#' @export
usb_tc08_set_channel <- function(x, channel, tc_type) UseMethod("usb_tc08_set_channel", x)

#' @export
usb_tc08_set_channel.tc08 <- function(x, ...) set_channel_(x, ...)

#' Runs a TC-08 asynchronously.
#' @details Only succeeds when in asynchronous mode. Fails when synchronous. Use
#'   \code{\link[usbtc08r]{usb_tc08_stop}} to stop the run, before closing.
#' @param x TC-08 opened for asynchronous-mode operations.
#' @param interval Sampling interval in milliseconds between the minimum
#'   possible level and 65535ms.
#' @export
usb_tc08_run <- function(x, interval) UseMethod("usb_tc08_run", x)

#' @export
usb_tc08_run.async_tc08 <- function(x, ...) run_(x, ...)

#' Stops an asynchronous TC-08.
#' @param x Opened and running TC-08 in asynchronous mode.
#' @export
usb_tc08_stop <- function(x) UseMethod("usb_tc08_stop", x)

#' @export
usb_tc08_stop.async_tc08 <- function(x, ...) stop_(x, ...)

#' Get temperatures asynchronously.
#' @param x Opened and running TC-08 in asynchronous mode.
#' @export
usb_tc08_get_temp <- function(x) UseMethod("usb_tc08_get_temp", x)

#' @export
usb_tc08_get_temp.async_tc08 <- function(x, ...) get_temp_(x, ...)

#' Get asynchronously-captured de-skewed temperatures.
#' @param x Opened and running TC-08 in asynchronous mode.
#' @export
usb_tc08_get_temp_deskew <- function(x) UseMethod("usb_tc08_get_temp_deskew", x)

#' @export
usb_tc08_get_temp_deskew.async_tc08 <- function(x, ...) get_temp_deskew_(x, ...)

#' Synchronously samples all enabled channels.
#' @param x Opened synchronous-mode TC-08 unit.
#' @param units Units for resulting temperatures.
#' @return Logically \code{TRUE} on success. The logical vector has two
#'   additional attributes.
#'   \describe{
#'     \item{\code{temp}}{Temperatures, nine in total, one for each channel plus
#'       the CJC or Cold-Junction Compensation.}
#'     \item{\code{overflow}}{Overflow flags, an integer carrying a nine-bit
#'       mask encoding channel overflow flags.}
#'   }
#' @export
usb_tc08_get_single <- function(x, units) UseMethod("usb_tc08_get_single", x)

#' @export
usb_tc08_get_single.sync_tc08 <- function(x, ...) get_single_(x, ...)

#' Closes TC-08 unit.
#' @param x Previously opened TC-08 unit.
#' @details Once closed externally, the handle becomes invalid.
#' @export
usb_tc08_close <- function(x) UseMethod("usb_tc08_close", x)

#' @export
usb_tc08_close.tc08 <- function(x) if (close_(x) < 1L) stop(error_(get_last_error_(x)))

#' Gets last error of TC-08 unit.
#' @param x Open TC-08 unit.
#' @export
usb_tc08_get_last_error <- function(x) UseMethod("usb_tc08_get_last_error", x)

#' @export
usb_tc08_get_last_error.tc08 <- function(x) get_last_error_(x)
