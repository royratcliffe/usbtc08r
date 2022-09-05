#include <Rcpp.h>
#include <usbtc08.h>

using namespace Rcpp;

//' Open Unit
//' @export
// [[Rcpp::export]]
int open_unit() {
  return usb_tc08_open_unit();
}

//' Get Last Error
//' @export
// [[Rcpp::export]]
int get_last_error(int handle) {
  return usb_tc08_get_last_error(handle);
}
