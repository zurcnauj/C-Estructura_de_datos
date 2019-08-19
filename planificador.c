#include <stdio.h>
#include <stdlib.h>



#include "gestorArchivo.h"
#include "comando.h"

/** hilo principal de ejecucion **/

int main(int cantidad,char ** variables){

    Info info = cargar_archivo(variables [1]);
    int instruccion;
    do {
    printf("Elija un comando o presione 5 para desplegar la lista de comandos \n");
    scanf("%i",&instruccion);

    } while(comand(instruccion,info));
    return 1;
}
