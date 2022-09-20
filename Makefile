a0_q2: a0_q2.o
	gcc -no-pie -o a0_q2 a0_q2.o
a0_q2.o: a0_q2.asm
	yasm -f elf64 -o a0_q2.o a0_q2.asm
