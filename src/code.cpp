#include <Rcpp.h>
#include <usbtc08.h>

using namespace Rcpp;

//' Open Unit
//' @export
// [[Rcpp::export]]
int open_unit() {
  return usb_tc08_open_unit();
}

//' Open Unit Asynchronously
//' @export
// [[Rcpp::export]]
int open_unit_async() {
  return usb_tc08_open_unit_async();
}

//' Open Unit Progress
//' @export
// [[Rcpp::export]]
List open_unit_progress() {
  short handle, percent_progress;
  auto x = List::create();
  switch (usb_tc08_open_unit_progress(&handle, &percent_progress)) {
  case USBTC08_PROGRESS_PENDING:
    x["progress"] = "pending";
    x["percent"] = percent_progress;
    break;
  case USBTC08_PROGRESS_COMPLETE:
    x["progress"] = "complete";
    break;
  case USBTC08_PROGRESS_FAIL:
    x["progress"] = "fail";
  }
  x["handle"] = handle;
  return x;
}

//' Get Last Error
//' @export
// [[Rcpp::export]]
int get_last_error(int handle) {
  return usb_tc08_get_last_error(handle);
}
