#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/inotify.h>

#define MAX_EVENTS 1024
#define EVENT_SIZE (sizeof (struct inotify_event))
#define EVENT_BUF_LEN (MAX_EVENTS * EVENT_SIZE)

#define NUM_FILAS 10
#define NUM_COLUMNAS 2

int main()
{
    int ganar=0;

     int fd, wd;
    char buffer[EVENT_BUF_LEN];
    char mensaje[256];

    // Crea el archivo tuberia.txt si no existe
    FILE *fp = fopen("tuberia.txt", "a");
    fclose(fp);



    char letras[] = "ABCDEFGHIJ";
    char** array = (char**)malloc(NUM_FILAS * 10 * sizeof(char*));
    
    for(int i = 0; i < NUM_FILAS; i++)
    {
        array[i] = (char*)malloc((NUM_COLUMNAS + 1) * sizeof(char));
        sprintf(array[i], "%c%d", letras[i], 0);
        
        for(int j = 1; j <= 9; j++)
        {
            array[i + j * NUM_FILAS] = (char*)malloc((NUM_COLUMNAS + 1) * sizeof(char));
            sprintf(array[i + j * NUM_FILAS], "%c%d", letras[i], j);
        }
    }

    printf("El tablero es el siguiente:\n");

    int salto = 0;
    for(int i = 0; i < NUM_FILAS * 10; i++)
    { salto++;
          if(salto == 11)
        {
            printf("\n");
            salto = 1;
        }
        printf("%s ", array[i]);
    }
    printf("\n\n");

    char** selecciones = (char**)malloc(10 * sizeof(char*));
    int num_selecciones = 0;
    int fila, columna;
    
    while(num_selecciones < 5)
    {
        printf("Ingrese las coordenadas donde quiere colocar tus barcos (Ejemplo: A0): ");
        char coordenada[3];
        scanf("%s", coordenada);
        
        // Verificar si la coordenada ingresada está dentro del rango del arraylist existente
        int es_valida = 0;
        for(int i = 0; i < NUM_FILAS * 10; i++)
        {
            if(strcmp(array[i], coordenada) == 0)
            {
                es_valida = 1;
                break;
            }
        }
        
        if(!es_valida)
        {
            printf("La coordenada ingresada no es válida. Intente nuevamente.\n");
            continue;
        }
        
        // Verificar si la coordenada ya fue seleccionada anteriormente
        int ya_seleccionada = 0;
        for(int i = 0; i < num_selecciones; i++)
        {
            if(strcmp(selecciones[i], coordenada) == 0)
            {
                ya_seleccionada = 1;
                printf("Esta coordenada ya se seleccionó. Intente nuevamente.\n");
                break;
            }
        }
        
        if(ya_seleccionada)
        {
            continue;
        }
        
        selecciones[num_selecciones] = (char*)malloc(3 * sizeof(char));
        strcpy(selecciones[num_selecciones], coordenada);
        num_selecciones++;
      
        // Obtener la fila y la columna seleccionadas
        fila = coordenada[0] - 'A';
        columna = coordenada[1] - '0';
    
        // Actualizar el valor del array en la posición seleccionada
        sprintf(array[fila + columna * NUM_FILAS], "%c%d", letras[fila], columna);
    }

printf("\nLas selecciones realizadas fueron:\n");
for(int i = 0; i < num_selecciones; i++)
{
    printf("%s ", selecciones[i]);
}
printf("\n\n");

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

while (1) {

    // Preguntar al usuario por otra cadena de caracteres a buscar
    char buscar[3];
    printf("\n\nIngrese la coordenada donde desea atacar: ");
    scanf("%s", buscar);
    if (strcmp(buscar, "q") == 0) {
        break;
    }
    
    // Verificar si la cadena ingresada es válida
    int valido = 0;
    for (int i = 0; i < NUM_FILAS * 10; i++) {
        if (strcmp(array[i], buscar) == 0) {
            valido = 1;
            
            // Escribe el mensaje en el archivo
            fp = fopen("tuberia1.txt", "w");
            fprintf(fp, "%s", buscar);
            fclose(fp);
            
            printf("\nEsperando confirmación\n");
            break;
        }
    }
    
    if (!valido) {
        printf("La coordenad '%s' no es un valor válido\n", buscar);
        continue;
    }

    //----------------------------------------------------------
    
         sleep(1);
    
         printf("\nEsperando confirmación\n");
       // Espera a que el archivo sea modificado
        fd = inotify_init();
        wd = inotify_add_watch(fd, "tuberia2.txt", IN_MODIFY);
        read(fd, buffer, EVENT_BUF_LEN);
        inotify_rm_watch(fd, wd);
        close(fd); 

        // Lee y muestra el nuevo contenido del archivo
        fp = fopen("tuberia2.txt", "r");
        fscanf(fp, "%s", mensaje);
        printf("Usted %s le dio a un barco\n", mensaje);
        fclose(fp); 
        
     //----------------------------------------------------------   

    // Pedir confirmación para reemplazar la cadena
   // char respuesta[3];
    
  //  respuesta[3] = mensaje;
    
   /* while (1) {
        printf("¿Usted le dió al barco en la coordenada: '%s'? (SI/NO): ", buscar);
        scanf("%s", respuesta);
        if (strcmp(respuesta, "SI") == 0 || strcmp(respuesta, "NO") == 0) {
            break;
        }
        printf("Respuesta inválida, por favor ingrese 'SI' o 'NO'\n");
    }
    */
    
    // Reemplazar la cadena según la respuesta del usuario
    if (strcmp(mensaje, "SI") == 0) {
        for (int i = 0; i < NUM_FILAS * 10; i++) {
            if (strcmp(array[i], buscar) == 0) {
                strcpy(array[i], "XX");
                ganar++;
                if(ganar == 5){
                printf("GANASTE");
                return 0;
                }
            }
        }
       printf("La coordenada '%s' se reemplazó por 'XX'\n", buscar);
        //  printf("Tablero actualizado\n");
    } else if (strcmp(mensaje, "NO") == 0) {
        for (int i = 0; i < NUM_FILAS * 10; i++) {
            if (strcmp(array[i], buscar) == 0) {
                strcpy(array[i], "00");
            }
        }
        printf("La coordenada '%s' se reemplazó por '00'\n", buscar);
    }
    
    // Mostrar los datos actualizados del array
    printf("\nTablero actualizado actualizado:\n");
    for (int i = 0; i < NUM_FILAS; i++) {
        for (int j = 0; j < 10; j++) {
            printf("%s ", array[i * 10 + j]);
        }
        printf("\n");
    }

    
//----------------------------------------------------------------------------------
     
 /*    
// Preguntar al usuario por otra cadena de caracteres a buscar
char buscar1[3];
printf("\nIngrese la coordenada a la que te atacaron: ");
scanf("%s", buscar1);

*/

  printf("\nEsperando ataque\n");
  
  
            sleep(2);

 // Espera a que el archivo sea modificado
        fd = inotify_init();
        wd = inotify_add_watch(fd, "tuberia1.txt", IN_MODIFY);
        read(fd, buffer, EVENT_BUF_LEN);
        inotify_rm_watch(fd, wd);
        close(fd);

        // Lee y muestra el nuevo contenido del archivo
        fp = fopen("tuberia1.txt", "r");
        fscanf(fp, "%s", mensaje);
        printf("Te atacaron en la coordenada: %s\n", mensaje);
        fclose(fp);


// Eliminar la cadena ingresada del array si existe
int encontrado = 0;
for (int i = 0; i < num_selecciones; i++) {
    if (strcmp(selecciones[i], mensaje) == 0) {
        encontrado = 1;
        for (int j = i; j < num_selecciones - 1; j++) {
            strcpy(selecciones[j], selecciones[j + 1]);
        }
        num_selecciones--;
        break;
    }
}

// Verificar si el array quedó vacío
if (num_selecciones == 0) {
printf("Te quedaste sin barcos. Perdiste...\n");

        sleep(1);
    
     // Escribe el mensaje en el archivo
       /* fp = fopen("tuberia.txt", "w");
        fprintf(fp, "%s", "GANASTE");
        fflush(fp);
        fsync(fileno(fp));
        fclose(fp); */
        
        sleep(1);

return 0;
}

char confsi[3] = "SI";
char confno[3] = "NO";

if (encontrado) {
    printf("Le dieron a tu barco\n");
    
    sleep(2);
    
     // Escribe el mensaje en el archivo
        fp = fopen("tuberia2.txt", "w");
        fprintf(fp, "%s", confsi);
        fflush(fp);
        fsync(fileno(fp));
        fclose(fp);
} else {
    //printf("La cadena '%s' no existe en el array\n", buscar1);
    printf("No le dieron a tu barco\n");
    
    sleep(2);
    
    // Escribe el mensaje en el archivo
        fp = fopen("tuberia2.txt", "w");
        fprintf(fp, "%s", confno);
        fflush(fp);
        fsync(fileno(fp));
        fclose(fp);
}

// Mostrar los datos que quedan en el array
printf("Los barcos que te quedan son:\n");
for (int i = 0; i < num_selecciones; i++) {
    printf("%s ", selecciones[i]);
}




    
    
}

//------------------------------------------------------------
//------------------------------------------------------------

return 0;
}

