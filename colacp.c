#include <stdlib.h>
#include "colacp.h"
#include "Constante.h"

/**
    El metodo recursivo se encarga de buscar segun el tamaño del arbol, la posicion a insertar o a eliminar
    segun el uso que uno le quiera dar,descripto en mayor detalle en la documentacion
**/
TNodo posicion_segun_size(TColaCP cola, int size){
    TNodo aux;
    if(size==1){
        aux= cola->raiz;
    }
    else{
        aux=posicion_segun_size(cola ,size/2);
        if(size%2==0){
            aux=aux->hijo_izquierdo;
        }
        else {
            aux=aux->hijo_derecho;
        }
    }
    return aux;
}
/** metodo de reordenamiento de la cola despues de la insercion **/
void burbujeo_hacia_arriba(int (*f)(TEntrada,TEntrada),TNodo nodo){
        if(nodo->padre!=POS_NULA){
            if(f(nodo->padre->entrada,nodo->entrada)==-1){
                TEntrada aux=nodo->padre->entrada;
                nodo->padre->entrada=nodo->entrada;
                nodo->entrada=aux;

                burbujeo_hacia_arriba(f,nodo->padre);
            }
        }
    }

/** recibe como argumento una funcion parametrizada que es la encargada de darle un orden a las claves y crea la cola **/
TColaCP crear_cola_cp(int (*f)(TEntrada,TEntrada)){
    TColaCP  nuevo =(TColaCP) malloc(sizeof(struct cola_con_prioridad));
    nuevo->raiz=POS_NULA;
    nuevo->cantidad_elementos=0;
    nuevo->f=f;
    return nuevo;

}
/** el procedimiento de insercion se apoya en un metodo recursivo posicion_segun_size que retorna la posicion del elemento
    , al cual nosotros le enviamos la posicion del padre asi obtenemos su posicion y luego basta con averiguar si debo
        insertar como hijo izquierdo o derecho **/
int cp_insertar(TColaCP cola,TEntrada entr){

    TNodo A_insertar = (TNodo) malloc(sizeof(struct nodo));
    A_insertar->entrada=entr;
    //le seteo tanto HI como HD como NUlos porque siempre que cree un nodo nuevo hare lo mismo
    A_insertar->hijo_derecho=POS_NULA;
    A_insertar->hijo_izquierdo=POS_NULA;
    //primero sumo en uno la cantidad de elementos para poder utilizar el metodo recursivo
    cola->cantidad_elementos=cola->cantidad_elementos+1;

    if (cola->cantidad_elementos==1){
        cola->raiz=A_insertar;
        A_insertar->padre=POS_NULA;

    }
    else{
        TNodo padre= posicion_segun_size(cola,cola->cantidad_elementos/2);
        A_insertar->padre=padre;
        if(padre->hijo_izquierdo==POS_NULA){
            padre->hijo_izquierdo=A_insertar;
        }
        else {
            padre->hijo_derecho=A_insertar;
        }

        burbujeo_hacia_arriba(cola->f,A_insertar);

    }
    return (A_insertar!=POS_NULA);
}

/** metodo de reordenamiento despues de la eliminacion del minimo **/
void burbujeo_hacia_abajo(int (*f)(TEntrada,TEntrada),TNodo nodo){
        TNodo toChange=POS_NULA;

        if(nodo!=POS_NULA){

            if(nodo->hijo_derecho!=POS_NULA){
                if(f(nodo->hijo_izquierdo->entrada,nodo->hijo_derecho->entrada)==-1){
                    toChange=nodo->hijo_derecho;
                }
                else {
                    toChange=nodo->hijo_izquierdo;
                }
            }else if(nodo->hijo_izquierdo!=POS_NULA){
                    toChange=nodo->hijo_izquierdo;
                }

            if(toChange!=POS_NULA){

                if(f(nodo->entrada,toChange->entrada)==-1){
                    TEntrada aux=nodo->entrada;
                    nodo->entrada=toChange->entrada;
                    toChange->entrada=aux;
                    burbujeo_hacia_abajo(f,toChange);
                        }

                    }
            }
    }



/**
    (Asumimos que la cola tiene al menos un elemento) y Eliminamos y retornamos la clave con mayor prioridad de la cola
        **/
    TEntrada cp_eliminar(TColaCP cola){

        TEntrada toRet=cola->raiz->entrada;

        if(cola->cantidad_elementos==1){
            free(cola->raiz);
            cola->raiz=POS_NULA;

        }
        else{
            TNodo padre = posicion_segun_size(cola,cola->cantidad_elementos/2);
            TEntrada aux;
            if(padre->hijo_derecho!=POS_NULA){
                 aux= padre->hijo_derecho->entrada;
                free(padre->hijo_derecho);
                padre->hijo_derecho=POS_NULA;
            }
            else{
                 aux= padre->hijo_izquierdo->entrada;
                free(padre->hijo_izquierdo);
                padre->hijo_izquierdo=POS_NULA;
            }
            cola->raiz->entrada=aux;
}

        cola->cantidad_elementos=cola->cantidad_elementos-1;
        burbujeo_hacia_abajo(cola->f,cola->raiz);
        return toRet;
        }

int cp_size(TColaCP cola){
    return cola->cantidad_elementos;
}

/**
    El procedimiento eliminar se encarga de vaciar y liberar el espacio de todos los elementos de la cola
    **/
void eliminar(TNodo raiz){
    if(raiz!=POS_NULA){
        if(raiz->hijo_derecho!=POS_NULA){
            eliminar(raiz->hijo_izquierdo);
            eliminar(raiz->hijo_derecho);
        }
        else if(raiz->hijo_izquierdo!=POS_NULA)
                eliminar(raiz->hijo_izquierdo);
    }

    free(raiz);
}
/** Hace uso del metodo recursivo eliminar que libera todo el espacio utilizado por la cola y luego por ultimo liberamos
    el espacio que utilizaba el mismo struct cola_con_prioridad **/
int cp_destruir(TColaCP cola){

    eliminar(cola->raiz);
    // por ultimo el free(cola) me permite eliminar el espacio que ocupaba la cola en si como struct
    free(cola);
    //el return 1 solo lo agrego para evitar el warning, ya que como el free es void no puedo ver si fue liberada o no
    return 1;
}


