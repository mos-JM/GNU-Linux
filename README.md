# OS-Linux
Sistemas Operativos

- Temporización:
  El objetivo es familiarizarse con los mecanismos de temporizacion que ofrece el sistema. 
  - Relojes del sistema
  - Temporización de aplicaciones
  - Llamadas al sistema y de libreria relacionada
 
- Sincronización de directorios usando inotify:
  Sincronizacion de dos directorios. El programa lee un fichero de configuracion "sincro.conf" que reside en el directorio HOME
  En dicho fichero hay dos lineas de texto indicando el dir_origen y el dir_destino.Si el directorio origen no existe,
  el programa reportará al usuario un error y finalizará. Si el directorio destino no existe, el programa lo creará (llamada al sistema mkdir).

-  Creación de un demonio:
  Contonuando con el apartado de sincronización, creamos un demonio que periodicamente, comprueba si los directorios estan sincronizados 
  y los soncronice en caso de ser necesario.
  
  
