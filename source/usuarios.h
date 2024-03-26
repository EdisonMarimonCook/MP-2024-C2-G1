#ifndef _USUARIOS_H_
#define _USUARIOS_H_

#define CON_MENU 1
#define SIN_MENU 0

/* FUNCIONES PUBLICAS */

// Precondición: nada.
// Postcondición: registra a un provedor en el sistema ESIZON.
void registrarProveedor();

// Precondición: nada.
// Postcondición: inicia sesión en el sistema ESIZON.
void iniciarSesion();

// Precondición: opcion, 1 para mandar al menu el usuario registrado y 0 en caso contrario.
// Postcondición: añade en el vector de estructuras tCliente un nuevo usuario e imprime en Cliente.txt los datos de ese nuevo usuario.
void registrarse(int op);

// Precondición: emails inicializado
// Postcondición: devuelve 1 si encuentra un email repetido y 0 en caso contrario
int existeEmail(char *email);

// Precondición: recibe una cadena de caracteres y dos enteros, uno para el numero que queremos realizar la ID y el numero de dígitos de esa ID.
// Poscondición: guarda en id una cadena de caracteres, por ejemplo, si num = 12 y numDigitos = 4, en id se encontrará 0012
void generarID(char *id, int idNum, int numDigitos);

#endif // _USUARIOS_H_