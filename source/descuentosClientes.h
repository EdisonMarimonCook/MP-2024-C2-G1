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

/* FUNCIONES PUBLICAS */

// Precondición: id del cliente que accede.
// Postcondición: proporciona al cliente el menu de descuentos.
void menuDescuentosCliente(const char *idCliente);

// Precondición: la id del cliente que accede y la id del código.
// Postcondición: guarda en el fichero los cambios y los descuentos
float obtenerDescuento(const char *id_cliente, const char *id_cod);

/* FUNCIONES PRIVADAS */

// Precondición: id del cliente que accede, los descuentos y el numero de ellos
// Postcondición: consulta si se encuentran o no codigos promocionales o cheques de regalo.
static void consultarDescuentos(const char *id_cliente, descuentosClientes descuentos[], int num_descuentos);

#endif