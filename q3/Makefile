obj-m := custommod.o

custommod.o:
	sudo make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) modules

clean:
	sudo make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) clean  
