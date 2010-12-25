.onLoad <- function(lib, pkg) {
  library.dynam("RSapid.so", pkg, lib)
}
