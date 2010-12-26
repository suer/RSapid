PKG_CXXFLAGS=-I$(SAPID_DEST)/include -DSAPID_AR4_KERNEL \
							$(shell Rscript -e "Rcpp:::CxxFlags()") \
							-I/Library/Frameworks/R.framework/Resources/include \
							-I/Library/Frameworks/R.framework/Resources/include/x86_64 \
							-I/Library/Frameworks/R.framework \
							-I/Library/Frameworks/R.framework/Versions/2.10/Resources/include

PKG_LIBS=-lSapidSMU -lSapidAR4 -lSapidPIDB -lSapidUtil -L$(SAPID_DEST)/lib \
					$(shell Rscript -e "Rcpp:::LdFlags()") \
					-L/usr/local/lib \
					-L/Library/Frameworks/R.framework/Resources/lib/x86_64 \
					-DSAPID_AR4_KERNEL
	
SOURCE= \
	TestMain.cc \
	../src/SapidFunctionCallList.cc \
	SapidFunctionCallListTest.cc 

test:
	g++ -arch x86_64 -lgtest $(PKG_CXXFLAGS) $(PKG_LIBS) $(SOURCE) -o test 

