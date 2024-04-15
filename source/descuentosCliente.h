#ifndef DESCUENTOSCLIENTE_H_
#define DESCUENTOSCLIENTE_H_

typedef struct{
    char Id_cliente[8];
    char Id_cod[11];
    char fechaAsignacion[11];   //DD/MM/AAAA
    char fechaCaducidad[11];    //DD/MM/AAAA
    bool Estado;    //1 es aplicado, 0 es no aplicado

}descuentosCliente;

void loqsea();

#endif