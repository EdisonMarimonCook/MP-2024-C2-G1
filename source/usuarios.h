#ifndef _USUARIOS_H_
#define _USUARIOS_H_

#include "clientes.h"   // tCliente
#include "adminprov.h"  // tAdminProv

typedef struct {
    tCliente *clientes;
    tAdminProv * adminprovs;
} tUsuarios;

/* FUNCIONES PUBLICAS */

// Precondición: nada.
// Postcondición: inicia sesión en el sistema ESIZON.
void iniciarSesion();

#endif // _USUARIOS_H_