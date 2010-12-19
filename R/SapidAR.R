spdUseModel <- function(modelId) {
  print(modelId)
  ret <- .C("spdUseModel_wrapper", arg1=as.integer(modelId), arg2=0)
  print(ret)
}

spdFunctionDefList <- function() {
  flist <- .Call("spdFunctionDefList")
  print(flist)
  return(flist)
}
