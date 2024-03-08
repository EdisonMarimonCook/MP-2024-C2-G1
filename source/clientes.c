#include <stdio.h>      
#include <stdlib.h>    // exit
#include <string.h>    // sscanf

#include "clientes.h"
#include "productos.h"

/* FUNCIONES PUBLICAS */

void menuCliente(tCliente cliente){
    system("cls");

    int op;

    do {
        printf("Menu: Tipo Cliente.\n\n");
        printf("\t\tUsuario: %s\n\n", cliente.Nomb_cliente);
        printf("1. Perfil.\n");
        printf("2. Productos.\n");
        printf("3. Descuentos.\n");
        printf("4. Pedidos.\n");
        printf("5. Devoluciones.\n");
        printf("6. Salir del sistema.\n\n");

        printf("Inserte la opcion: ");

        if(scanf("%i", &op) != 1 || op < 1 && op > 6){
            system("cls");
            fflush(stdin);
            fprintf(stderr, "Entrada no valida.\n\n");
        } else{
            switch(op){
                case 1: break;
                case 2: break;
                case 3: break;
                case 4: break;
                case 5: break;
                case 6: break;
                default: fprintf(stderr, "Se ha producido un error\n"); exit(1);
            }
        }

    } while(op < 1 && op > 6);
}

void iniciarSesionCliente(){
    system("cls");
    printf("\t\t\tESIZON\n\n");

    int op = 0; 
    tCliente *infocli;
    char email[EMAIL], psw[PASS];

    infocli = crearListaClientes();
    cargarClientes(infocli);

    do {
        op = 0;

        printf("Usuario (direccion email): ");
        fflush(stdin);
        fgets(email, EMAIL, stdin);

        printf("Contrasena: ");
        fflush(stdin);
        fgets(psw, PASS, stdin);

        // es importante eliminar el \n
        email[strcspn(email, "\n")] = 0;
        psw[strcspn(psw, "\n")] = 0;

        // comprobamos si el inicio es valido o no
        if(inicioValido(infocli, email, psw) == 0){
            fprintf(stderr, "\nEl usuario o la contrasena no coinciden.\n\n");

            // manejo de opciones
            do {
                printf("\nDesea registrarse? (1) o intentarlo de nuevo (2): ");

                if(scanf("%i", &op) != 1 || op != 1 && op != 2){
                    fflush(stdin);
                    fprintf(stderr, "Entrada no valida.");
                }

            } while(op != 1 && op != 2);
        }

    } while(inicioValido(infocli, email, psw) == 0 && op != 1);

    free(infocli);

    if(op == 1)
        registrarCliente();    // linea 75 el usuario es preguntado por registrarse (opcion 1)
    else if(inicioValido(infocli, email, psw)){
        int pos = inicioValido(infocli, email, psw)-1;    // inicioValido devuelve la posicion que le corresponde al cliente en el vector infocli
        menuCliente(infocli[pos]);      // menu principal del cliente
    }
}

void registrarCliente(){
    system("cls");
    printf("\t\t\tESIZON\n\n");

    tCliente *datos;
    unsigned nClientes = numClientes();

    datos = crearListaClientes();
    cargarClientes(datos);

    if(nClientes != 0)
        reservarNuevoCliente(datos);    // crearListaCliente si nClientes es cero reserva 1 posicion

    // Obtenemos los datos del cliente

    generarID(datos[nClientes].Id_cliente, nClientes+1, ID-1);
    obtenerNombreCliente(datos[nClientes].Nomb_cliente);
    obtenerDireccion(datos[nClientes].Dir_cliente);
    obtenerPoblacion(datos[nClientes].Poblacion);
    obtenerProvincia(datos[nClientes].Provincia);
    obtenerEmail(datos[nClientes].email);

    // comprobamos que ningún email se repita
    if(existeEmail(datos, datos[nClientes].email)){
        fprintf(stderr, "El email ya esta registrado en ESIZON.\n");
        limpiarCadena(datos[nClientes].email, EMAIL);
        obtenerEmail(datos[nClientes].email);
    }

    obtenerContrasenia(datos[nClientes].Contrasenia);
    datos[nClientes].Cartera = obtenerCartera();

    tCliente nuevoCliente = datos[nClientes];

    // Guardamos los datos del cliente
    guardarDatosClienteFich("../datos/Clientes.txt", nuevoCliente);

    free(datos);

    menuCliente(nuevoCliente);
}

void cargarClientes(tCliente *infocli){
    int i;
    char buffer[MAX_LIN_FICH_CLI];

    if(numClientes() != 0){    // Comprobamos si existe algún usuario en Usuarios.txt
        FILE *pf;

        pf = fopen("../datos/Clientes.txt", "r");    // Abrimos el fichero en tipo lectura.

        if(pf == NULL){     // Comprobamos si su apertura es correcta.
            fprintf(pf, "Error en la apertura de archivos.\n");
            exit(1);
        }

        for(i = 0; i < numClientes(); ++i){   // Recorremos el vector
            // Cogemos línea por línea, ya que sabemos que MAX_LIN_FICH es el máximo que ocupara cada línea de Usuarios.txt
            // Tras recoger una línea completa, eliminamos el \n y lo transformamos por un \0, y dicha cadena la metemos en los campos de infoper gracias a sscanf.
            if(fgets(buffer, MAX_LIN_FICH_CLI, pf) != NULL){
                buffer[strcspn(buffer, "\n")] = '\0';
                sscanf(buffer, "%[^-]-%[^-]-%[^-]-%[^-]-%[^-]-%[^-]-%[^-]-%lf", infocli[i].Id_cliente, infocli[i].Nomb_cliente, 
                                                                     infocli[i].Dir_cliente, infocli[i].Poblacion, 
                                                                     infocli[i].Provincia, infocli[i].email, 
                                                                     infocli[i].Contrasenia, &infocli[i].Cartera);
            }
        }

        fclose(pf); // Cerramos fichero.
    }
}

tCliente *crearListaClientes(){
    tCliente *clientes;

    // Reservamos la memoria necesaria gracias a la función numClientes()
    if(numClientes() == 0)
        clientes = (tCliente *)calloc(numClientes()+1, sizeof(tCliente)); 
    else
        clientes = (tCliente *)calloc(numClientes(), sizeof(tCliente));

    if(clientes == NULL){   // Comprobamos si surge algún error en la asignación
        fprintf(stderr, "Error en la asignacion de memoria.");
        exit(1);
    }

    return clientes;    // Devolvemos dicho vector.
}

void imprimirClientes(){
    FILE *pf;

    pf = fopen("../datos/Clientes.txt", "r");

    if(pf == NULL){
        fprintf(stderr, "Error en la apertura de ficheros.\n");
        exit(1);
    }

    char buffer[MAX_LIN_FICH_CLI];  

    // leemos linea a linea el fichero Clientes.txt
    while(fgets(buffer, MAX_LIN_FICH_CLI, pf) != NULL)
        printf("%s", buffer);

    fclose(pf);
}


/* FUNCIONES PRIVADAS */

static unsigned numClientes(){
    // Sabemos que el fichero Clientes.txt tendrá tantas lineas como clientes en el sistema ESIZON
    char buffer[MAX_LIN_FICH_CLI];
    FILE *pf;
    unsigned i = 0;

    pf = fopen("../datos/Clientes.txt", "r");

    if(pf == NULL){
        fprintf(stderr, "Error en la apertura del fichero.\n");
        exit(1);
    }

    // Hasta que no se llegue al fin de fichero, contamos linea a linea
    while(!feof(pf)){
        fgets(buffer, MAX_LIN_FICH_CLI, pf);
        ++i;
    }

    fclose(pf);

    return i;
}

static int inicioValido(tCliente *infocli, char *email, char *psw){
    int i = 0, fin = 0;

    while(i < numClientes() && !fin){
        if(strcmp(infocli[i].email, email) == 0 && strcmp(infocli[i].Contrasenia, psw) == 0)
            fin = 1;

        ++i;
    }

    if(fin == 1)
        fin = i;    // devolvemos en que posicion se ha encontrado del vector infocli

    return fin;
}

static int existeEmail(tCliente *clientes, char *email){
    int i = 0, fin = 0;

    // buscamos si coinciden dos emails
    while(i < numClientes() && !fin){
        if(strcmp(clientes[i].email, email) == 0)
            fin = 1;    // se han encontrado dos emails iguales
        
        ++i;
    }

    return fin;
}

static void guardarDatosClienteFich(char *destino, tCliente datos){
    FILE *pf;

    pf = fopen(destino, "a");   // append

    if(pf == NULL){
        fprintf(stderr, "Error en la apertura de archivos.\n");
        exit(1);
    }
    
    fprintf(pf, "\n%s-%s-%s-%s-%s-%s-%s-%lf", datos.Id_cliente, datos.Nomb_cliente, datos.Dir_cliente,
                                           datos.Poblacion, datos.Provincia, datos.email, 
                                           datos.Contrasenia, datos.Cartera);

    fclose(pf);
}

static void generarID(char *id, int num, int numDigitos){
    if(num >= 0 && numDigitos > 0)
        sprintf(id, "%0*d", numDigitos, num);   // Transformamos num en ID con el numero de dígitos almacenados en numDigitos
    else
        fprintf(stderr, "La ID no puede ser negativa.");
}

static void reservarNuevoCliente(tCliente *infocli){
    if(numClientes() == 0)
        infocli = (tCliente *) calloc(numClientes()+1, sizeof(tCliente));
    else
        infocli = (tCliente *) realloc(infocli, (numClientes()+1)*sizeof(tCliente));
    
    if(infocli == NULL){
        fprintf(stderr, "Error en la asignacion de memoria.\n");
        exit(1);
    }
}

static void obtenerNombreCliente(char *nomCliente){
    int i = 0;
    char c;

    printf("\nEscriba su nombre completo (maximo 20 caracteres): ");
    fflush(stdin);

    while((c = getchar()) != '\n' && i < NOM){    // Recogemos caracter a caracter para controlar el tamaño de entrada
        nomCliente[i] = c;
        i++;
    }

    nomCliente[i] = '\0';           // Añadimos el \0 final

    // Comprobamos si el tamaño es correcto, en caso de no serlo, limpiamos la cadena y volvemos a llamar a la función
    if(strlen(nomCliente) > NOM-1){
        fprintf(stderr, "El nombre completo excede los 20 caracteres.");
        limpiarCadena(nomCliente, NOM);
        obtenerNombreCliente(nomCliente);
    } 
    
    if(strlen(nomCliente) == 0){
        fprintf(stderr, "El nombre completo no puede estar vacio.");
        limpiarCadena(nomCliente, NOM);
        obtenerNombreCliente(nomCliente);
    } 
}

static void obtenerDireccion(char *nomDireccion){
    int i = 0;
    char c;

    printf("\nEscribe el nombre de su direccion (maximo 50 caracteres): ");
    fflush(stdin);

    while((c = getchar()) != '\n' && i < DIR){        // Recogemos caracter a caracter para controlar el tamaño de entrada
        nomDireccion[i] = c;
        i++;
    }

    nomDireccion[i] = '\0';         // Añadimos el \0 final

    // Comprobamos si el tamaño es correcto, en caso de no serlo, limpiamos la cadena y volvemos a llamar a la función
    if(strlen(nomDireccion) > DIR-1){
        fprintf(stderr, "El nombre de la direccion excede los 50 caracteres.");
        limpiarCadena(nomDireccion, DIR);
        obtenerDireccion(nomDireccion);
    }

    if(strlen(nomDireccion) == 0){
        fprintf(stderr, "El nombre de la direccion no puede estar vacio.");
        limpiarCadena(nomDireccion, DIR);
        obtenerDireccion(nomDireccion);
    }
}

static void obtenerPoblacion(char *nomPoblacion){
    int i = 0;
    char c;

    printf("\nEscribe el nombre de su poblacion (maximo 20 caracteres): ");
    fflush(stdin);

    while((c = getchar()) != '\n' && i < POB){        // Recogemos caracter a caracter para controlar el tamaño de entrada
        nomPoblacion[i] = c;
        i++;
    }

    nomPoblacion[i] = '\0';         // Añadimos el \0 final

    // Comprobamos si el tamaño es correcto, en caso de no serlo, limpiamos la cadena y volvemos a llamar a la función
    if(strlen(nomPoblacion) > POB-1){
        fprintf(stderr, "El nombre de la poblacion excede los 20 caracteres.");
        limpiarCadena(nomPoblacion, POB);
        obtenerPoblacion(nomPoblacion);
    }

    if(strlen(nomPoblacion) == 0){
        fprintf(stderr, "El nombre de la poblacion no puede estar vacio.");
        limpiarCadena(nomPoblacion, POB);
        obtenerPoblacion(nomPoblacion);
    }
}

static void obtenerProvincia(char *nomProvincia){
    int i = 0;
    char c;

    printf("\nEscribe el nombre de su provincia (maximo 20 caracteres): ");
    fflush(stdin);

    while((c = getchar()) != '\n' && i < POB){        // Recogemos caracter a caracter para controlar el tamaño de entrada
        nomProvincia[i] = c;
        i++;
    }

    nomProvincia[i] = '\0';         // Añadimos el \0 final

    // Comprobamos si el tamaño es correcto, en caso de no serlo, limpiamos la cadena y volvemos a llamar a la función
    if(strlen(nomProvincia) > POB-1){
        fprintf(stderr, "El nombre de la provincia excede los 20 caracteres.");
        limpiarCadena(nomProvincia, POB);
        obtenerProvincia(nomProvincia);
    }

    if(strlen(nomProvincia) == 0){
        fprintf(stderr, "El nombre de la provincia no puede estar vacio.");
        limpiarCadena(nomProvincia, POB);
        obtenerProvincia(nomProvincia);
    }
}

static void obtenerEmail(char *nomEmail){
    int i = 0;
    char c;

    printf("\nEscriba su email (maximo 30 caracteres): ");
    fflush(stdin);

    while((c = getchar()) != '\n' && i < EMAIL){        // Recogemos caracter a caracter para controlar el tamaño de entrada
        nomEmail[i] = c;
        i++;
    }

    nomEmail[i] = '\0';         // Añadimos el \0 final

    // Comprobamos si el tamaño es correcto, en caso de no serlo, limpiamos la cadena y volvemos a llamar a la función
    if(strlen(nomEmail) > EMAIL-1){
        fprintf(stderr, "El email excede los 30 caracteres.");
        limpiarCadena(nomEmail, EMAIL);
        obtenerEmail(nomEmail);
    }

    if(strlen(nomEmail) == 0){
        fprintf(stderr, "El email no puede estar vacio.");
        limpiarCadena(nomEmail, EMAIL);
        obtenerEmail(nomEmail);
    }
}

static void obtenerContrasenia(char *contrasenia){
    int i = 0;
    char c;

    printf("\nEscribe la contrasena (maximo 15 caracteres): ");
    fflush(stdin);

    while((c = getchar()) != '\n' && i < PASS){        // Recogemos caracter a caracter para controlar el tamaño de entrada
        contrasenia[i] = c;
        i++;
    }

    contrasenia[i] = '\0';       // Añadimos el \0 final

    // Comprobamos si el tamaño es correcto, en caso de no serlo, limpiamos la cadena y volvemos a llamar a la función
    if(strlen(contrasenia) > PASS-1){
        fprintf(stderr, "La contrasena excede los 15 caracteres.");
        limpiarCadena(contrasenia, PASS);
        obtenerContrasenia(contrasenia);
    }

    if(strlen(contrasenia) == 0){
        fprintf(stderr, "La contrasena no puede estar vacio.");
        limpiarCadena(contrasenia, PASS);
        obtenerContrasenia(contrasenia);
    } 
}

static double obtenerCartera() {
    double saldoIni = 0;
    
    printf("\nIndique su saldo inicial (formato 0.00euros): ");
    
    while(scanf("%lf", &saldoIni) != 1 || saldoIni < 0) {
        fflush(stdin);
        fprintf(stderr, "Entrada no esperada. Intente de nuevo.\n");
        printf("Indique su saldo inicial: ");
    }
    
    return saldoIni;
}

static void limpiarCadena(char *cad, int tam){
    int i;

    for(i = 0; i < tam; i++)    // Recorremos la cadena e introducimos el \0 en cada posición.
        cad[i] = '\0';

}