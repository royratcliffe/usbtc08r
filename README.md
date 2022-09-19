
<!-- README.md is generated from README.Rmd. Please edit that file -->

# usbtc08r

<!-- badges: start -->

[![Lifecycle:
experimental](https://img.shields.io/badge/lifecycle-experimental-orange.svg)](https://lifecycle.r-lib.org/articles/stages.html#experimental)
[![CRAN
status](https://www.r-pkg.org/badges/version/usbtc08r)](https://CRAN.R-project.org/package=usbtc08r)
[![R-CMD-check](https://github.com/royratcliffe/usbtc08r/actions/workflows/R-CMD-check.yaml/badge.svg)](https://github.com/royratcliffe/usbtc08r/actions/workflows/R-CMD-check.yaml)
<!-- badges: end -->

The goal of usbtc08r is to …

## Installation

You can install the development version of `usbtc08r` as follows,
starting with `devtools` if not already installed:

``` r
install.packages("devtools")
remotes::install_github("royratcliffe/usbtc08r", "royratcliffe-patch-3")
```

Before installation can succeed, you first need to install Pico
Technology’s `libusbtc08` driver library. Install the PicoSDK on
Windows, or on macOS, but install using Aptitude as package
`libusbtc08-dev` on Linux. The build process needs access to the
driver’s header and shared library.

### Rtools on Windows

You need [Rtools](https://cran.r-project.org/bin/windows/Rtools/) to
build the package on Windows. The package includes C++, so needs the
compiler toolchain. Check for package build problems using the
`pkgbuild` package.

``` r
pkgbuild::check_build_tools(debug = TRUE)
```

## Example

This is a basic example which shows you how to solve a common problem:

``` r
library(usbtc08r)
## basic example code
```

## Unit Behaviour, Synchronous and Asynchronous

Each unit comprises nine channels. Strictly speaking, using Unified
Modelling nomenclature, units *compose* of channels; the life time of
the channel strictly depends on its unit. Units “have” channels, the
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
types requires a shut-down and re-start.

## References

-   [libusbtc08-1—Hardware interface library for PicoTech USB TC08
    Thermocouple sensor](https://reposcope.com/package/libusbtc08-1)
-   [Linux Software & Drivers for Oscilloscopes and Data
    Loggers](https://www.picotech.com/downloads/linux)
-   [Pico Technology at GitHub](https://github.com/picotech)
-   [TC-08 thermocouple data
    logger](https://www.picotech.com/data-logger/tc-08/thermocouple-data-logger)
-   [Pico SDK C examples at
    GitHub](https://github.com/picotech/picosdk-c-examples/tree/master/usbtc08)
-   [USB TC-08 Thermocouple Data Logger MATLAB
    Examples](https://github.com/picotech/picosdk-usbtc08-matlab-examples)