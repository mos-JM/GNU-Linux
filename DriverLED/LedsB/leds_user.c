#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

char array[3][3]= {
  {'2','\n','\n'},
  {'13', '\n', '\n'},
  {'3', '\n', '\n'},
 /* {"12"},
  {"1"},
  {"23"},
  {"123"},
  {""},*/
};

/*int main() {
 FILE* id= fopen("/dev/ledsa", "w+");
fwrite("123",sizeof(unsigned int),10, id);

fclose(id);
*/
int main() {

	int i = 0;
  	//srand (time(NULL));
  	//int v2 = rand() % 5 + 1;
	for(; ; i++){
		
  		int v2 = rand() % 5 + 1;
  		int j = i%8;

  		printf("valor -> [%s], ----- \n", array[j], v2);

		char command[50];
 		printf(command, "sudo echo %c > /dev/ledsa",array[j][0]);
		//sprintf("echo %s > /dev/ledsa",array[j]);
		system(command);
		sleep(v2);
	}
	return 0;
}
