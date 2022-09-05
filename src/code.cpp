#include <Rcpp.h>

#if defined(linux)
#include <libusbtc08-1.7/TC08Api.h>
#else
#include <usbtc08.h>
#endif

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
