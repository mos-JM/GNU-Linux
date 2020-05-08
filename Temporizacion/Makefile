CC = gcc
#SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
#MIAPP = $(OBJ:.o=.elf)
#LDFLAGS = -lm

LDFLAGS = -lrt
CFLAGS = -O3
#$(MIAPP) : $(OBJ)





all: appstatic.elf appdynamic.elf

appstatic.elf: 
	$(CC) -c tiempo.c
	ar cr libtiempo.a tiempo.o
	$(CC) -o $@ main.c -L. -ltiempo -lrt

appdynamic.elf : 
	$(CC) -c -fPIC tiempo.c
	$(CC) -shared -fPIC -o libtiempo.so tiempo.o
	$(CC) -L. -Wall -o $@ main.c -L. -ltiempo -lrt

install:
	sudo cp ./libtiempo.so /usr/lib/
clean:
	rm $(binaries) *.o *.elf *.a *.so
