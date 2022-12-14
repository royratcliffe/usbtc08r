% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/code.R
\name{usb_tc08_run}
\alias{usb_tc08_run}
\title{Runs a TC-08 asynchronously.}
\usage{
usb_tc08_run(x, interval)
}
\arguments{
\item{x}{TC-08 opened for asynchronous-mode operations.}

\item{interval}{Sampling interval in milliseconds between the minimum
possible level and 65535ms. A lower limit exists depending on the number of
enabled channels; 1000ms interval handles all eight channels.}
}
\description{
Runs a TC-08 asynchronously.
}
\details{
Only succeeds when in asynchronous mode. Fails when synchronous. Use
\code{\link[usbtc08r]{usb_tc08_stop}} to stop the run, before closing.
}
