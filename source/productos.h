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
    int stock;                  
    int entrega;                
    double importe;             
}tProductos;


/*  FUNCIONES PUBLICAS  */

//Precondición: nada
//Postcondición: devuelve el listado de productos
void consultaProductosCli();

//Precondicion: nada
//Postcondicion: devuelve el numero de productos que hay en el fichero Productos.txt
unsigned numProd();

//Precondicion: nada
//Postcondicion: depende de la accion realizada, puede realizar un alta, baja, modificar...
void consultaProdAdmin();

//Precondicion: recibe tantas estructuras como productos haya
//Postcondicion: devuelve todas las estructuras inicializadas con los datos del fichero Productos.txt
void cargarProductos(tProductos *prod);

//Precondicion: recibe una cadena de caracteres
//Postcondicion: devuelve esa cadena cambniando el \n del final por un \0
void cambio(char *temp);

//Precondicion: recibe una cadena de caracteres
//Postcondicion: devuelve esa cadena de caracteres vacia
void vaciar(char temp[]);

//Precondicion: nada
//Postcondicion: devuelve informacion sobre un producto referenciado
char* buscarNombreProd(char *idProd, int *encontrado);

//Precondicion: recibe todas las estructuras de los productos y el numero de productos
//Postcondicion: crea un nuevo fichero Productos.txt con los cambios realizados en los productos
void recrearFicheroProductos(tProductos *productos, unsigned numProd);



/*  FUNCIONES PRIVADAS  */

//Precondicion: recibe una estructura tipo productos
//Postcondicion: si encuentra el producto te da su informacion
static int productoEncontrado(tProductos prod);

//Precondicion: recibe una línea del fichero, el delimitador entre los datos y una estructura tipo productos
//Postcondicion: devuelve la estructura con los datos de la linea del fichero
static void dividirCadenaProd(char temp[], char del[], tProductos *producto);

//Precondicion: nada
//Postcondicion: devuelve la informacion de los productos que pertenezcan a una categoria en especifico
static void buscarCatProd();

//Precondicion: Recibe una estructura inicializada y el delimitador del fichero si se he encontrado la categoria
//Postcondicion: devuelve la información de un producto que pertenece a una categoria en especifico
static void categoriaEncontrada(Categorias *cat, char del[]);


//Precondicion: Recibe una linea del fichero, el delimitador de cada dato de la linea y una estructura inicializada
//Postcondicion: devuelve la estructura con los datos de la linea del fichero
static void dividirCadenaCat(char temp[], char del[], Categorias *cat);

//Precondicion: nada
//Postcondicion: devuelve la informacion del fichero productos.txt
static void infoProdAdmin();

//Precondicion: nada
//Postcondicion: da de alta un producto y lo almacena en Productos.txt
static void darAltaProd();

//Precondicion: nada
//Postcondicion: modificara el fichero Productos.txt si el admin/prov cambia los datos de algun Producto
static void modProdAdmin();

//Precondicion: Recibe una cadena de caracteres
//Postcondicion: Devuelve esa misma cadena de caracteres con los datos introducidos
static void getDescripcion(char *Descripcion);

//Precondicion: Recibe una cadena de caracteres
//Postcondicion: Devuelve esa misma cadena de caracteres con los datos introducidos
static void getIDcateg(char *categ);

//Precondicion: Recibe una cadena de caracteres
//Postcondicion: Devuelve esa misma cadena de caracteres con los datos introducidos
static void getIDgestor(char *idNProd);

//Precondicion: Recibe una linea del fichero, el delimitador de cada dato de la linea y una estructura inicializada
//Postcondicion: devuelve la estructura con los datos de la linea del fichero
static void dividirCadenaAdminProv(char temp[], char del[], tAdminProv *adminProv);

//Precondicion: recibe un entero
//Postcondicion: devuelve el entero con los datos introducidos
static void getStock(int *stock);

//Precondicion: recibe un entero
//Postcondicion: devuelve el entero con los datos introducidos
static void getEntrega(int *entrega);

//Precondicion: recibe un double
//Postcondicion: devuelve el double con los datos introducidos
static void getImporte(double *importe);

//Precondicion: recibe la ruta donde esta el fichero y una estructura inicializada con datos
//Postcondicion: en el fichero introduce un nuevo producto con los datos de la estructura
static void guardarNuevoProducto(char *destino, tProductos Nprod);

//Precondicion: nada
//Postcondicion: da de baja un producto y lo elimina de Productos.txt
static void darBajaProd();

//Precondicion: nada
//Postcondicion: devuelve el listado de todos los productos en el fichero Productos.txt
static void imprimirProductos();

//Precondicion: recibe dos estructuras de productos
//Postcondicion: devuelve un valor dependiendo si las dos estructuras son distintas
static int existeCambiosProductos(tProductos nuevo, tProductos original);

//Precondicion: recibe una estructura
//Postcondicion: modifica el fichero Productos.txt con los datos de la estructura 
static void modificarFicheroProductos(tProductos productoMod);

#endif