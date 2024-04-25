#ifndef DESCUENTOS_H_
#define DESCUENTOS_H_

#define MAX_ID 11
#define MAX_DESCRIP 51
#define MAX_TIPO 8
#define MAX_ESTADO 9
#define MAX_APLICA 7
#define MAX_LIN_FICH_DESC 94

typedef struct{
    char id_cod[MAX_ID];
    char Descrip[MAX_DESCRIP];
    char Tipo[MAX_TIPO];   //codpro, cheqreg
    char Estado[MAX_ESTADO]; //activo, inactivo
    float Importe;  //Importe del descuento en euros
    char Aplicabilidad[MAX_APLICA];  //todos, esizon

}Descuentos;

/* FUNCIONES PUBLICAS */

// Precondición: nada.
// Postcondición: proporciona al usuario el menu para los descuentos.
void menuDescuentos();

/* FUNCIONES PRIVADAS */

// Precondición: recibe un puntero a descuentos, un puntero a entero con el número de descuentos.
// Postcondición: Agrega un descuento al sistema.
static void agregarDescuento(Descuentos *descuentos, int *numDescuentos);

// Precondición: recibe un punteor a desceuntos, una variable con el número de descuentos y el nombre del fichero
// Postcondición: guarda los descuentos en Descuentos.txt
static void guardarDescuentos(Descuentos *descuentos, int numDescuentos, char *filename);

// Precondición: recibe un puntero a descuentos, un puntero a entero con el número de descuentos y la id.
// Postcondición: elimina el descuento indicado con los parametros de la precondicion.
static void eliminarDescuento(Descuentos *descuentos, int *numDescuentos, char *id);

// Precondición: 
// Postcondición:
static void mostrarDescuentos(Descuentos *descuentos, int numDescuentos);

#endif