CFLAGS = -Wall -Wextra

all: mmult_sequential mmult_pthread mmult_openmp nn_sequential nn_pthread

debug: CFLAGS += -DDEBUG -g
debug: all

mmult_sequential : mmult_sequential.c
	gcc $(CFLAGS) -o mmult_sequential mmult_sequential.c
	
mmult_pthread : test_mmult_pthread.c
	gcc $(CFLAGS) -o mmult_pthread test_mmult_pthread.c matrix.c multiply_pthread.c -lpthread

mmult_openmp : openmm.c
	gcc $(CFLAGS) -o mmult_openmp openmm.c matrix.c multiply_openmp.c -fopenmp

nn_sequential : nnseq.c
	gcc $(CFLAGS) -o nn_sequential nnseq.c
	
nn_pthread : test_neighbor_pthread.c
	gcc $(CFLAGS) -o nn_pthread test_neighbor_pthread.c matrix.c neighbor_pthread.c -lpthread

clean : 
	rm mmult_sequential mmult_pthread mmult_openmp nn_sequential nn_pthread
