.First.lib <- function(lib, pkg) {
    print("hoge")
    library.dynam("command_wrapper", pkg, lib)
}
print("hoge")

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

