#ifndef GESTORARCHIVO_H_INCLUDED
#define GESTORARCHIVO_H_INCLUDED
#include "lista.h"
typedef struct ubicacionVisitante{
    float x;
    float y;
}*ubicacionVisitante;

 typedef struct ciudad{
    char * nombre;
    float pos_x;
    float pos_y;
}*TCiudad;

/** Registro que contiene la informacion fundamental del visitante y en el cual nos apoyamos para implementar las
    operaciones fundamentales del programa**/

typedef struct informacion{
    ubicacionVisitante visitante;
    TLista ciudades;
} * Info;

/** funcion que se encarga de leer el archivo y cargar en un struct informacion los datos del usuario
    y retorna un puntero a ese struct asi podemos acceder a la misma **/

Info cargar_archivo(char nombre []);






#endif // GESTORARCHIVO_H_INCLUDED
