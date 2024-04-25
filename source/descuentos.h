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

void menuDescuentos();

static void agregarDescuento(Descuentos *descuentos, int *numDescuentos);
static void guardarDescuentos(Descuentos *descuentos, int numDescuentos, char *filename);
static void eliminarDescuento(Descuentos *descuentos, int *numDescuentos, char *id);
static void mostrarDescuentos(Descuentos *descuentos, int numDescuentos);

#endif