.onLoad <- function(libname, pkgname) {
  assign("ERROR", error(), pos = asNamespace(pkgname))
}
