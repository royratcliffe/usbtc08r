% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/code.R
\name{usb_tc08_set_channel}
\alias{usb_tc08_set_channel}
\title{Sets a channel thermocouple type.}
\usage{
usb_tc08_set_channel(x, channel, tc_type)
}
\arguments{
\item{x}{TC-08 unit, synchronous or asynchronous mode.}

\item{channel}{Channel to set.}

\item{tc_type}{Type of thermocouple. Must be a character, not an integer.
Valid types include: B, E, J, K, N, R, S, T, X or space for channels 1
through 8; where X measures voltage in mV with no cold-junction
compensation, space disables a channel.}
}
\description{
Sets a channel thermocouple type.
}
\details{
Set up the channels \emph{before} running in asynchronous mode.
}
