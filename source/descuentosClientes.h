#ifndef DESCUENTOSCLIENTES_H_
#define DESCUENTOSCLIENTES_H_

typedef struct{
    char Id_cliente[8];
    char Id_cod[11];
    char fechaAsignacion[11];   //DD/MM/AAAA
    char fechaCaducidad[11];    //DD/MM/AAAA
    int Estado;    //1 es aplicado, 0 es no aplicado

}descuentosClientes;

void menuDescuentosCliente();
static void consultarDescuentos(const char *id_cliente, descuentosClientes descuentos[], int num_descuentos);

#endif