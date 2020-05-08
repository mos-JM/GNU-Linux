
#include "tiempo.h"

static struct timeval tv_ini, tv_fin;
static bool started =false;
static bool paused =false;
static double t_ini, t_fin;
static double accumulated;

//clockid_t reloj;
static struct timespec ts_ini, ts_fin;
static char globopt;
static int clockopt;
static clockid_t clocks[] = {
	CLOCK_REALTIME,
  	CLOCK_MONOTONIC,
 	CLOCK_PROCESS_CPUTIME_ID,
 	CLOCK_THREAD_CPUTIME_ID,
 	CLOCK_MONOTONIC_RAW,
	CLOCK_REALTIME_COARSE,
	CLOCK_MONOTONIC_COARSE
    	//(clockid_t) - 1 
};

void confTiempo (){

     int fd = open("reloj.conf", O_RDONLY);
     ssize_t len;
     char c;
     if(fd == -1){
        perror("error de configuracion");
	exit(1);
     }
     len = read(fd, &globopt, 1); 
// contrlo de errores
     if (globopt != '0'){
        len = read(fd, &c, 1); 
        clockopt = c - 48;
	//char == '0'

//para tener el entero int i = atoi(c) o i = c-48
     }
    
     
}

void start(){

     int t;
     
     confTiempo();
     if(!started){ // si no esta arrancado
	accumulated = 0;
	started = true;
	if (globopt == '0'){
		t = gettimeofday(&tv_ini, NULL);
		if (t == -1){
			perror("Error en (gettimeofday)");
		}
		t_ini = (double)(tv_ini.tv_sec + (tv_ini.tv_usec * 1E-6));		// 1 usec = 1E-6 sec
	}
	else{
		t = clock_gettime(clocks[clockopt], &ts_ini);
		if (t == -1)
			perror("Error en la medida de tiempo inicial (clock_gettime)");
		t_ini = (double)(ts_ini.tv_sec + (ts_ini.tv_nsec * 1E-9));		// 1 nsec = 1E-9 sec
	}
     }
}



void stop(){ // Devuelve el tiempo transcurrido desde start, o -1 si se ha producido algún error o se ha intentado hacer
// un stop sin un start previo
	int t;

	if (started && !paused) {
		paused = true;
		started = false; // paro el chrono
		if (globopt == '0'){
			t = gettimeofday(&tv_fin, NULL);
			if (t == -1)
				perror("Error en la medida de tiempo final (gettimeofday)");
			t_fin = (double)(tv_fin.tv_sec + (tv_fin.tv_usec * 1E-6));    	// 1 usec = 1E-6 sec
		}
		else{
			t = clock_gettime(clocks[clockopt], &ts_fin);
			if (t == -1)
				perror("Error en la medida de tiempo final (clock_gettime)");
			t_fin = (double)(ts_fin.tv_sec + (ts_fin.tv_nsec * 1E-9));		// 1 nsec = 1E-9 sec
		}
		accumulated += (double)(t_fin - t_ini);
	}

}

void pause(){				// Devuelve el tiempo desde el último resume, o 1 si se ha intentado hacer un pause detrás de otro pause
	int t;

	if (started && !paused) {
		paused = true;
		if (globopt == '0'){
			t = gettimeofday(&tv_fin, NULL);
			if (t == -1)
				perror("Error en la medida de tiempo final (gettimeofday)");
			t_fin = (double)(tv_fin.tv_sec + (tv_fin.tv_usec * 1E-6));    	// 1 usec = 1E-6 sec
		}
		else{
			t = clock_gettime(clocks[clockopt], &ts_fin);
			if (t == -1)
				perror("Error en la medida de tiempo final (clock_gettime)");
			t_fin = (double)(ts_fin.tv_sec + (ts_fin.tv_nsec * 1E-9));		// 1 nsec = 1E-9 sec
		}
		accumulated += (double)(t_fin - t_ini);
	}
}

void resume(){	// si esta parado calcula un nuevo inicio
     int t;
     if(started && paused){ // si esta pausado
	paused = false;
	
	if (globopt == '0'){
		t = gettimeofday(&tv_ini, NULL);
		if (t == -1){
			perror("Error en (gettimeofday)");
		}
		t_ini = (double)(tv_ini.tv_sec + (tv_ini.tv_usec * 1E-6));		// 1 usec = 1E-6 sec
	}
	else{
		t = clock_gettime(clocks[clockopt], &ts_ini);
		if (t == -1)
			perror("Error en la medida de tiempo inicial (clock_gettime)");
		t_ini = (double)(ts_ini.tv_sec + (ts_ini.tv_nsec * 1E-9));		// 1 nsec = 1E-9 sec
	}
     }
}

double getAccumulated(){
    return accumulated;

}
