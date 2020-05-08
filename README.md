# OS-Linux
Sistemas Operativos

- **Temporización:**
  El objetivo es familiarizarse con los mecanismos de temporizacion que ofrece el sistema. 
  - Reloj del sistema
  - Temporización de aplicaciones
  - Llamadas al sistema y de libreria relacionada
 
- **Sincronización de directorios usando inotify:**
  Sincronizacion de dos directorios. El programa lee un fichero de configuracion "sincro.conf" que reside en el directorio HOME
  En dicho fichero hay dos lineas de texto indicando el dir_origen y el dir_destino.Si el directorio origen no existe,
  el programa reportará al usuario un error y finalizará. Si el directorio destino no existe, el programa lo creará (llamada al sistema mkdir).

-  **Creación de un demonio:**
  Contonuando con el apartado de sincronización, creamos un demonio que periodicamente, comprueba si los directorios estan sincronizados 
  y los soncronice en caso de ser necesario.
  
- **Creación de un fichero TAR MyTar : **
Herramienta de linea de órdenes llamada mytar, capaz de crear un archivo tarball que contiene varios ficheros, o de extraer los ficheros de un tarball previamente creado.

- **Sistema de ficheros propio (myFUSE):**
Se implementa un conjunto de funciones que dota a este sistema de una funcionalidad mínima. Se usan llamadas al sistema y funciones de biblioteca .
Para ello usamos la biblioteca FUSE1 (Filesystem in Userspace) que proporciona una API sencilla que permite implementar sistemas de ficheros.

- **Planificacion y sincronizacion (Procesos e hilos):**
implementarán distintos algoritmos de planificación en un simulador que refleja con bastante exactitud la estructura de un planificador real.

- **Implementacion de un Driver sensillo en Linux: **
Control de los leds del teclado.

  
