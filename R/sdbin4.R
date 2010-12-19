.onLoad <- function(lib, pkg) {
  library.dynam("command_wrapper.so", pkg, lib)
  library.dynam("SapidAR4Wrapper.so", pkg, lib)
  library.dynam("RSapid.so", pkg, lib)
}

sdb4 <- function(filelist, sdbDirectory="SDB", targetProgramName="a.out") {
  command <- paste("-sdbd", sdbDirectory, "-o", targetProgramName, sep=" ")
  files <- ""
  for (file in filelist)
    files <- paste(files, file, sep=" ")
  command <- paste(command,  files, sep=" ")
  print(command)
  result <- .C("sdb4_wrapper", arg1=command, arg2=0)
  print(result)
}
