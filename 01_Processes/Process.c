#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h> 
#include <sys/wait.h> 

int main(){
	int pid,status;
	switch(pid=fork()){
		case -1:/*Gestor of error*/
		exit(1);
		break;

		case 0: /*Proceso hijo*/
		printf("\nProceso hijo. PID=%d\n",pid);
		break;

		default: /*Father process*/
		printf("\nProceso padre.PID=%d\n",pid);
		wait(&status);/*wait the end of son process*/
		break;
	}/*end of switch*/

	printf("\nFin de la ejecucion\n");
	return 0;
}