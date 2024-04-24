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

void consultaPedidosCli(tCliente *cli);

unsigned numPedidos();

static void realizarPedido(tCliente *cliente);

static void recrearFicheroProductos(tProductos *Productos, unsigned numProd);

static void darAltaPedido(tCliente Cliente, int reparto);

static void generarFecha(int *fecha, int reparto);

static void guardarNuevoPedido(char *destino, tPedidos datos);

static void estadoPedidos(tCliente *cliente);

static void idEncontrada(tPedidos *pedido);

static void dividirCadenaPed(char *temp, char del[], tPedidos *pedido);

#endif