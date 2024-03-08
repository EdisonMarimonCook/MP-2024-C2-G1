#ifndef CLIENTES_H_
#define CLIENTES_H_

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

/* FUNCIONES PUBLICAS */

// Precondición: devuelve una estructura tCliente que no puede ser NULL
// Postcondición: proporciona al cliente el menu
void menuCliente(tCliente *cliente);

// Precondición: recibe una estructura tCliente
// Postcondición: proporciona al cliente las opciones de perfil, asi como consultar datos y poder modificarlos
void perfilCliente(tCliente *cliente);

// Precondición: nada.
// Postcondición: inicia sesión en el sistema ESIZON
void iniciarSesionCliente();

// Precondición: nada.
// Postcondición: añade en el vector de estructuras tPerfil un nuevo usuario e imprime en Cliente.txt los datos de ese nuevo usuario.
void registrarCliente();

// Precondicion: recibe un vector de estructuras tipo tCliente
// Postcondicion: carga toda la informacion de Clientes.txt en infocli
void cargarClientes(tCliente *infocli);

// Precondicion: nada
// Postcondicion: devuelve un vector de tipo tCliente de tamaño igual al nº de clientes del sistema
tCliente *crearListaClientes();

// Precondición: nada.
// Postcondicion: imprime todos los clientes dados de alta en la plataforma
void imprimirClientes();


/* FUNCIONES PRIVADAS */

// Precondición: recibe una variable de tipo tCliente
// Postcondición: inserta en Clientes.txt los nuevos datos de clienteMod
static void modificarFichero(tCliente clienteMod);

// Precondición: recibe dos parámetros tipo tCliente
// Postcondición: devuelve 1 si nuevo = original y 0 en caso contrario
static int existeCambios(tCliente nuevo, tCliente original);

// Precondición: variable cliente pasada por referencia
// Postcondición: almacena en el campo Nomb_cliente el valor que proporcione el usuario
static void getNombre(tCliente *cliente);

// Precondición: variable cliente pasada por referencia
// Postcondición: almacena en el campo Dir_cliente el valor que proporcione el usuario
static void getDireccion(tCliente *cliente);

// Precondición: variable cliente pasada por referencia
// Postcondición: almacena en el campo poblacion el valor que proporcione el usuario
static void getPoblacion(tCliente *cliente);

// Precondición: variable cliente pasada por referencia
// Postcondición: almacena en el campo provincia el valor que proporcione el usuario
static void getProvincia(tCliente *cliente);

// Precondición: variable cliente pasada por referencia y un vector de datos de clientes
// Postcondición: almacena en el campo email el valor que proporcione el usuario
static void getEmail(tCliente *cliente, tCliente *datos);

// Precondición: variable cliente pasada por referencia
// Postcondición: almacena en el campo contrasenia el valor que proporcione el usuario
static void getContrasenia(tCliente *cliente);

// Precondicion: nada
// Postcondicion: devuelve el nº de clientes del sistema
static unsigned numClientes();

// Precondición: no pueden haber argumentos vacíos
// Postcondición: devuelve la posición que le corresponde al cliente si existe email y contraseña que coinciden con los parametros email y psw
static int inicioValido(tCliente *infocli, char *email, char *psw);

// Precondición: emails inicializado y clientes
// Postcondición: devuelve 1 si encuentra un email repetido y 0 en caso contrario
static int existeEmail(tCliente *clientes, char *email);

// Precondicion: destino será una cadena de caracteres y datos es de tipo tCliente
// Postcondicion: guarda el contenido de datos en el fichero destino
static void guardarDatosClienteFich(char *destino, tCliente datos);

// Precondición: recibe una cadena de caracteres y dos enteros, uno para el numero que queremos realizar la ID y el numero de dígitos de esa ID.
// Poscondición: guarda en id una cadena de caracteres, por ejemplo, si num = 12 y numDigitos = 4, en id se encontrará 0012
static void generarID(char *id, int idNum, int numDigitos);

// Precondicion: recibe un puntero a un vector dinamico de tipo tCliente
// Postcondicion: reserva espacio de memoria
static void reservarNuevoCliente(tCliente *infocli);

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

// Precondición: nada.
// Postcondicion: devuelve el saldo de la cartera introducido por el cliente.
static double obtenerCartera();

#endif // CLIENTES_H_