#ifndef _PRODUCTOS_H_
#define _PRODUCTOS_H_

#include "clientes.h"   // MACRO ID

#define DES 50
#define ID_PROD 4
#define MAX_LIN_FICH_PROD 82

typedef struct{
    char id_prod[ID];           // 8 bytes
    char descrip[DES];          // 50 bytes
    char id_categ[ID_PROD];     // 4 bytes
    char id_gestor[ID_PROD];    // 4 bytes
    unsigned stock;             // 4 bytes
    unsigned entrega;           // 4 bytes
    double importe;             // 8 bytes          TOTAL = 82 BYTES
} t_productos;


/*  FUNCIONES PRIVADAS  */

//Precondición: nada
//Postcondición: devuelve el listado de productos
static void consultaProductos ();

#endif