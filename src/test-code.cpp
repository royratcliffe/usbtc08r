#include <testthat.h>

#include "code.h"

context("Measurement units") {
  test_that("String to integer works") {
    expect_true(units_("centigrade") == USBTC08_UNITS_CENTIGRADE);
    expect_true(units_("fahrenheit") == USBTC08_UNITS_FAHRENHEIT);
    expect_true(units_("kelvin") == USBTC08_UNITS_KELVIN);
    expect_true(units_("rankine") == USBTC08_UNITS_RANKINE);
  }
}
