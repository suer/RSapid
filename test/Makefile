CXXFLAGS= \
	-I$(SAPID_DEST)/include \
	-DSAPID_AR4_KERNEL \
	$(shell Rscript -e "Rcpp:::CxxFlags()") \
	-I$(shell Rscript -e "cat(R.home())")/include \
	-I../src \
	-g

LIBS= \
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

OBJS= \
	../src/SapidFunctionCallList.o \
	SapidFunctionCallListTest.o \
	TestMain.o


#ARCH=$(shell arch)
ARCH=x86_64

#.o:
#	g++ -arch $(ARCH) -lgtest $(CXXFLAGS) $(LIBS) -c $@

test: $(OBJS) 
	g++ -arch $(ARCH) -lgtest $(CXXFLAGS) $(LIBS) $(OBJS) -o test -g

clean:
	rm *.o ../src/*.o test
