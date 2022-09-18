
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

You can install the development version of `usbtc08r` like so, starting
with `devtools` if not already installed:

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
