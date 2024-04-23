#ifndef _PRODUCTOS_H_
#define _PRODUCTOS_H_

#include "clientes.h"
#include "categorias.h"
#include "adminprov.h"

#define DES 51
#define ID_PROD 5
#define MAX_LIN_FICH_PROD 75

typedef struct{
    char id_prod[ID];           // 8 bytes
    char descrip[DES];          // 51 bytes
    char id_categ[ID_PROD];     // 5 bytes
    char id_gestor[ID_PROD];    // 5 bytes
    int stock;                  // 4 bytes
    int entrega;                // 4 bytes
    double importe;             // 8 bytes          TOTAL = 85 BYTES
}tProductos;


/*  FUNCIONES PUBLICAS  */

//Precondición: nada
//Postcondición: devuelve el listado de productos
void consultaProductosCli();

//Precondicion: nada
//Postcondicion: devuelve el numero de productos que hay en el fichero Productos.txt
unsigned numProd();

//Precondicion: nada
//Postcondicion: 
void consultaProdAdmin();

void cargarProductos(tProductos *prod);

void cambio(char *temp);



/*  FUNCIONES PRIVADAS  */

//Precondicion: nada
//Postcondicion: devuelve la informacion sobre un producto referenciado
char* buscarNombreProd(char *idProd, int *encontrado);

//Precondicion: recibe una cadena de caracteres
//Postcondicion: devuelve esa cadena de caracteres vacia
static void vaciar(char temp[]);

//Precondicion: recibe una estructura tipo productos
//Postcondicion: si encuentra el producto te da su informacion
static int productoEncontrado(tProductos prod);

//Precondicion: recibe una línea del fichero, el delimitador entre los datos y una estructura tipo productos
//Postcondicion: devuelve la estructura con los datos de la linea del fichero
static void dividirCadenaProd(char temp[], char del[], tProductos *producto);

static void buscarCatProd();

static void categoriaEncontrada(Categorias *cat, char del[]);

static void dividirCadenaCat(char temp[], char del[], Categorias *cat);

//Precondicion: nada
//Postcondicion: da la informacion del fichero productos.txt
static void infoProdAdmin();

static void darAltaProd();

static void modProdAdmin();

static void getDescripcion(char *Descripcion);

static void getIDcateg(char *categ);

static void getIDgestor(char *idNProd);

static void dividirCadenaAdminProv(char temp[], char del[], tAdminProv *adminProv);

static void getStock(int *stock);

static void getEntrega(int *entrega);

static void getImporte(double *importe);

static void guardarNuevoProducto(char *destino, tProductos Nprod);

static void darBajaProd();

#endif