Para su funcionamiento copiar sinc.conf en home/<user>

para compilar hay que crear el objeto .o de copia.c y sincro.c. y luego el ejecutable usando los dos .o
 gcc -c copia.c
 gcc -c  sincro.c

gcc sincro.o copia.o -o sincro
