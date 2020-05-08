/**
 * Temporizacion
 * @autor Agustin Jofre Millet
**/


#include "tiempo.h"



int fibonacci(n, x1, x2) {
  if (n == 0) {
    return x1;
  }
  return fibonacci(n - 1, x2, x1 + x2);
}

int main(){


	start();
	int i = 0; 
  	for(i = 0; i < 999; i++) {
      		fibonacci(40, 0, 1);
  	}
	pause();
	resume();
	for(i = 0; i < 999; i++) {
      		fibonacci(40, 0, 1);
  	}
	
	pause();
	for(i = 0; i < 999; i++) {
      		fibonacci(40, 0, 1);
  	}
	resume();
	for(i = 0; i < 999; i++) {
      		fibonacci(40, 0, 1);
  	}

	stop();
	printf("tiempo ,%lf\n" , getAccumulated());
			

	return EXIT_SUCCESS;

}


