all: sequential pthread openmp

sequential : mmult_sequential.c
	gcc -o sequential mmult_sequential.c
	
pthread : mmult_pthread.c
	gcc -o pthread mmult_pthread.c -lpthread

openmp : mmult_openmp.c
	gcc -o openmp mmult_openmp.c -fopenmp

clean : 
	rm sequential pthread openmp
