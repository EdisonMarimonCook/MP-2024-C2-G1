#ifndef CLIENTES_H_
#define CLIENTES_H_

#define NOM 21
#define DIR 51
#define POB 21
#define EMAIL 31
#define PASS 16

typedef struct {
    unsigned id;            // Identificador del cliente
    char nombre[NOM];       // Nombre completo del cliente
    char direccion[DIR];    // Direccion del cliente
    char poblacion[POB];    // Localidad del cliente
    char provincia[POB];    // Provincia del cliente
    char email[EMAIL];      // Email del cliente
    char contrasenia[PASS]; // Contraseña de acceso al sistema
    double cartera;         //  almacenará el dinero del que dispone el cliente
} tCliente;

#endif // CLIENTES_H_