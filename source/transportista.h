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

typedef enum {
    NOMBRE_TR, CORREO_TR, NOMBRE_EMP, NOM_CIUDAD
} BusquedaTransp;

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
void administracionTransportistas();

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

// Precondición: variable transportista pasada por referencia
// Postcondición: almacena en el campo Nombre el valor que proporcione el usuario 
void getNombreTransportista(tTransportista *transportista);

// Precondición: variable transportista pasada por referencia
// Postcondición: almacena en el campo email el valor que proporcione el usuario
void getEmailTransportista(tTransportista *transportista);

// Precondición: variable transportista pasada por referencia
// Postcondición: almacena en el campo Contrasenia el valor que proporcione el usuario
void getContraseniaTransportista(tTransportista *transportista);

// Precondición: variable transportista pasada por referencia
// Postcondición: almacena en el campo Ciudad el valor que proporcione el usuario
void getNombreEmpresa(tTransportista *transportista);

// Precondición: variable transportista pasada por referencia
// Postcondición: almacena en el campo Ciudad el valor que proporcione el usuario
void getCiudad(tTransportista *transportista);

/* FUNCIONES PRIVADAS */

// Precondición: nada.
// Postcondición: elimina los clientes indicado por el administrador del sistema.
static void bajaTransportista();

// Precondición: recibe un array dinamico de tipo tTransportista y el numero de transportistas
// Postcondición: modifica Transportistas.txt con los transportistas que haya en transportistas
static void recrearFicheroTransportistas(tTransportista *transportistas, int numTransp);

// Precondición: nada.
// Postcondición: menu para buscar transportistas 
static void buscadorTransportistas();

// Precondición: nada.
// Postcondición: proporciona la busqueda por IDs de transportistas.
static void buscarIDtransportistas();

// Precondición: se debe proporcionar el tipo de Busqueda
// Postcondición: realiza la busqueda que proporcione el administrador
static void buscarConTextoTransportistas(BusquedaTransp tipo);

// Precondición: se debe proporcionar el tipo de Busqueda, recibe un string y el tamaño de dicho string
// Postcondición: se proporciona los transportistas bajo el criterio de busqueda
static void buscarEnTransportistas(BusquedaTransp tipo, const char *str, unsigned tamStr);

// Precondición: un transportista en concreto.
// Postcondición: imprime los datos del transportista.
static void desgloseCompletoTransportistas(tTransportista transportista);

// Precondición: nada.
// Postcondición: modifica en Transportistas.txt aquello que haya modificado el administrador
static void modificarTransportistas();

// Precondición: nada.
// Postcondición: imprime por pantalla el listado de transportistas del sistema.
static void imprimirTransportistas();

// Precondición: recibe una variable de tipo tTransportista
// Postcondición: inserta en Transportistas.txt los nuevos datos de transportistaMod
static void modificarFicheroTransportistas(tTransportista transportistaMod);

// Precondición: recibe dos parámetros tipo tCliente
// Postcondición: devuelve 1 si nuevo = original y 0 en caso contrario
static int existeCambiosTransportistas(tTransportista nuevo, tTransportista original);

// Precondición: un valor tipo tNombre.
// Poscondición: devuelve el nombre de usuario o empresa que se introduzca, con varios mensajes de error en caso de que no sea válida.
static char *obtenerNombreTransportista();

// Precondición: nada.
// Poscondición: devuelve el email que se introduzca, con varios mensajes de error en caso de que no sea válida.
static char *obtenerEmail();

// Precondición: nada.
// Poscondición: devuelve el nombre de usuario que se introduzca, con varios mensajes de error en caso de que no sea válida.
static char *obtenerContrasenia();

// Precondición: nada.
// Poscondición: devuelve el nombre de usuario que se introduzca, con varios mensajes de error en caso de que no sea válida.
static char *obtenerNombreEmpresa();

// Precondición: nada.
// Poscondición: devuelve el nombre de usuario que se introduzca, con varios mensajes de error en caso de que no sea válida.
static char *obtenerCiudad();

#endif // _TRANSPORTISTA_H_