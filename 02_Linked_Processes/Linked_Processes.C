#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h> //Se agregó esta libreria
#include <stdlib.h>
#include <unistd.h>

#define SHMKEY 75
#define TRUE 1
int region_critica(int pid); //Se agrego int pid
int region_no_critica(int pid);
int esperando_turno(int pid);

/// ESTE PROGRAMA SE CORRE PRIMERO para sistema V. programa_1_sistemav.c
int main(){
    // Declaración de variables
    int shmid, pid;
    char *addr, *turno;
    pid = getpid(); // Obtenemos el Pid del proceso
    shmid = shmget(SHMKEY, 10, 0777 | IPC_CREAT); /* Crear la region de memoria y
    obtener la dirección */
    addr = shmat(shmid, 0, 0); /* ENLAZAR REGIÓN AL ESPACIO DE DIRECCIONAMIENTO DEL
    PROCESO */
    turno = (char *) addr; /* Reservar addr */
    /* CÓDIGO DE SINCRONIZACIÓN */
    printf("\n [I] Variables Declaradas");
    sleep(5); /* Para dar tiempo a que se ejecute el segundo proceso */
    (*turno) = '0'; // Declara el turno inicial
    printf("\n [I] Iniciando proceso de turnos con turno inicial: %c", (*turno));

    // Muestra el turno
    while (TRUE) {
        while ((*turno) != '0') { //Este while no tenia corchete
        esperando_turno(pid); // Espera a su turno
    }
    region_critica(pid); // Manda a llamar a región crítica
    sleep(1);
    (*turno) = '1'; // Cambia el turno
    region_no_critica(pid); // Manda a llamar a región no crítica
    }

    /* Separar la región del espacio de direccionamiento del proceso */
    shmdt(addr);
    /* Eliminar la región de memoria compartida */
    shmctl(shmid, IPC_RMID, 0);
    return 0;
} /* Fin de la función main */

int esperando_turno(int pid) {
    printf("\n [I] Proceso %d y esperando turno :p", pid);
    sleep(2);
    return 0;
}

int region_critica(int pid) {
    printf("\n\n [O] Cambiando Variables");
    for (int i = 0; i < 5; i++) {
        printf("\n [O] Turno %d", i + 1);
    sleep(1);
    }
    return 0;
}

int region_no_critica(int pid) {
    printf("\n [O] Proceso %d y turno tomado :))))))))))))))))))))))))\n", pid);
    return 0;
}