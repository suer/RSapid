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


.onLoad <- function(lib, pkg) {
  print("hoge")
#  library.dynam(paste(lib, "libs/command_wrapper", sep="/"), pkg, lib)
  print(lib)
  print(pkg)
  library.dynam("command_wrapper.so", pkg, lib)
#  print(paste(pkg, lib, "command_wrapper", sep="/"))
#  dyn.load(paste(lib, pkg, "libs/command_wrapper.so", sep="/"))
}
