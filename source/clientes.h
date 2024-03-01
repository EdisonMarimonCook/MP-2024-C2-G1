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

// Precondicion: nada
// Postcondicion: devuelve el nº de clientes del sistema
static unsigned numClientes();

// Precondición: no pueden haber argumentos vacíos
// Postcondición: devuelve 1 si existe email y contraseña que coinciden con los parametros email y psw
static int inicioValido(tCliente *infocli, char *email, char *psw);

// Precondición: clientes y emails inicializados
// Postcondición: devuelve 1 si encuentra un email repetido y 0 en caso contrario
static int existeEmail(tCliente *clientes, char *email);

// Precondicion: destino será una cadena de caracteres y datos es de tipo tCliente
// Postcondicion: guarda el contenido de datos en el fichero destino
static void guardarDatosClienteFich(char *destino, tCliente datos);

// Precondición: recibe una cadena de caracteres y dos enteros, uno para el numero que queremos realizar la ID y el numero de dígitos de esa ID.
// Poscondición: guarda en id una cadena de caracteres, por ejemplo, si num = 12 y numDigitos = 4, en id se encontrará 0012
static void generarID(char *id, int num, int numDigitos);

// Precondicion: recibe un puntero a un vector dinamico de tipo tCliente
// Postcondicion: reserva espacio de memoria
static void reservarNuevoCliente(tCliente *infocli);

// Precondición: recibe una cadena de caracteres, la cual no debe estar inicializada
// Poscondición: guarda en la cadena el nombre de usuario que se introduzca, con varios mensajes de error en caso de que no sea válida.
static void obtenerNombreCliente(char *nomCliente);

// Precondición: recibe una cadena de caracteres, la cual no debe estar inicializada
// Poscondición: guarda en la cadena la direccion que se introduzca, con varios mensajes de error en caso de que no sea válida.
static void obtenerDireccion(char *nomDireccion);

// Precondición: recibe una cadena de caracteres, la cual no debe estar inicializada
// Poscondición: guarda en la cadena la poblacion que se introduzca, con varios mensajes de error en caso de que no sea válida.
static void obtenerPoblacion(char *nomPoblacion);

// Precondición: recibe una cadena de caracteres y el tamaño de dicha cadena.
// Poscondición: limpia la cadena poniendo \0 en todas las posiciones de la cadena
static void obtenerProvincia(char *nomProvincia);

// Precondición: recibe una cadena de caracteres y el tamaño de dicha cadena.
// Poscondición: limpia la cadena poniendo \0 en todas las posiciones de la cadena
static void obtenerEmail(char *nomEmail);

// Precondición: recibe una cadena de caracteres y el tamaño de dicha cadena.
// Poscondición: limpia la cadena poniendo \0 en todas las posiciones de la cadena
static void obtenerContrasenia(char *contrasenia);

// Precondición: nada.
// Postcondicion: devuelve el saldo de la cartera introducido por el cliente.
static double obtenerCartera();

// Precondición: recibe una cadena de caracteres y el tamaño de dicha cadena.
// Poscondición: limpia la cadena poniendo \0 en todas las posiciones de la cadena
static void limpiarCadena(char *cad, int tam);

#endif // CLIENTES_H_