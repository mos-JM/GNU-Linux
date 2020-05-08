#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mytar.h"

extern char *use;

/** Copy nBytes bytes from the origin file to the destination file.
 *
 * origin: pointer to the FILE descriptor associated with the origin file
 * destination:  pointer to the FILE descriptor associated with the destination file
 * nBytes: number of bytes to copy
 *
 * Returns the number of bytes actually copied or -1 if an error occured.
 */

//return numero de bytes contados
int
copynFile(FILE * origin, FILE * destination, int nBytes)
{
	int nCopy=0;
	char c;

	  // Copiar todo el contenido del fichero origen, byte a byte, al destino.
	  // Devolvemos en nCopy los bytes copiados.
	  while( nCopy<nBytes && (c=getc(origin))!=EOF ){
	    putc((unsigned char)c, destination);
	    nCopy++;
	  }
	  return(nCopy);

	/*int nCopy = 0; // contador de bytes
	int c; 			// para leer con getc

	while(nCopy < nBytes && (c = getc(origin) != EOF)){
		putc((unsigned char)c, destination);
		nCopy++;
	}

	return nCopy;*/
}
/*
int
numBytes(const FILE * origin)
{
	int size = 0;
	int c;

	while((c = getc(origin)) != EOF){
		size++;
	}
	return size;
}
*/

/** Loads a string from a file.
 *
 * file: pointer to the FILE descriptor 
 * 
 * The loadstr() function must allocate memory from the heap to store 
 * the contents of the string read from the FILE. 
 * Once the string has been properly built in memory, the function returns
 * the starting address of the string (pointer returned by malloc()) 
 * 
 * Returns: !=NULL if success, NULL if error
 */
//desempaquetado, file es archivo tar
char*
loadstr(FILE * file)
{
	int n , size = 0;
	char * buf; // array

	//cañculamos el tamaño de la cadena
	do {
		n = getc(file); //leemos 1º caracter
		size++;
	} while (( n != (int) '\0') && (n != EOF));  //cast

	if (n == EOF)  // si no hay nada para leer devuelve null
		return NULL;

	buf = (char*)malloc(size); // creamos el array de tamaño

	//traemos el contador al principio
	fseek(file, -size, SEEK_CUR);
	//ahora leemos file de tamaño size de 1 byte y guardamos en buf
	fread(buf, 1, size, file);

	return buf;
}

/** Read tarball header and store it in memory.
 *
 * tarFile: pointer to the tarball's FILE descriptor 
 * nFiles: output parameter. Used to return the number 
 * of files stored in the tarball archive (first 4 bytes of the header).
 *
 * On success it returns the starting memory address of an array that stores 
 * the (name,size) pairs read from the tar file. Upon failure, the function returns NULL.
 * extraer
 */
stHeaderEntry*
readHeader(FILE * tarFile, int *nFiles)
{
	int i;
	stHeaderEntry* header;

	// Leemos el número de ficheros (N) del tarFile y lo copiamos en nFiles
	fread(nFiles, sizeof(int) , 1, tarFile);

	/* Reservamos memoria para el array */
	header = (stHeaderEntry *) malloc(sizeof (stHeaderEntry) * (*nFiles));

	/* usamos loadstr para cargar el nombre en header[i].name
	... comprobación y tratamiento de errores
	... leemos el tamaño del fichero y lo almacenamos en header[i].size*/
	for(i = 0; i < *nFiles; ++i) {
		if ((header[i].name = loadstr(tarFile)) == NULL){
			perror("Error al cargar nombre");
			fclose(tarFile);
			return NULL;
		}
		//leo el tamaño
		fread(&header[i].size, sizeof(header[i].size), 1, tarFile);
	}

	return header;


	  //y si hacemnos esto directamente
	  //fread(*header,sizeof(stHeaderEntry), *nFiles,  tarFile);
		//fread (copio en memoria a partir de,de tamaño, leer nitems, de este fichero



}

/** Creates a tarball archive 
 *
 * nfiles: number of files to be stored in the tarball
 * filenames: array with the path names of the files to be included in the tarball
 * tarname: name of the tarball archive
 * 
 * On success, it returns EXIT_SUCCESS; upon error it returns EXIT_FAILURE. 
 * (macros defined in stdlib.h).
 *
 * HINTS: First reserve room in the file to store the tarball header.
 * Move the file's position indicator to the data section (skip the header)
 * and dump the contents of the source files (one by one) in the tarball archive. 
 * At the same time, build the representation of the tarball header in memory.
 * Finally, rewind the file's position indicator, write the number of files as well as 
 * the (file name,file size) pairs in the tar archive.
 *
 * Important reminder: to calculate the room needed for the header, a simple sizeof 
 * of stHeaderEntry will not work. Bear in mind that, on disk, file names found in (name,size) 
 * pairs occupy strlen(name)+1 bytes.
 *
 */
int
createTar(int nFiles, char *fileNames[], char tarName[])
{

	int i;
	FILE  *inputFile, *mtar;
	stHeaderEntry *header;

	//abrimos el fichero mtar para escritura
	mtar = fopen(tarName, "w");
	//Validamos que el fichero se abra correctamente
	if(mtar == NULL){
		  fprintf(stderr,"El fichero: %s no se ha abierto correctamente \n", tarName); //Mostramos un mensaje de error
		  perror(NULL);
		  return(EXIT_FAILURE);
	  }

	// Reservamos memoria para el array //
	header = (stHeaderEntry *) malloc(sizeof (stHeaderEntry) *nFiles);
	//if header  == NULL

	fseek(mtar,sizeof (int)+sizeof(stHeaderEntry)*nFiles,SEEK_SET);//con SEEK_SET indicamos que es el inicio del fichero


	  // copio los datos de los ficheros , crando el struct
	  for(i=0; i<nFiles; i++) {
		  //abrimos fichero a copiar
		  inputFile = fopen(fileNames[i], "rb");

		  // numero de caracteres hasta nulo
		  header[i].name = malloc(strlen(fileNames[i]) + 1);
		  //copiamos la cabecera a header nombre , size
		  strcpy(header[i].name, fileNames[i]);

		  if(inputFile==NULL){
			  fprintf(stderr,"El fichero %s no se ha podido abrir  \n", fileNames[i]);
			  perror(NULL);
			  free(header);
			  fclose(mtar);
			  remove(tarName);
			  return(EXIT_FAILURE);
		  }

		 // fseek(mtar,sizeof (int)+sizeof(stHeaderEntry)*nFiles,SEEK_SET);
		  //Copiamos el fichero origen al fichero TAR
		  header[i].size = copynFile(inputFile,mtar,INT_MAX);
		  fclose(inputFile);
	  }


	  // Escribimos al fichero mtar la cabecera
	  //fseek(mtar,sizeof (int)+sizeof(stHeaderEntry)*nFiles,SEEK_SET);
	  rewind(mtar);  //(void) fseek( stream, 0L, SEEK_SET ) fseek(fileNames[i], -size, SEEK_CUR);
	  fwrite(&nFiles,sizeof(int), 1,  mtar);


	  //fwrite(header,sizeof(stHeaderEntry), nFiles,  mtar);
	 for (i = 0; i < nFiles; i++) {
	  		fwrite(header[i].name, strlen(header[i].name) + 1, 1, mtar);
	  		fwrite(&header[i].size, sizeof (header[i].size), 1, mtar);
	  	}

	  fprintf(stdout, "Archivo %s: comprimido correctamente.\n", tarName);
	  free(header);
	  fclose(mtar);
	  return(EXIT_SUCCESS);


}








/** Extract files stored in a tarball archive
 *
 * tarName: tarball's pathname
 *
 * On success, it returns EXIT_SUCCESS; upon error it returns EXIT_FAILURE. 
 * (macros defined in stdlib.h).
 *
 * HINTS: First load the tarball's header into memory.
 * After reading the header, the file position indicator will be located at the 
 * tarball's data section. By using information from the 
 * header --number of files and (file name, file size) pairs--, extract files 
 * stored in the data section of the tarball.
 *
 */
int
extractTar(char tarName[])
{
	stHeaderEntry *header;
	int nFiles,i;
	FILE *mtar,*outputFile;

	//Abrimos el fichero destino
	mtar = fopen(tarName, "rb");
	if(mtar == NULL) {
	    fprintf(stderr, "El fichero tar %s no se ha podido abrir \n", tarName);
	    perror(NULL);
	    return(-1);
	}

	//Leemos la cabecera del mtar y la metemos en header
	header = readHeader(mtar, &nFiles);
	fseek(mtar,sizeof (int)+sizeof(stHeaderEntry)*nFiles,SEEK_SET);
	//Creamos los ficheros contenidos en el mtar
	for(i = 0; i < nFiles; i++){
		outputFile = fopen(header[i].name, "wb");
	    if(outputFile==NULL) {
	    	fprintf(stderr, "El fichero %s no se ha podido crear. \n", header[i].name);
	    	perror(NULL);
	    	free(header);
	    	fclose(mtar);
	    	return(-1);
	    }

	    printf("[%i]: Creando fichero %s, tamaño %i Bytes...", i, header[i].name, header[i].size);

	    //Copiamos el fichero
	    copynFile(mtar,outputFile,header[i].size);


	    fclose(outputFile);
	    printf("Ok\n");

	}
	free(header);
	fclose(mtar);
	return(EXIT_SUCCESS);

}
