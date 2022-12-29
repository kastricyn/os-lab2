obj-m += maks.o
 
all: build-pedantic
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm -f my_user my_user_p

build-pedantic: my_user.c
	gcc -pedantic-errors -Wall -Werror -g3 -O0 --std=c99 my_user.c -o my_user

build: my_user.c
	gcc my_user.c -o my_user