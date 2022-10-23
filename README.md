
<!-- README.md is generated from README.Rmd. Please edit that file -->

# USB 8-Channel Thermocouple for R (`usbtc08r` Package)

<!-- badges: start -->

[![Lifecycle:
experimental](https://img.shields.io/badge/lifecycle-experimental-orange.svg)](https://lifecycle.r-lib.org/articles/stages.html#experimental)
[![CRAN
status](https://www.r-pkg.org/badges/version/usbtc08r)](https://CRAN.R-project.org/package=usbtc08r)
[![R-CMD-check](https://github.com/royratcliffe/usbtc08r/actions/workflows/R-CMD-check.yaml/badge.svg)](https://github.com/royratcliffe/usbtc08r/actions/workflows/R-CMD-check.yaml)
<!-- badges: end -->

The goal of the R package `usbtc08r` is to provide the thinnest amount
of software wrapping between R and the Pico Technology TC-08 via C++.
The package acts as a thin shimming layer. While it provides access for
R to the underlying vendor interface with suitable mapping between C
types and R types, the package also adds higher-level functions that
operate using the vendor interface, e.g. synchronous and non-synchronous
initialisation.

## Installation

You can install the development version of `usbtc08r` as follows,
starting with `devtools` if not already installed:

``` r
install.packages("devtools")
remotes::install_github("royratcliffe/usbtc08r", "main")
```

Before installation can succeed, you first need to install Pico
Technology’s `libusbtc08` driver library. Install the PicoSDK on
Windows, or macOS, but install using Aptitude as the package
`libusbtc08-dev` on Linux. The build process needs access to the
driver’s header files and shared library; hence the `dev` package for
the headers.

### Rtools on Windows

You need [Rtools](https://cran.r-project.org/bin/windows/Rtools/) to
build the package on Windows. The package includes C++, so needs the
compiler toolchain. Check for package build problems using the
`pkgbuild` package.

``` r
pkgbuild::check_build_tools(debug = TRUE)
```

## Example

Connect one or more Pico TC-08 devices to your computer and initialise
using the exemplar code listed below:

``` r
library(usbtc08r)

usb_tc08_open_async()
tc08 <- usb_tc08_open_async_complete()
apply(expand.grid(unit = tc08, channel = 1:8), 1L, function(x)
  usb_tc08_set_channel(x$unit, x$channel, "K"))
lapply(tc08, usb_tc08_run, 1000L)
```

This snippet opens all attached TC-08 devices, one or more, for
asynchronous temperature sampling. Opening starts and opening itself
runs asynchronously until complete. The result is a list of device unit
handles. The snippet expands the list by channel for channels one
through eight and applies a channel set request to each unit channel for
K-type thermocouple and enables each one. Finally, it runs each unit
with a 1,000-millisecond sampling interval or one sample continuously
for all enabled channels every second.

The Pico Technology eight-channel thermocouple in asynchronous mode
outputs time-stamped temperatures in buffered blocks. Buffered blocks of
timed temperatures comprise an ordered list of time-temperature pairs.
Time stamps have millisecond dimensions relative to the start of the
asynchronous sampling process. The thermocouple instrument continuously
samples its channels internally, filling an internal buffer until the
connected host reads the buffer over USB.

Once set up, a task needs to periodically read the channels along the
following lines.

``` r
unit.chan <- expand.grid(unit = tc08, channel = 0:8)
repeat {
  time.temps <- Filter(function(df)
    nrow(df) != 0L, apply(unit.chan, 1L, function(x, length, ...)
      usb_tc08_get_temp_deskew(x$unit, length, x$channel, ...),
      10L, "centigrade", FALSE, simplify = FALSE))
  if (length(lapply(time.temps, function(df) {
    key <- sprintf("pico:tc08:%d:%d", attr(df, "handle"), attr(df, "channel"))
    apply(df, 1L, function(row) cat(key, row["time"], row["temp"], "\n"))
  })) == 0L) Sys.sleep(0.1)
}
```

This example calls `usb_tc08_get_temp_deskew` but the interface also
makes equivalent `usb_tc08_get_temp` available. Both functions read the
temperature buffers. The repeat loop applies “get temp” to the unit
channel grid, thereby running once for each unit-channel permutation.
Channels have indices 0 through 8 inclusive. The calls ask for 10
samples at a time in Centrigrade units. The result is a list of
time-temperature data frames. The snippet filters out empty frames. The
second half of the repeat loop outputs the times and temperatures by row
for each non-empty data frame; else sleeps for 100 milliseconds if all
empty. The sleep idles the task for a short while but only if nothing at
all reads from any attached device. Call this a greedy approach: crunch
until nothing left to eat.

## Unit Behaviour, Synchronous and Asynchronous

Each unit comprises nine channels. Strictly speaking, using Unified
Modelling nomenclature, units *compose* of channels; the lifetime of the
channel strictly depends on its unit. Units “have” channels, the
[stronger form of
aggregation](https://www.uml-diagrams.org/composition.html).

Units have two modes of operation: synchronous and asynchronous. The
difference between these modes extends beyond the driver threading
model. A unit itself switches mode accordingly and precludes behaviours
from the non-operating mode. Specifically, asking for a single sample
set fails when running asynchronously. Software experimentation quickly
discovers this limitation, or feature, which impacts driver acquisition
design.

Asynchronous mode switches the unit into a more advanced form of
temperature data collection where the Pico Technology firmware records
time-stamped temperature readings for all its enabled channels. By
implication, therefore, channel set-up always precedes acquisition; nor
can set-up interlace with asynchronous running. Switching thermocouple
types requires a shutdown and re-start.

## Trapping errors

The R functions wrap ‘error trapping’ by performing two important
sub-duties:

1.  detect errors by testing return values and thereby discern non-error
    values and their meaning;
2.  translate error codes to R exceptions thereby making it easier to
    plot execution paths in client-level user code.

Generally speaking, the driver interface functions have *signed* 16-bit
integer return values returning positive values on success, and negative
on failure.

## References

Useful links are below.

- [TC-08 thermocouple data
  logger](https://www.picotech.com/data-logger/tc-08/thermocouple-data-logger),
  manufacturer’s page
- [Linux Software & Drivers for Oscilloscopes and Data
  Loggers](https://www.picotech.com/downloads/linux)
- [Pico Technology at GitHub](https://github.com/picotech), Pico
  Technology GitHub organisation
- [Pico SDK C examples at
  GitHub](https://github.com/picotech/picosdk-c-examples/tree/master/usbtc08),
  manufacturer’s C examples
- [USB TC-08 Thermocouple Data Logger MATLAB
  Examples](https://github.com/picotech/picosdk-usbtc08-matlab-examples),
  manufacturer’s MATLAB examples
- [libusbtc08-1—Hardware interface library for PicoTech USB TC08
  Thermocouple sensor](https://reposcope.com/package/libusbtc08-1),
  Linux repositories inspector
