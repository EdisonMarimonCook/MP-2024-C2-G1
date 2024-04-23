#ifndef DESCUENTOSCLIENTES_H_
#define DESCUENTOSCLIENTES_H_

#define MAX_ID_CLI 8
#define MAX_ID_COD 11
#define MAX_FECHA_ASIG 11
#define MAX_FECHA_CAD 11
#define MAX_LIN_FICH_DESC_CLI 47

typedef struct{
    char Id_cliente[MAX_ID_CLI];
    char Id_cod[MAX_ID_COD];
    char fechaAsignacion[MAX_FECHA_ASIG];   //DD/MM/AAAA
    char fechaCaducidad[MAX_FECHA_CAD];    //DD/MM/AAAA
    int Estado;    //1 es aplicado, 0 es no aplicado

}descuentosClientes;

void menuDescuentosCliente();
static void consultarDescuentos(const char *id_cliente, descuentosClientes descuentos[], int num_descuentos);

#endif