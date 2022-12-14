% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/code.R
\name{usb_tc08_get_single}
\alias{usb_tc08_get_single}
\title{Synchronously samples all enabled channels.}
\usage{
usb_tc08_get_single(x, units)
}
\arguments{
\item{x}{Opened synchronous-mode TC-08 unit.}

\item{units}{Units for resulting temperatures.}
}
\value{
Logically \code{TRUE} on success. The logical vector has two
additional attributes.
\describe{
\item{\code{temp}}{Temperatures, nine in total, one for each channel plus
the CJC or Cold-Junction Compensation.}
\item{\code{overflow}}{Overflow flags, an integer carrying a nine-bit
mask encoding channel overflow flags.}
}
}
\description{
Synchronously samples all enabled channels.
}
