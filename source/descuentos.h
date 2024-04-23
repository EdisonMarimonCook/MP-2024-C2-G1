#ifndef DESCUENTOS_H_
#define DESCUENTOS_H_

#define MAX_ID 11
#define MAX_DESCRIP 51
#define MAX_TIPO 8
#define MAX_ESTADO 9
#define MAX_APLICA 7
#define MAX_LIN_FICH_DESC 94

typedef struct{
    char id_cod[11];
    char Descrip[51];
    char Tipo[8];   //codpro, cheqreg
    char Estado[9]; //activo, inactivo
    float Importe;  //Importe del descuento en euros
    char Aplicabilidad[7];  //todos, esizon

}Descuentos;

void menuDescuentos();

static void agregarDescuento(Descuentos *descuentos, int *numDescuentos);
static void buscarDescuento(Descuentos *descuentos, int numDescuentos, char *id);
static void guardarDescuentos(Descuentos *descuentos, int numDescuentos, char *filename);

#endif