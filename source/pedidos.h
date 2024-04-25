#ifndef _PEDIDOS_H_
#define _PEDIDOS_H_

#include "productos.h"
#include "clientes.h"   // ID

#define LUGAR 10        // max es domicilio = 9 caracteres
#define LOCKER 11       // max 10 caracteres
#define MAX_LIN_FICH_PED 41

typedef struct{
    char id_pedido[ID];            // 8 bytes
    int fecha[3];           
    char id_cliente[ID];           // 8 bytes
    char lugar[LUGAR];             // 10 bytes
    char id_cod[11];            // MACRO EDISON
}tPedidos;                          // TOTAL = 41 bytes


/*  FUNCIONES PUBLICAS  */

//Precondicion: Recibe la estructura del cliente
//Postcondicion: realiza un pedido o una consulta
void consultaPedidosCli(tCliente *cli);

//Precondicion: Recibe la estructura del admin/prov
//Postcondicion: depende de la accion realizada así sera la postcondicion
void consultaPedidosAdmin(tAdminProv *admin);

//Precondicion: nada
//Postcondicion: devuelve el numero de pedidos que hay en el fichero Pedidos.txt
unsigned numPedidos();


/*  FUNCIONES PRIVADAS  */

//Precondicion: recibe los datos del cliente
//Postcondicion: crea un pedido y lo introduce en Pedidos.txt
static void realizarPedido(tCliente *cliente);

//Precondicion: recibe los datos del cliente, numero de dias de entrega y codigo promocional
//Postcondicion: crea un pedido y lo introduce en Pedidos.txt
static void darAltaPedido(tCliente Cliente, int reparto, char *cod, unsigned numPedidos);

//Precondicion: recibe un vector de enteros y el numero de dias de entrega
//Postcondicion: devuelve la fecha de reparto del pedido
static void generarFecha(int *fecha, int reparto);

//Precondicion: recibe la ruta donde esta el fichero y una estructura inicializada con datos
//Postcondicion: en el ficheron introduce un nuevo pedido con los datos de la estructura
static void guardarNuevoPedido(char *destino, tPedidos datos);

//Precondicion: recibe los datos del cliente
//Postcondicion: devuelve la informacion de los pedidos del cliente
static void estadoPedidos(tCliente *cliente);

//Precondicion: recibe los datos de un pedido
//Postcondicion: devuelve la informacion de ese pedido
static void idEncontrada(tPedidos *pedido);

//Precondicion: Recibe una linea del fichero, el delimitador de cada dato de la linea y una estructura inicializada
//Postcondicion: devuelve la estructura con los datos de la linea del fichero
static void dividirCadenaPed(char *temp, char del[], tPedidos *pedido);

//Precondicion: nada
//Postcondicion: devuelve la informacion del fichero Pedidos.txt
static void infoPedAdmin();

//Precondicion: recibe los datos del prod/admin
//Postcondicion: da de alta un pedido y lo almacena en Pedidos.txt
static void AltaPedidoAdmin(tAdminProv admin);

//Precondicion: nada
//Postcondicion: da de baja un pedido y lo elimina de Pedidos.txt
static void darBajaPedido();

//Precondicion: recibe tantas estructuras como pedidos haya
//Postcondicion: devuelve todas las estructuras inicializadas con los datos del fichero Pedidos.txt
static void cargarPedidos(tPedidos *pedidos);

//Precondicion: nad
//Postcondicion: devuelve el listado de todos los pedidos en Pedidos.txt
static void imprimirPedidos();

//Precondicion: recibe todas las estructuras de los pedidos y el numero de pedidos
//Postcondicion: crea un nuevo fichero Pedidos.txt con los cambios realizados en los pedidos
static void recrearFicheroPedidos(tPedidos *pedidos, unsigned numPedidos);


//Precondicion: recibe dos estructuras de pedidos
//Postcondicion: devuelve un valor dependiendo si las dos estructuras son distintas
static int existeCambioPedidos(tPedidos nuevo, tPedidos original);

//Precondicion: recibe un vector de enteros
//Postcondicion: devuelve este vector con una nueva fecha
static void nuevaFecha(int *fecha);

//Precondicion: recibe una cadena de caracteres
//Postcondicion: devuelve un nuevo lugar de recogida
static void nuevoLugar(char *lugar);

//Precondicion: nada
//Postcondicion: modificara el fichero Pedidos.txt si el admin/prov cambia los datos de algun producto
static void modPedAdmin();


//Precondicion: recibe una estructura
//Postcondicion: modifica el fichero Pedidos.txt con los datos de la estructura
static void modificarFicheroPedidos(tPedidos pedidoMod);

#endif