#ifndef _ADMINPROV_H_
#define _ADMINPROV_H_

#define ID_EMPRESA 5
#define NOM 21
#define EMAIL 31
#define PASSW 16
#define PERFIL 14   // administrador o proveedor, administrador tiene 13 caracteres
#define MAX_LIN_FICH_ADMINPROV 91   // numero maximo de caracteres por linea en AdminProv.txt

typedef struct {
    char Id_empresa[ID_EMPRESA];
    char Nombre[NOM];
    char email[EMAIL];
    char Contrasenia[PASSW];
    char Perfil_usuario[PERFIL];    // administrador o proovedor
} tAdminProv;


/* FUNCIONES PUBLICAS */

void menuAdminProv(tAdminProv *adminprov);

// Precondición:nada
// Postcondicion: devuelve un vector de tipo tCliente de tamaño igual al nº de clientes del sistema
tAdminProv *crearListaAdminProv();

// Precondición: recibe un vector de estructuras tipo tCliente
// Postcondición: carga toda la informacion de Clientes.txt en infocli
void cargarAdminProvs();

// Precondición: no pueden haber argumentos vacíos
// Postcondición: devuelve la posición que le corresponde al cliente si existe email y contraseña que coinciden con los parametros email y psw
int inicioValidoAdminProv(tAdminProv *infoAdminProv, char *email, char *psw);


/* FUNCIONES PRIVADAS */

// Precondición: nada.
// Postcondición: devuelve el numero de administradores + proovedores del sistema.
static unsigned numAdminProvs();

#endif // _ADMINPROV_H_
