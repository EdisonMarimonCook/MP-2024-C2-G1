#ifndef DESCUENTOS_H_
#define DESCUENTOS_H_

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
static void mostrarDescuentos(Descuentos *descuentos, int numDescuentos);
static void buscarDescuento(Descuentos *descuentos, int numDescuentos, char *id);
static void guardarDescuentos(Descuentos *descuentos, int numDescuentos, char *filename);

#endif