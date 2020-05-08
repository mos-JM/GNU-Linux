#ifndef TIEMPO_H
#define TIEMPO_H

#include <stdio.h>
#include <stdlib.h>
//#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <stdbool.h>
#include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>





void start();
void stop();
void pause();
void resume();
double getAccumulated();


#endif //LIBTIEMPO_H

