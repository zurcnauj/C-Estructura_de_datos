#include <stdlib.h>
#include <stdio.h>
#include "comando.h"
#include "colacp.h"


/** funcion que calcula la distancia de Manhattan **/

int distancia(int x1,int y1,int x2,int y2){
    int X= abs(x2-x1);
    int Y=abs(y2-y1);
    return X+Y;
}
/** funcion a parametrizar **/

int funcionAscendente(TEntrada i1,TEntrada i2){
    if ( i1->clave<i2->clave) return 1;
    else if (i1->clave==i2->clave) return 0;
    else return -1;
}

void imprimirPantalla(TColaCP cola){
    int size= cp_size(cola);
    int pos =1;
    while(size>0){
        TEntrada e = cp_eliminar(cola);
        TCiudad ciudad = e->valor;
        printf("%i %s \n",pos,ciudad->nombre);
        size=size-1;
        pos=pos+1;
    }
}
/**
    Muestra de forma ascendente el listado de las ciudades
**/
void mostrarAscendente(Info info){
    TLista listaCiudades= info->ciudades;
    int dist;
    TColaCP cola = crear_cola_cp(&funcionAscendente);
    TEntrada e1;
    while(listaCiudades!=NULL){
        TCiudad ciudad = listaCiudades->elemento;
        dist = distancia(info->visitante->x,info->visitante->y,ciudad->pos_x,ciudad->pos_y);
        e1 = (TEntrada) malloc(sizeof(struct entrada));
        e1->clave=(void *) dist;
        e1->valor=ciudad;
        cp_insertar(cola,e1);

        listaCiudades=listaCiudades->celda_siguiente;
    }

    imprimirPantalla(cola);
}

/** funcion a parametrizar**/

int funcionDescendente(TEntrada i1,TEntrada i2){
    if ( i1->clave<i2->clave) return -1;
    else if (i1->clave==i2->clave) return 0;
    else return 1;
}

/** muestra de forma descendente el listado de las ciudades **/

void mostrarDescendente(Info info){
        TLista listaCiudades = info->ciudades;
        int dist;
        TColaCP cola = crear_cola_cp(&funcionDescendente);
        TEntrada e1;

        while(listaCiudades!=NULL){
        TCiudad ciudad = listaCiudades->elemento;
        dist = distancia(info->visitante->x,info->visitante->y,ciudad->pos_x,ciudad->pos_y);
        e1 = (TEntrada) malloc(sizeof(struct entrada));
        e1->clave=(void *)dist;
        e1->valor=ciudad;
        cp_insertar(cola,e1);

        listaCiudades=listaCiudades->celda_siguiente;
    }

    imprimirPantalla(cola);

}
/** carga la cola de forma ascentedente segun la ubicacion de ṕartida o inicial del visitante**/
void cargarCola(TColaCP cola,TLista lista,ubicacionVisitante u){
    int dist;
    TEntrada e1 ;
    while(lista!=NULL){
        TCiudad ciudad = lista->elemento;
        dist= distancia(u->x,u->y,ciudad->pos_x,ciudad->pos_y);
        e1= (TEntrada) malloc(sizeof(struct entrada));
        e1->clave=(void *)dist;
        e1->valor=ciudad;
        cp_insertar(cola,e1);
        lista=lista->celda_siguiente;
    }
}

/** Procedimiento utilizado por la funcion ReducirHoras para ir hallando recursivamente la
    ciudad a menor distancia de la posicion actual del visitante y calculando la distancia recorrida por el visitante
    e imprimiendo por pantalla los resultados **/

void recursivo(TColaCP cola,ubicacionVisitante u,int pos,float recorrido){
    if (cp_size(cola)==1){
    TCiudad ciudad = cp_eliminar(cola)->valor;
        recorrido =recorrido+ distancia(u->x,u->y,ciudad->pos_x,ciudad->pos_y);
        printf("%i  %s \n Distancia Recorrida : %f \n",pos,ciudad->nombre,recorrido);
    }
    else {
        TEntrada e=cp_eliminar(cola);
        TCiudad ciudad=e->valor;
        printf("%i  %s \n ",pos,ciudad->nombre);
        recorrido =recorrido+ distancia(u->x,u->y,ciudad->pos_x,ciudad->pos_y);
        u->x=ciudad->pos_x;
        u->y=ciudad->pos_y;
        TColaCP colaAux=crear_cola_cp(&funcionAscendente);
        int size =cp_size(cola);
        int dist;
        while(size>0){
            TEntrada e2= cp_eliminar(cola);
            TEntrada e3=(TEntrada) malloc(sizeof(struct entrada));
            TCiudad ciudad2 = e2->valor;
            dist= distancia(u->x,u->y,ciudad2->pos_x,ciudad2->pos_y);
            e3->clave=(void *)dist;
            e3->valor=ciudad2;
            cp_insertar(colaAux,e3);
            size=size-1;
        }

        recursivo(colaAux,u,pos+1,recorrido);
    }
}

/** el procedimento reducir horas utiliza un metodo para cargar la cola y otro recursivo que se encarga
    de ir hayando siempre la ciudad a menor distacia e imprimirla **/

void reducirHoras(Info info){
    TLista listaCiudades = info->ciudades;
    ubicacionVisitante ubicacion = info->visitante;
    TColaCP cola = crear_cola_cp(&funcionAscendente);

    cargarCola(cola,listaCiudades,info->visitante);
    recursivo(cola,ubicacion,1,0.0);
}

/** listamos los comandos **/
void help(){
    printf("Los Comando Posibles son: \n");
    printf("El comando N° 1 equivale a: mostrarAscendente  \n");
    printf("El comando N° 2 equivale a: mostrarDescentende \n");
    printf("El comando N°3 equivale a: reducirHorasManejo \n");
    printf("El comando N° 4 equivale a: terminar ejecucion del programa (exit) \n");
    printf("El comando N°5 equivale a: ver lista de comandos(HELP) \n");
}

/** proceso de finalizacion y liberacion de espacio utilizado para cargar los datos del visitante**/

void terminar(Info info){
   free(info->visitante);
   l_destruir((&info->ciudades));
   free(info);
}

/** procedimiento encargado de ejecutar las instrucciones del usuario**/
int comand (int instruccion,Info info){
    int retu =1;
    if(instruccion==1){
        mostrarAscendente(info);
    }
    else if(instruccion==2){
        mostrarDescendente(info);
    }
    else if(instruccion==3){
        reducirHoras(info);
    }
    else if(instruccion==4){
        terminar(info);
        retu=0;
    }
    //el 5 equivale a la instruccion helṕ
    else if(instruccion==5){
        help();
    }
    return retu;
}
