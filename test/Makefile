PKG_CXXFLAGS= \
	-I$(SAPID_DEST)/include \
	-DSAPID_AR4_KERNEL \
	$(shell Rscript -e "Rcpp:::CxxFlags()") \
	-I$(shell Rscript -e "cat(R.home())")/Resources/include

PKG_LIBS= \
	-lSapidSMU \
	-lSapidAR4 \
	-lSapidPIDB \
	-lSapidUtil \
	-L$(SAPID_DEST)/lib \
	$(shell Rscript -e "Rcpp:::LdFlags()") \
	-L$(shell Rscript -e "cat(R.home())")/Resources/lib \
	-lR \
	-DSAPID_AR4_KERNEL

SOURCE= \
	TestMain.cc \
	../src/SapidFunctionCallList.cc \
	SapidFunctionCallListTest.cc 

test:
	g++ -arch x86_64 -lgtest $(PKG_CXXFLAGS) $(PKG_LIBS) $(SOURCE) -o test 

