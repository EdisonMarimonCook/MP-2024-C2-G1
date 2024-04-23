#ifndef _PEDIDOS_H_
#define _PEDIDOS_H_

#include "productos.h"
#include "clientes.h"   // ID

#define LUGAR 10        // max es domicilio = 9 caracteres
#define LOCKER 11       // max 10 caracteres

typedef struct{
    char id_pedido[ID];
    int fecha[3];
    char id_cliente[ID];
    char lugar[LUGAR];
    char id_locker[LOCKER];
    char id_cod[11];            // MACRO EDISON
}tPedidos;

void consultaPedidosCli(tCliente *cli);

static void realizarPedido(tCliente *cliente);

static void recrearFicheroProductos(tProductos *Productos, unsigned numProd);

#endif