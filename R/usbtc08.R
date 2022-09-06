#' @export
last_error.usbtc08 <- function(x) {
  last <- get_last_error(x)
  arr <- error()
  ind <- which(arr == last)
  ifelse(length(ind) == 1L, names(arr[ind]), last)
}
