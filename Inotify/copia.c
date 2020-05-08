
#include "copia.h"



int copia (int fdo , int fdd ){
  int n;
  while ( (n=read(fdo, array, TAM_BLOQUE)) > 0 )
  {
     if (write(fdd, array , n) != n)
     {
     	perror("Error en write");
	 }
  }   

	return n;
}         

/*int copynFile(FILE * origin, FILE * destination){
	int nCopy=0;
	char c;

	  // Copiar todo el contenido del fichero origen, byte a byte, al destino.
	  // Devolvemos en nCopy los bytes copiados.
	  while( nCopy<INT_MAX && (c=getc(origin))!=EOF ){
	    putc((unsigned char)c, destination);
	    nCopy++;
	  }
	  return(nCopy);

*/
