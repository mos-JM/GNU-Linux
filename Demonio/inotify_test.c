#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <sys/inotify.h>
#include <signal.h>

#include "event_queue.h"
#include "inotify_utils.h"
#include <syslog.h>
#include <sys/time.h>

int keep_running;
int numEvents;

char *dir_origen;
char *dir_destino;
int segundos;

queue_t q;
/* This is the file descriptor for the inotify watch */
int inotify_fd;


char rutaLock [128];


/* This program will take as arguments one or more directory 
   or file names, and monitor them, printing event notifications 
   to the console. It will automatically terminate if all watched
   items are deleted or unmounted. Use ctrl-C or kill to 
   terminate otherwise.
*/

void alarma (int signo)
{
  //printf("alarma: %d\n", numEvents);
     //char buf[150];
     //sprintf(buf, "%d", numEvents);
     syslog (LOG_INFO, "El numero de eventos hasta ahora son: %d\n", numEvents);
     
};

void * ini_manejador(int signal, void *manejador)
{
    struct sigaction act;
    struct sigaction old_act;

// Inicializar el puntero de la funcion 
    act.sa_handler = manejador; //puntero a funcion y lo mete en sa handler

// Crear el conjunto de seniales en act a vacio 
    sigemptyset(&act.sa_mask);

// Opciones del handler a SA_RESTART 
    act.sa_flags = SA_RESTART;

//cambiar la acción tomada por un proceso cuando recibe una determinada señal.
    sigaction(signal, &act, &old_act);
}

void senalAlarma(int segundos)
{
    struct itimerval it;

// Inicializar el manejador con la funcion ini_manejador  
   ini_manejador(SIGALRM,&alarma);   // cuando llegue SIGALARM, invocare alarm

//inicializo la estructura
  it.it_value.tv_sec = segundos;
  it.it_value.tv_usec = 0;
  it.it_interval.tv_sec = segundos;
  it.it_interval.tv_usec = 0;

// Inicializar el reloj de pared (wall-clock) mediante setitimer 
  if(setitimer(ITIMER_REAL,&it,NULL)==-1){
 	perror("setitimer");
	exit(1);
  }
}



/* Signal handler that simply resets a flag to cause termination */
void signal_handler (int signum)
{
  keep_running = 0;
}



void handler_daemon_clean(int signal)
{
      printf("aqui llega a borrarlo todo\n");
      
      
      numEvents = 0; // no hace falta
      unlink(rutaLock);
      closelog ();
      close_inotify_fd (inotify_fd);
      queue_destroy (q);
      exit(EXIT_SUCCESS);
}

void handler_usr(int signal)
{
	printf("señal sigusr1\n");
	syslog(LOG_INFO, "El numero de eventos hasta ahora son: %d\n", numEvents);
}

void handler_fichero(int signal)
{
	confFicheroConf();
}

int main (int argc, char **argv)
{
  

  keep_running = 1;
  numEvents = 0;

//char *dir_origen;
//char *dir_destino;

/* configuracion sincro.conf origen destino y segundos*/

   /*const char *home;
    char rutaConf [128];

    home = getenv ("HOME");
    strcpy(rutaConf, home);
    strcat(rutaConf, "/sincro.conf");
    
    strcpy(rutaLock, home);
    strcat(rutaLock, "/sincro.lock");

    int fdConf = open (rutaConf, O_RDONLY);
    if(fdConf == -1 ){
       perror("error en archivo de configuracin , no existe");
       exit(1);
    }

    //guardar directorios de configuracion
    char buf[200];
    char ** directorios;
    size_t nbytes;
    //ssize_t bytes_read;
   
    nbytes = sizeof(buf); 
    read(fdConf, buf, nbytes);
  
    directorios = parse(buf);

    dir_origen = directorios[0];
    dir_destino = directorios[1];
    segundos = atoi(directorios[2]) ;*/
   confFicheroConf();

    /*init daemon*/
    daemonize();
    syslog (LOG_NOTICE, "Started.");

   

    confFicheroLock();
	


  //Llamada a init alarma
     senalAlarma(segundos);

  //Señal sigterm
     ini_manejador(SIGTERM, &handler_daemon_clean); 
 
  //Señal sighup
     ini_manejador(SIGHUP, &handler_fichero);



//------------------------------------------------------------------

  /* Set a ctrl-c signal handler */
  if (signal (SIGINT, signal_handler) == SIG_IGN)
    {
      /* Reset to SIG_IGN (ignore) if that was the prior state */
      signal (SIGINT, SIG_IGN);
    }

  /* First we open the inotify dev entry */
  inotify_fd = open_inotify_fd ();
  if (inotify_fd > 0)
    {

      /* We will need a place to enqueue inotify events,
         this is needed because if you do not read events
         fast enough, you will miss them. This queue is 
         probably too small if you are monitoring something
         like a directory with a lot of files and the directory 
         is deleted.
       */
      
      q = queue_create (128);

      /* This is the watch descriptor returned for each item we are 
         watching. A real application might keep these for some use 
         in the application. This sample only makes sure that none of
         the watch descriptors is less than 0.
       */
      int wd;


      /* Watch all events (IN_ALL_EVENTS) for the directories and 
         files passed in as arguments.
         Read the article for why you might want to alter this for 
         more efficient inotify use in your app.      
       */
     // int index;
      wd = 0;
      printf("\n");
      //for (index = 1; (index < argc) && (wd >= 0); index++) 
	//{
	  wd = watch_dir (inotify_fd, dir_origen, IN_ALL_EVENTS);
	  /*wd = watch_dir (inotify_fd, argv[index], IN_ALL_EVENTS & ~(IN_CLOSE | IN_OPEN) ); */
	//}

      if (wd > 0) 
	{
	  /* Wait for events and process them until a 
             termination condition is detected
           */
	  process_inotify_events (q, inotify_fd, dir_origen, dir_destino);
	}
      printf ("\nTerminating\n");

      /* Finish up by closing the fd, destroying the queue,
         and returning a proper code
       */
      unlink(rutaLock);
      closelog ();
      close_inotify_fd (inotify_fd);
      queue_destroy (q);
      
    }
  return 0;
}

