#ifndef _ADMINPROV_H_
#define _ADMINPROV_H_

#define ID_EMPRESA 4
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

// Precondición: nada.
// Postcondición: devuelve el numero de administradores + proovedores del sistema.
unsigned numAdminProvs();

/* FUNCIONES PRIVADAS */

// Precondición: variable adminprovs pasada por referencia
// Postcondición: almacena en el campo Nombre el valor que proporcione el administrador o el provedor
static void getNombreProvedor(tAdminProv *adminprovs);

// Precondición: nada.
// Poscondición: devuelve el nombre de provedor que se introduzca, con varios mensajes de error en caso de que no sea válida.
static char *obtenerNombreProvedor();

// Precondición: variable adminprovs pasada por referencia
// Postcondición: almacena en el campo email el valor que proporcione el administrador o el provedor
static void getEmailAdminProv(tAdminProv *adminprovs);

// Precondición: nada.
// Poscondición: devuelve el email que se introduzca, con varios mensajes de error en caso de que no sea válida.
static char *obtenerEmail();

// Precondición: variable adminprovs pasada por referencia
// Postcondición: almacena en el campo Contrasenia el valor que proporcione el administrador o el provedor
static void getContraseniaAdminProv(tAdminProv *adminprovs);

// Precondición: nada.
// Poscondición: devuelve la contrasenia que se introduzca, con varios mensajes de error en caso de que no sea válida.
static char *obtenerContrasenia();

#endif // _ADMINPROV_H_
