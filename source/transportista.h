#ifndef _TRANSPORTISTA_H_
#define _TRANSPORTISTA_H_

#define ID_TR 5
#define NOM 21
#define EMAIL 31
#define PASS 16
#define CIUDAD 21
#define MAX_LIN_FICH_TRANS 99

typedef enum {
    EMPRESA, TRANSPORTISTA
} tNombre;

typedef struct {
    char Id_transp[ID_TR];
    char Nombre[NOM];
    char email[EMAIL];
    char Contrasenia[PASS];
    char Nomb_empresa[NOM];
    char Ciudad[CIUDAD];
} tTransportista;

/* FUNCIONES PUBLICAS */

// Precondición: nada.
// Postcondición: el administrador del sistema podrá operar en función de las opciones
//                que proporciona el menu.
void infoTransportistas();

// Precondición: devuelve una estructura tTransportista que no puede ser NULL
// Postcondición: proporciona al transportista el menu
void menuTransportista(tTransportista *transportista);

// Precondición: recibe una estructura tTransportista
// Postcondición: proporciona al transportista las opciones de perfil, asi como consultar datos y poder modificarlos
void perfilTransportista(tTransportista *transportista);

// Precondicion: nada
// Postcondicion: devuelve un vector de tipo tTransportista de tamaño igual al nº de transportistas del sistema
tTransportista *crearListaTransportistas();

// Precondicion: recibe un vector de estructuras tipo tTransportista
// Postcondicion: carga toda la informacion de Transportistas.txt en infotransp
void cargarTransportistas(tTransportista *infotransp);

// Precondicion: nada
// Postcondicion: devuelve el nº de transportistas del sistema
unsigned numTransportistas();

// Precondición: recibe una cadena de caracteres y datos de tipo tAdminProv
// Postcondición: guarda el contenido de datos en el fichero destino
void guardarNuevoTransportista(char *destino, tTransportista datos);

// Precondición: no pueden haber argumentos vacíos
// Postcondición: devuelve la posición que le corresponde al transportista si existe email y contraseña que coinciden con los parametros email y psw
//                devuelve 0 si no se encuentra
int inicioValidoTransportistas(tTransportista *transp, char *email, char *psw);

// Precondición: variable transportista pasada por referencia y un valor tipo tNombre
// Postcondición: almacena en el campo Nombre o Nomb_empresa (depende del valor de tNombre)
//                el valor que proporcione el usuario 
void getNombreTransportista(tTransportista *transportista, tNombre t);

// Precondición: variable transportista pasada por referencia
// Postcondición: almacena en el campo email el valor que proporcione el usuario
void getEmailTransportista(tTransportista *transportista);

// Precondición: variable transportista pasada por referencia
// Postcondición: almacena en el campo Contrasenia el valor que proporcione el usuario
void getContraseniaTransportista(tTransportista *transportista);

// Precondición: variable transportista pasada por referencia
// Postcondición: almacena en el campo Ciudad el valor que proporcione el usuario
void getCiudad(tTransportista *transportista);

/* FUNCIONES PRIVADAS */

// Precondición: recibe una variable de tipo tTransportista
// Postcondición: inserta en Transportistas.txt los nuevos datos de transportistaMod
static void modificarFicheroTransportistas(tTransportista transportistaMod);

// Precondición: recibe dos parámetros tipo tCliente
// Postcondición: devuelve 1 si nuevo = original y 0 en caso contrario
static int existeCambiosTransportistas(tTransportista nuevo, tTransportista original);

// Precondición: un valor tipo tNombre.
// Poscondición: devuelve el nombre de usuario o empresa que se introduzca, con varios mensajes de error en caso de que no sea válida.
static char *obtenerNombreTransportistaOempresa(tNombre t);

// Precondición: nada.
// Poscondición: devuelve el email que se introduzca, con varios mensajes de error en caso de que no sea válida.
static char *obtenerEmail();

// Precondición: nada.
// Poscondición: devuelve el nombre de usuario que se introduzca, con varios mensajes de error en caso de que no sea válida.
static char *obtenerContrasenia();

// Precondición: nada.
// Poscondición: devuelve el nombre de usuario que se introduzca, con varios mensajes de error en caso de que no sea válida.
static char *obtenerCiudad();

#endif // _TRANSPORTISTA_H_