PKG_CXXFLAGS= \
	-I$(SAPID_DEST)/include \
	-DSAPID_AR4_KERNEL \
	$(shell Rscript -e "Rcpp:::CxxFlags()") \
	-I$(shell Rscript -e "cat(R.home())")/include

PKG_LIBS= \
	-lSapidSMU \
	-lSapidAR4 \
	-lSapidPIDB \
	-lSapidUtil \
	-L$(SAPID_DEST)/lib \
	$(shell Rscript -e "Rcpp:::LdFlags()") \
	-L$(shell Rscript -e "cat(R.home())")/lib \
	-lR \
	-DSAPID_AR4_KERNEL

SOURCE= \
	TestMain.cc \
	../src/SapidFunctionCallList.cc \
	SapidFunctionCallListTest.cc 

#ARCH=$(shell arch)
ARCH=x86_64

test:
	g++ -arch $(ARCH) -lgtest $(PKG_CXXFLAGS) $(PKG_LIBS) $(SOURCE) -o test 

