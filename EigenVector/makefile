LFLAG = -lgsl -lgslcblas 
SRC = main.cpp generateEigenvector.cpp  countNum.cpp Matrix.cpp
LIBPATH = lib
INCLPATH1 =include


CC=g++
CFLAGS = -g

ALL: $(SRC)
	$(CC) $(SRC) -I $(INCLPATH1) -L $(LIBPATH) $(LFLAG) $(CFLAGS) -o Eigen
clean:
	rm Eigen
