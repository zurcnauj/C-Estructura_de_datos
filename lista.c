#include "lista.h"
#include "Constante.h"

TLista crear_lista(){
    return NULL;
}
/** Asumo que la posicion que me envian por parametro es valida
    El procedimiento agregar el elemento en la posicion pos de la lista o como primer elemento
    en caso de que la posicion sea Nula
**/
int l_insertar(TLista * lista,TPosicion pos,TElemento elem){
    TPosicion nuevo = (TPosicion) malloc(sizeof(struct celda));
    nuevo->elemento=elem;
    if(pos==POS_NULA){

        //me fijo si la lista esta vacia y en ese caso la celda siguiente es NULL
        if(*lista==POS_NULA)
            nuevo->celda_siguiente=NULL;
        //caso contrario el siguiente, va a ser el primer elemento de la lista
        else{
            nuevo->celda_siguiente=*lista;
            nuevo->celda_siguiente->celda_anterior=nuevo;
        }
        nuevo->celda_anterior=NULL;

        *lista=nuevo;
    }

    else{
        nuevo->celda_siguiente=pos;
        nuevo->celda_anterior=pos->celda_anterior;
        //quiero insertar en la primera posicion de la lista
        if(pos->celda_anterior==POS_NULA){
            *lista=nuevo;
        }

        else {
            nuevo->celda_anterior->celda_siguiente=nuevo;

        }
            pos->celda_anterior=nuevo;

    }

    return TRUE;
}

/** Elimina el elemento de la posicion pos de la lista **/
int l_eliminar(TLista * lista,TPosicion pos){
    //me sersioro que la posicion apunte a un elemento
    if(pos!=POS_NULA){

        if(pos->celda_anterior==POS_NULA)
            *lista=pos;
        else
            pos->celda_anterior->celda_siguiente=pos->celda_siguiente;
        //compruebo que el siguiente de pos no sea NULL para enlazarle el anterior de pos
        if(pos->celda_siguiente!=POS_NULA)
            pos->celda_siguiente->celda_anterior=pos->celda_anterior;


        free(pos);
        return TRUE;
    }
    else{
        return FALSE;
    }
}
/** retorna la primer posicion de la lista, si la lista vacia retorna POS_NULA**/
TPosicion l_primera(TLista lista){
    return lista;
}
/** retorna la ultima posicion de la lista, POS_NULA si la lista esta vacia**/
TPosicion l_ultima(TLista lista){
    while(lista->celda_siguiente!=POS_NULA)
        lista=lista->celda_siguiente;

    return lista;
}
/** retorna la posicion anterior a pos, y en caso de que pos sea la primer posicion retorna POS_NULA **/
TPosicion l_anterior(TLista lista, TPosicion pos){
    TPosicion toRet=POS_NULA;
    if(pos!=POS_NULA)
        toRet=pos->celda_anterior;

    return toRet;
}
/** Retorna la siguiente posicion de pos, si pos es la ultima retorna POS_NULA **/
TPosicion l_siguiente(TLista lista,TPosicion pos){
    TPosicion toRet=POS_NULA;
    if(pos!=POS_NULA)
        toRet=pos->celda_siguiente;

    return toRet;
}
/** retorna el elemento correspondiente  a  la posicion pos, si pos es POS_NULA retorna ELE_NULO**/
TElemento l_recuperar(TLista lista,TPosicion pos){
    TElemento toRet=ELE_NULO;
    if (pos!=POS_NULA)
        toRet=pos->elemento;

    return toRet;
}

int l_size(TLista lista){
    int contador=0;
    while(lista!=POS_NULA){
        contador=contador+1;
        lista=lista->celda_siguiente;

    }
    return contador;
}
/** elimina todos los elementos y libera todo el espacio utilizado por la lista **/
int l_destruir(TLista * lista){

    while(*lista!=NULL){
        TPosicion pos=*lista;
        *lista= pos->celda_siguiente;
        free(pos);
    }
    return TRUE;
}
