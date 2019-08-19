#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gestorArchivo.h"


ubicacionVisitante cargar_visitante(FILE * file);
TLista cargar_ciudades(FILE * file );

/** funcion que se encarga de leer el archivo y cargar en un struct informacion los datos del usuario
    y retorna un puntero a ese struct asi podemos acceder a la misma **/
Info cargar_archivo(char nombre[]){
    Info retu = (Info) malloc(sizeof(struct informacion));
    FILE * file = fopen(nombre,"r");
    if( file != NULL ){
        retu->visitante = cargar_visitante(file);
        retu->ciudades = cargar_ciudades(file);

    }else{
        printf(":::Error archivo no enconetrado \n");
    }
    return retu;
}
/** carga la ubicacion del visitante extraida del archivo.txt y la retorna**/
ubicacionVisitante cargar_visitante(FILE * file){
    ubicacionVisitante retu = (ubicacionVisitante) malloc(sizeof(struct ubicacionVisitante));
    int rec = 0,can = 0;
    double num = 0;
    char cadena[20],letra;
    while ( !feof(file) && can < 2 ){
        letra = fgetc(file);
        if(letra != ';' && letra!='\n'){
            cadena[rec] = letra;
            rec++;
        }else{
            cadena[rec] = 0;
            rec = 0;
            can++;
            num = atof(cadena);
            if( letra == ';'){
                retu->x = num;
            }else{
                retu->y = num;
            }
        }
    }
    return retu;
}
/** carga las ciudades por visitar del visitante las cuales estan en el archivo.txt y retorna una lista de las mismas**/
TLista cargar_ciudades(FILE * file ){
    TLista retu = crear_lista();
    TCiudad ciudad;

    int can,rec = 0;
    float num = 0;
    char cadena[30],*nuevo,letra;
    while( !feof(file)){
        can = 0;
        ciudad = (TCiudad) malloc( sizeof(struct ciudad));
        rec = 0;
        do{
            letra = fgetc(file);
            if(letra == ';' || letra == '\n' ||feof(file)){
                can++;
                cadena[rec] = 0;
                rec = 0;
                switch(can){
                    case 1:
                        nuevo = (char*) malloc( sizeof(char)*30);
                        strcpy(nuevo,cadena);
                        ciudad->nombre = nuevo;
                        break;
                    case 2:
                        num = atof(cadena);
                        ciudad->pos_x = num;
                        break;
                    case 3:
                        num = atof(cadena);
                        ciudad->pos_y = num;
                        break;
                }
            }else{
                cadena[rec] = letra;
                rec++;
            }
        }while( letra!= '\n' && !feof(file));
        if( ciudad->nombre != NULL){
           l_insertar(&retu,NULL,ciudad);

        }
    }
    return retu;
}
