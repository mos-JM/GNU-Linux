compilacion: 
Generacion lib estatica:Se copia parte de la librería en los programas cuando se compilan. programa ocupa más espacio en disco, consume más RAM en ejecución,se ejecuta en principio más rápido .
Si una biblioteca que se utilizó durante la compilación se actualizara, sería necesario recompilar el programa para que incluyera los cambios que se han realizado en esa biblioteca.

	gcc -c tiempo.c
	ar cr libtiempo.a tiempo.o
	gcc -o app main.c -L. -ltiempo -lrt

Lib dinamica:
También llamadas compartidas. Extensión .so (shared object). el programa sólo incluye en su código referencias a las bibliotecas, que se localizan en otra parte. 
En ocasiones las actualizaciones de bibliotecas no son compatibles. Gran cantidad de dependencias entre librerías compartidas.

	gcc -c -fPIC tiempo.c
	gcc -shared -fPIC -o libtiempo.so tiempo.o


gcc -L/home/<directorio> -Wall -o appdynamic main.c -ltiempo -lrt

 echo $LD_LIBRARY_PATH
LD_LIBRARY_PATH=/home/<directorio>:$LD_LIBRARY_PATH
