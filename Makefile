CFLAGS = -Wall -Werror -Wextra

all: sequential pthread openmp

debug: CFLAGS += -DDEBUG -g
debug: all

sequential : mmult_sequential.c
	gcc $(CFLAGS) -o sequential mmult_sequential.c
	
pthread : mmult_pthread.c
	gcc $(CFLAGS) -o pthread mmult_pthread.c matrix_pthread.c -lpthread

openmp : mmult_openmp.c
	gcc $(CFLAGS) -o openmp mmult_openmp.c -fopenmp

clean : 
	rm sequential pthread openmp
