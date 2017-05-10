CXX = icpc
CFLAGS = -std=c++11 -g -O3 -qopenmp
LD = icpc
OBJS = diagDriver.o diagCommon.o Random64.o
EXES = diagMKL diagGPU

%.o:	%.cpp
	$(CXX) -c $(CFLAGS) $(MAGMA_CFLAGS) $(MKL_CFLAGS) $<

diagMKL:	diagMKL.o $(OBJS)
	$(LD) -o $@ $^ $(MAGMA_LIBS) $(MKL_LIBS)

diagGPU:	diagGPU.o $(OBJS)
	$(LD) -o $@ $^ $(MAGMA_LIBS) $(MKL_LIBS)

.PHONY:	clean
clean:
	rm -f $(EXES) *.o
