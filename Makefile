CFLAGS = -Wall -Wextra

all: mmseq mmpthread mmomp nnseq nnpthread nnomp

debug: CFLAGS += -DDEBUG -g
debug: all

mmseq : 
	gcc $(CFLAGS) -o mmseq MatMul/mmseq.c
	
mmpthread :
	gcc $(CFLAGS) -o mmpthread MatMul/mmpthread.c MatMul/matrix.c -lpthread

mmomp : 
	gcc $(CFLAGS) -o mmomp MatMul/mmomp.c -fopenmp

nnseq :
	gcc $(CFLAGS) -o nnseq Neighbor/nnseq.c
	
nnpthread : 
	gcc $(CFLAGS) -o nnpthread Neighbor/nnpthread.c Neighbor/matrix.c -lpthread
	
nnomp : 
	gcc $(CFLAGS) -o nnomp Neighbor/nnomp.c -fopenmp

clean : 
	rm mmseq mmpthread mmomp nnseq nnpthread nnomp
