#ifndef _CLIENTES_H_
#define _CLIENTES_H_

#define ID 8
#define NOM 21
#define DIR 51
#define POB 21  // para poblacion y provincia
#define EMAIL 31
#define PASS 16
#define MAX_LIN_FICH_CLI 176 // MAX_LIN_FICH es el tamaño máximo que habrá en cada linea, incluyendo los guiones

typedef struct {
    char Id_cliente[ID];            // Identificador del cliente
    char Nomb_cliente[NOM];       // Nombre completo del cliente
    char Dir_cliente[DIR];    // Direccion del cliente
    char Poblacion[POB];    // Localidad del cliente
    char Provincia[POB];    // Provincia del cliente
    char email[EMAIL];      // Email del cliente
    char Contrasenia[PASS]; // Contraseña de acceso al sistema
    double Cartera;         //  almacenará el dinero del que dispone el cliente
} tCliente;

typedef enum {
    NOMBRE, CORREO, PROVINCIA, POBLACION
} BusquedaClientes;

/* FUNCIONES PUBLICAS */

// Precondición: devuelve una estructura tCliente que no puede ser NULL
// Postcondición: proporciona al cliente el menu
void menuCliente(tCliente *cliente);

// Precondición: recibe una estructura tCliente
// Postcondición: proporciona al cliente las opciones de perfil, asi como consultar datos y poder modificarlos
void perfilCliente(tCliente *cliente);

// Precondicion: recibe un vector de estructuras tipo tCliente
// Postcondicion: carga toda la informacion de Clientes.txt en infocli
void cargarClientes(tCliente *infocli);

// Precondicion: nada
// Postcondicion: devuelve un vector de tipo tCliente de tamaño igual al nº de clientes del sistema
tCliente *crearListaClientes();

// Precondición: no pueden haber argumentos vacíos
// Postcondición: devuelve la posición que le corresponde al cliente si existe email y contraseña que coinciden con los parametros email y psw
//                devuelve 0 si no se encuentra
int inicioValidoClientes(tCliente *infocli, char *email, char *psw);

// Precondicion: destino será una cadena de caracteres y datos es de tipo tCliente
// Postcondicion: guarda el contenido de datos en el fichero destino
void guardarNuevoCliente(char *destino, tCliente datos);

// Precondicion: recibe un puntero a un vector dinamico de tipo tCliente
// Postcondicion: reserva espacio de memoria
void reservarNuevoCliente(tCliente *infocli);

// Precondicion: nada
// Postcondicion: devuelve el nº de clientes del sistema
unsigned numClientes();

// Precondición: variable cliente pasada por referencia
// Postcondición: almacena en el campo Nomb_cliente el valor que proporcione el usuario
void getNombre(tCliente *cliente);

// Precondición: variable cliente pasada por referencia
// Postcondición: almacena en el campo Dir_cliente el valor que proporcione el usuario
void getDireccion(tCliente *cliente);

// Precondición: variable cliente pasada por referencia
// Postcondición: almacena en el campo poblacion el valor que proporcione el usuario
void getPoblacion(tCliente *cliente);

// Precondición: variable cliente pasada por referencia
// Postcondición: almacena en el campo provincia el valor que proporcione el usuario
void getProvincia(tCliente *cliente);

// Precondición: variable cliente pasada por referencia 
// Postcondición: almacena en el campo email el valor que proporcione el usuario
void getEmail(tCliente *cliente);

// Precondición: variable cliente pasada por referencia
// Postcondición: almacena en el campo contrasenia el valor que proporcione el usuario
void getContrasenia(tCliente *cliente);

// Precondición: nada.
// Postcondicion: devuelve el saldo de la cartera introducido por el cliente.
double obtenerCartera();

// Precondición: nada.
// Postcondición: el administrador del sistema podrá operar en función de las opciones
//                que proporciona el menu
void administracionClientes();

// Precondición: nada.
// Postcondicion: imprime todos los clientes dados de alta en la plataforma
void imprimirClientes();

// Precondición: recibe una variable de tipo tCliente
// Postcondición: inserta en Clientes.txt los nuevos datos de clienteMod
void modificarFicheroClientes(tCliente clienteMod);

/* FUNCIONES PRIVADAS */

// Precondición: nada.
// Postcondición: elimina los clientes indicado por el administrador del sistema.
static void bajaCliente();

// Precondición: recibe un array dinamico de tipo tCliente y el numero de clientes
// Postcondición: modifica Clientes.txt con el los clientes que haya en clientes
static void recrearFichero(tCliente *clientes, int numClientes);

// Precondición: nada.
// Postcondición: modifica en Clientes.txt aquello que haya modificado el administrador
static void modificarClientes();

// Precondición: nada.
// Postcondición: menu para buscar clientes 
static void buscadorCliente();

// Precondición: nada.
// Postcondición: proporciona la busqueda por IDs de clientes.
static void buscarIDclientes();

// Precondición: un cliente en concreto.
// Postcondición: imprime los datos del cliente.
static void desgloseCompletoClientes(tCliente cliente);

// Precondición: se debe proporcionar el tipo de Busqueda, recibe un string y el tamaño de dicho string
// Postcondición: se proporciona los usuarios bajo el criterio de busqueda
static void buscarEnClientes(BusquedaClientes tipo, const char *str, unsigned tamStr);

// Precondición: se debe proporcionar el tipo de Busqueda
// Postcondición: realiza la busqueda que proporcione el administrador
static void buscarConTextoClientes(BusquedaClientes tipo);

// Precondición: recibe dos parámetros tipo tCliente
// Postcondición: devuelve 1 si nuevo = original y 0 en caso contrario
static int existeCambiosClientes(tCliente nuevo, tCliente original);

// Precondición: nada.
// Poscondición: devuelve el nombre de usuario que se introduzca, con varios mensajes de error en caso de que no sea válida.
static char *obtenerNombreCliente();

// Precondición: nada
// Poscondición: devuelve la direccion que se introduzca, con varios mensajes de error en caso de que no sea válida.
static char *obtenerDireccion();

// Precondición: nada.
// Poscondición: devuelve la poblacion que se introduzca, con varios mensajes de error en caso de que no sea válida.
static char *obtenerPoblacion();

// Precondición: nada.
// Poscondición: devuelve la provincia que se introduzca
static char *obtenerProvincia();

// Precondición: nada.
// Poscondición: devuelve el email que se introduzca
static char *obtenerEmail();

// Precondición: nada.
// Poscondición: devuelve la contraseña que se introduzca.
static char *obtenerContrasenia();



#endif // _CLIENTES_H_