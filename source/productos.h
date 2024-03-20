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


/*  FUNCIONES PUBLICAS  */

//Precondición: nada
//Postcondición: devuelve el listado de productos
void consulta_Productos();



/*  FUNCIONES PRIVADAS  */

//Precondicion: nada
//Postcondicion: devuelve la informacion sobre un producto referenciado
static void buscar_nombre_prod();

//Precondicion: nada
//Postcondicion: devuelve el numero de productos que hay en el fichero Productos.txt
static unsigned num_prod();

//Precondicion: recibe una cadena de caracteres
//Postcondicion: devuelve esa cadena de caracteres vacia
static void vaciar(char temp[]);

static void producto_encontrado(t_productos prod);

#endif