#ifndef _PRODUCTOS_H_
#define _PRODUCTOS_H_

#include "clientes.h"   // MACRO ID
#include "categorias.h"

#define DES 51
#define ID_PROD 5
#define MAX_LIN_FICH_PROD 85

typedef struct{
    char id_prod[ID];           // 8 bytes
    char descrip[DES];          // 51 bytes
    char id_categ[ID_PROD];     // 5 bytes
    char id_gestor[ID_PROD];    // 5 bytes
    unsigned stock;             // 4 bytes
    unsigned entrega;           // 4 bytes
    double importe;             // 8 bytes          TOTAL = 85 BYTES
}t_productos;


/*  FUNCIONES PUBLICAS  */

//Precondición: nada
//Postcondición: devuelve el listado de productos
void consulta_Productos();

//Precondicion: nada
//Postcondicion: da la informacion del fichero productos.txt
void infoProdAdmin();



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

//Precondicion: recibe una estructura tipo productos
//Postcondicion: si encuentra el producto te da su informacion
static void producto_encontrado(t_productos prod);

//Precondicion: recibe una línea del fichero, el delimitador entre los datos y una estructura tipo productos
//Postcondicion: devuelve la estructura con los datos de la linea del fichero
static void dividir_cadena_prod(char temp[], char del[], t_productos *producto);

static void buscar_cat_prod();

static void categoria_encontrada(Categorias *cat, char del[]);

static void dividir_cadena_cat(char temp[], char del[], Categorias *cat);


#endif