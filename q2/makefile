all:	p1f	p2f	p1s	p2s	p1shm	p2shm

p1f:
	gcc -w -o ./fifo/p1f ./fifo/p1.c
p2f:
	gcc -w -o ./fifo/p2f ./fifo/p2.c
p1s:
	gcc -w -o ./sockets/p1s ./sockets/p1.c
p2s:
	gcc -w -o ./sockets/p2s ./sockets/p2.c
p1shm:
	gcc -w -o ./shared_mem/p1shm ./shared_mem/p1.c
p2shm:
	gcc -w -o ./shared_mem/p2shm ./shared_mem/p2.c


clean:
	rm ./fifo/p1f ./fifo/p2f
	rm ./sockets/p1s ./sockets/p2s
	rm ./shared_mem/p1shm ./shared_mem/p2shm