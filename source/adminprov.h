#ifndef _ADMINPROV_H_
#define _ADMINPROV_H_

#define ID_EMPRESA 5
#define NOM 21
#define EMAIL 31
#define PASS 16
#define PERFIL 14   // administrador o proveedor, administrador tiene 13 caracteres
#define MAX_LIN_FICH_ADMINPROV 91   // numero maximo de caracteres por linea en AdminProv.txt

// Estructura adminprov
typedef struct {
    char Id_empresa[ID_EMPRESA];
    char Nombre[NOM];
    char email[EMAIL];
    char Contrasenia[PASS];
    char Perfil_usuario[PERFIL];    // administrador o proovedor
} tAdminProv;

typedef enum {
    NOMBREPV, CORREOPV
} BusquedaProveedores;

/* FUNCIONES PUBLICAS */

// Precondición: recibe una estructura tAdminProv que no puede ser NULL
// Postcondición: proporciona al administrador el menu
void menuAdmin(tAdminProv *admin);

// Precondición: recibe una estructura tAdminProv que no puede ser NULL
// Postcondición: proporciona al proveedor el menu
void menuProveedor(tAdminProv *proveedor);

// Precondición:nada
// Postcondicion: devuelve un vector de tipo tCliente de tamaño igual al nº de clientes del sistema
tAdminProv *crearListaAdminProv();

// Precondición: recibe un vector de estructuras tipo tCliente
// Postcondición: carga toda la informacion de Clientes.txt en infocli
void cargarAdminProvs();

// Precondición: no pueden haber argumentos vacíos
// Postcondición: devuelve la posición que le corresponde al cliente si existe email y contraseña que coinciden con los parametros email y psw
int inicioValidoAdminProv(tAdminProv *infoAdminProv, char *email, char *psw);

// Precondición: recibe una estructura tAdminProv
// Postcondición: proporciona al administrador las opciones de perfil, asi como consultar datos y poder modificarlos
void perfilAdmin(tAdminProv *admin);

// Precondición: recibe una estructura tAdminProv
// Postcondición: proporciona al proveedor las opciones de perfil, asi como consultar datos y poder modificarlos
void perfilProveedor(tAdminProv *proveedor);

// Precondición: nada.
// Postcondición: devuelve el numero de administradores + proovedores del sistema.
unsigned numAdminProvs();

// Precondición: recibe una cadena de caracteres y datos de tipo tAdminProv
// Postcondición: guarda el contenido de datos en el fichero destino
void guardarNuevoAdminProv(char *destino, tAdminProv datos);

// Precondición: variable adminprovs pasada por referencia
// Postcondición: almacena en el campo Nombre el valor que proporcione el administrador o el provedor
void getNombreProvedor(tAdminProv *adminprovs);

// Precondición: variable adminprovs pasada por referencia
// Postcondición: almacena en el campo email el valor que proporcione el administrador o el provedor
void getEmailAdminProv(tAdminProv *adminprovs);

// Precondición: variable adminprovs pasada por referencia
// Postcondición: almacena en el campo Contrasenia el valor que proporcione el administrador o el provedor
void getContraseniaAdminProv(tAdminProv *adminprovs);

// Precondicion: recibe un puntero a un vector dinamico de tipo tAdminProv
// Postcondicion: reserva espacio de memoria
void reservarAdminProv(tAdminProv *infoAdminProv);

/* FUNCIONES PRIVADAS */

// Precondición: nada.
// Postcondición: registra un Proveedor en el sistema.
static void administracionProveedores();

// Precondición: nada.
// Postcondición: elimina los proveedores indicado por el administrador del sistema.
static void bajaProveedor();

// Precondición: recibe un array dinamico de tipo tAdminProv y el numero de proveedores
// Postcondición: modifica AdminProv.txt con los proveedores que haya en proveedores
static void recrearFicheroProveedores(tAdminProv *proveedores, int numProveedores);

// Precondición: nada.
// Postcondición: modifica en AdminProv.txt aquello que haya modificado el administrador
static void modificarProveedores();

// Precondición: nada.
// Postcondición: menu para buscar proveedores 
static void buscadorProveedores();

// Precondición: nada.
// Postcondición: proporciona la busqueda por IDs de proveedores.
static void buscarIDproveedor();

// Precondición: un proveedor en concreto.
// Postcondición: imprime los datos del proveedor.
static void desgloseCompletoProveedor(tAdminProv proveedor);

// Precondición: se debe proporcionar el tipo de Busqueda, recibe un string y el tamaño de dicho string
// Postcondición: se proporciona los proveedores bajo el criterio de busqueda
static void buscarEnProveedores(BusquedaProveedores tipo, const char *str, unsigned tamStr);

// Precondición: se debe proporcionar el tipo de Busqueda
// Postcondición: realiza la busqueda que proporcione el administrador
static void buscarConTextoProveedores(BusquedaProveedores tipo);

// Precondición: nada.
// Postcondición: imprime por pantalla los proveedores del sistema.
static void imprimirProveedores();

// Precondición: recibe dos parámetros tipo tAdminProv
// Postcondición: devuelve 1 si nuevo = original y 0 en caso contrario
static int existeCambiosAdminProv(tAdminProv nuevo, tAdminProv original);

// Precondición: recibe una variable de tipo tAdminProv
// Postcondición: inserta en AdminProv.txt los nuevos datos de adminprovMod
static void modificarFicheroAdminProv(tAdminProv adminprovMod);

// Precondición: nada.
// Poscondición: devuelve el nombre de provedor que se introduzca, con varios mensajes de error en caso de que no sea válida.
static char *obtenerNombreProvedor();

// Precondición: nada.
// Poscondición: devuelve el email que se introduzca, con varios mensajes de error en caso de que no sea válida.
static char *obtenerEmail();

// Precondición: nada.
// Poscondición: devuelve la contrasenia que se introduzca, con varios mensajes de error en caso de que no sea válida.
static char *obtenerContrasenia();

#endif // _ADMINPROV_H_
