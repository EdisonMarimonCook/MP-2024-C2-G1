#include <stdio.h>      
#include <stdlib.h>    // exit
#include <string.h>    // sscanf

#include "clientes.h"

/* FUNCIONES PUBLICAS */

void menuCliente(tCliente *cliente){
    system("cls");

    int op, fin = 0;

    do {
        printf("Menu: Tipo Cliente.\n\n");
        printf("\t\tUsuario: %s\n\n", cliente->Nomb_cliente);
        printf("1. Perfil.\n");
        printf("2. Productos.\n");
        printf("3. Descuentos.\n");
        printf("4. Pedidos.\n");
        printf("5. Devoluciones.\n");
        printf("6. Salir del sistema.\n\n");

        printf("Inserte la opcion: ");

        if(scanf("%i", &op) != 1 || op < 1 || op > 6){
            system("cls");
            fflush(stdin);
            fprintf(stderr, "Entrada no valida.\n\n");
        } else{
            // Menu Clientes
            switch(op){
                case 1: perfilCliente(cliente); break;
                case 2: break;
                case 3: break;
                case 4: break;
                case 5: break;
                case 6: fin = 1; break;
                default: fprintf(stderr, "Se ha producido un error\n"); exit(1);
            }
        }

    } while(op < 1 || op > 6 || !fin);
}

void perfilCliente(tCliente *cliente){
    system("cls");

    int op;
    tCliente *datos;    // nos se puede declarar dentro del bloque Switch
    tCliente original = *cliente;

    datos = crearListaClientes(); 
    cargarClientes(datos); 

    do {
        printf("Perfil.\n\n");
        printf("\t1. Usuario: %s\n", cliente->Nomb_cliente);
        printf("\t2. Direccion: %s\n", cliente->Dir_cliente);
        printf("\t3. Poblacion: %s\n", cliente->Poblacion);
        printf("\t4. Provincia: %s\n", cliente->Provincia);
        printf("\t5. Email: %s\n", cliente->email);
        printf("\t6. Contrasena: %s\n", cliente->Contrasenia);
        printf("\t7. Saldo en la cartera: %.2lf euros\n", cliente->Cartera);
        printf("\t8. Volver.\n\n");

        printf("Pulse opcion si desea modificar algun dato: ");

        if(scanf("%i", &op) != 1 || op < 1 || op > 8){
            system("cls");
            fflush(stdin);
            fprintf(stderr, "Entrada no valida.\n\n");
        } else{
            // TODO : datos cambiados que se modifiquen en el txt
            switch(op){
                case 1: getNombre(cliente); break;
                case 2: getDireccion(cliente); break;
                case 3: getPoblacion(cliente); break;
                case 4: getProvincia(cliente); break;
                case 5: 
                    
                    getEmail(cliente, datos); 
                     
                    break;
                case 6: getContrasenia(cliente); break;
                case 7: cliente->Cartera = obtenerCartera(); break;
                case 8: break;
                default: fprintf(stderr, "Se ha producido un inesperado.\n"); exit(1);
            }

            system("cls"); 
        }

    } while(op < 1 || op > 8);

    // si se ha producido algun cambio, es necesario modificar Clientes.txt
    if(existeCambios(*cliente, original))
        modificarFichero(*cliente);

    free(datos);
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

        // es importante eliminar el \n para que no haya problemas
        // comprobando si es un inicio valido
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

    int pos = inicioValido(infocli, email, psw)-1;    // inicioValido devuelve la posicion que le corresponde al cliente en el vector infocli
    tCliente aux = infocli[pos];
    free(infocli);

    if(op == 1)
        registrarCliente();    // linea 75 el usuario es preguntado por registrarse (opcion 1)
    else if(inicioValido(infocli, email, psw))
        menuCliente(&aux);      // menu principal del cliente
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
    getNombre(&datos[nClientes]);
    getDireccion(&datos[nClientes]);
    getPoblacion(&datos[nClientes]);
    getProvincia(&datos[nClientes]);
    getEmail(&datos[nClientes], datos);
    getContrasenia(&datos[nClientes]);
    datos[nClientes].Cartera = obtenerCartera();

    tCliente nuevoCliente = datos[nClientes];
    
    // liberamos memoria que ya no nos hace falta
    free(datos);    

    // Guardamos los datos del cliente
    guardarDatosClienteFich("../datos/Clientes.txt", nuevoCliente);

    menuCliente(&nuevoCliente);
}

void cargarClientes(tCliente *infocli){
    int i;
    char buffer[MAX_LIN_FICH_CLI];

    if(numClientes() != 0){    // Comprobamos si existe algún usuario en Clientes.txt
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

// TODO: que funcione esta función
static void modificarFichero(tCliente clienteMod){
    FILE *pf, *temp;
    char buffer[MAX_LIN_FICH_CLI];
    char *fich = "../datos/Clientes.txt";
    char *fichTemp = "../datos/Temp-Clientes.txt";

    pf = fopen(fich, "r");
    temp = fopen(fichTemp, "w");

    if(pf == NULL || temp == NULL){
        fprintf(stderr, "Error en la apertura de ficheros.\n");
        exit(1);
    }

    // Buscar la ID en el fichero y cambiar la linea por los datos de clienteMod
    while(fgets(buffer, MAX_LIN_FICH_CLI, pf) != NULL){
        char idFich[ID];
        
        strncpy(idFich, buffer, 7);    // En id se almacena los 7 primeros caracteres de cada linea

        // En temp se guardara el fichero modificado
        if(strcmp(idFich, clienteMod.Id_cliente) == 0){
            // si se añade una linea de mas al final del fichero, tendremos problemas con el numClientes
            if(numClientes() == atoi(idFich))
                fprintf(temp, "%s-%s-%s-%s-%s-%s-%s-%lf", clienteMod.Id_cliente, clienteMod.Nomb_cliente, clienteMod.Dir_cliente,
                                                            clienteMod.Poblacion, clienteMod.Provincia, clienteMod.email,
                                                            clienteMod.Contrasenia, clienteMod.Cartera);
        
            else
                fprintf(temp, "%s-%s-%s-%s-%s-%s-%s-%lf\n", clienteMod.Id_cliente, clienteMod.Nomb_cliente, clienteMod.Dir_cliente,
                                                            clienteMod.Poblacion, clienteMod.Provincia, clienteMod.email,
                                                            clienteMod.Contrasenia, clienteMod.Cartera);
        } else
            fprintf(temp, "%s", buffer);
    }

    // cerramos ficheros
    fclose(pf);
    fclose(temp);

    // Tenemos que renombrar temp y eliminar pf
    remove(fich);
    rename(fichTemp, fich); // fichTemp pasa a ser fich
}

static int existeCambios(tCliente nuevo, tCliente original){
    int boole = 1;

    if(nuevo.Nomb_cliente == original.Nomb_cliente && nuevo.Dir_cliente == original.Dir_cliente
        && nuevo.Poblacion == original.Poblacion && nuevo.Provincia == original.Provincia && nuevo.email == original.email
        && nuevo.Contrasenia == original.Contrasenia && nuevo.Cartera == original.Cartera)
        boole = 0;
    
    return boole;
}

static void getNombre(tCliente *cliente){
    char *nomCliente = NULL;

    while(!nomCliente)
        nomCliente = obtenerNombreCliente();

    strncpy(cliente->Nomb_cliente, nomCliente, NOM);
    free(nomCliente);
}

static void getDireccion(tCliente *cliente){
    char *direccion = NULL;

    while(!direccion)
        direccion = obtenerDireccion();

    strncpy(cliente->Dir_cliente, direccion, DIR);
    free(direccion);
}

static void getPoblacion(tCliente *cliente){
    char *poblacion = NULL;

    while(!poblacion)
        poblacion = obtenerPoblacion();

    strncpy(cliente->Poblacion, poblacion, POB);
    free(poblacion);
}

static void getProvincia(tCliente *cliente){
    char *provincia = NULL;

    while(!provincia)
        provincia = obtenerProvincia();

    strncpy(cliente->Provincia, provincia, POB);
    free(provincia);
}

static void getEmail(tCliente *cliente, tCliente *datos){
    char *email = NULL;

    while(!email)
        email = obtenerEmail();

    char aux[EMAIL];

    strncpy(cliente->email, email, EMAIL);
    strncpy(aux, email, EMAIL);     // para poder liberar la memoria y llamar de nuevo a la funcion sin problemas
    free(email);

    // Comprobamos si el Email introducido ya existe
    if(existeEmail(datos, aux)){
        fprintf(stderr, "El email ya esta registrado en ESIZON.\n");
        getEmail(cliente, datos);
    }    
}


static void getContrasenia(tCliente *cliente){
    char *psw = NULL;

    while(!psw)
        psw = obtenerContrasenia();

    strncpy(cliente->Contrasenia, psw, PASS);
    free(psw); 
}

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

static void generarID(char *id, int idNum, int numDigitos){
    if(idNum >= 0 && numDigitos > 0)
        sprintf(id, "%0*d", numDigitos, idNum);   // Transformamos idNum en ID con el numero de dígitos almacenados en numDigitos
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

static char *obtenerNombreCliente(){
    int i = 0;
    char c, *nomCliente;

    nomCliente = (char *) calloc(NOM, sizeof(char));

    if(nomCliente == NULL){
        fprintf(stderr, "Error en asignacion de memoria.\n");
        exit(1);
    }

    printf("\nEscriba su nombre completo (maximo 20 caracteres): ");
    fflush(stdin);

    while((c = getchar()) != '\n' && i < NOM){    // Recogemos caracter a caracter para controlar el tamaño de entrada
        nomCliente[i] = c;
        i++;
    }

    // Comprobamos si el tamaño es correcto, en caso de no serlo, limpiamos la cadena y volvemos a llamar a la función
    if(strlen(nomCliente) > NOM-1){
        fprintf(stderr, "El nombre completo excede los 20 caracteres.");
        free(nomCliente);
        return NULL;
    } 
    
    if(strlen(nomCliente) == 0){
        fprintf(stderr, "El nombre completo no puede estar vacio.");
        free(nomCliente);
        return NULL;
    }

    return nomCliente;
}

static char *obtenerDireccion(){
    int i = 0;
    char c, *nomDireccion;

    nomDireccion = (char *) calloc(DIR, sizeof(char));

    if(nomDireccion == NULL){
        fprintf(stderr, "Error en asignacion de memoria.\n");
        exit(1);
    }

    printf("\nEscribe el nombre de su direccion (maximo 50 caracteres): ");
    fflush(stdin);

    while((c = getchar()) != '\n' && i < DIR){        // Recogemos caracter a caracter para controlar el tamaño de entrada
        nomDireccion[i] = c;
        i++;
    }

    // Comprobamos si el tamaño es correcto, en caso de no serlo, limpiamos la cadena y volvemos a llamar a la función
    if(strlen(nomDireccion) > DIR-1){
        fprintf(stderr, "El nombre de la direccion excede los 50 caracteres.");
        free(nomDireccion);
        return NULL;
    }

    if(strlen(nomDireccion) == 0){
        fprintf(stderr, "El nombre de la direccion no puede estar vacio.");
        free(nomDireccion);
        return NULL;
    }

    return nomDireccion;
}

static char *obtenerPoblacion(){
    int i = 0;
    char c, *nomPoblacion;

    nomPoblacion = (char *) calloc(POB, sizeof(char));

    if(nomPoblacion == NULL){
        fprintf(stderr, "Error en asignacion de memoria.\n");
        exit(1);
    }

    printf("\nEscribe el nombre de su poblacion (maximo 20 caracteres): ");
    fflush(stdin);

    while((c = getchar()) != '\n' && i < POB){        // Recogemos caracter a caracter para controlar el tamaño de entrada
        nomPoblacion[i] = c;
        i++;
    }

    // Comprobamos si el tamaño es correcto, en caso de no serlo, limpiamos la cadena y volvemos a llamar a la función
    if(strlen(nomPoblacion) > POB-1){
        fprintf(stderr, "El nombre de la poblacion excede los 20 caracteres.");
        free(nomPoblacion);
        return NULL;
    }

    if(strlen(nomPoblacion) == 0){
        fprintf(stderr, "El nombre de la poblacion no puede estar vacio.");
        free(nomPoblacion);
        return NULL;
    }

    return nomPoblacion;
}

static char *obtenerProvincia(){
    int i = 0;
    char c, *nomProvincia;

    nomProvincia = (char *) calloc(POB, sizeof(char));

    if(nomProvincia == NULL){
        fprintf(stderr, "Error en asignacion de memoria.\n");
        exit(1);
    }

    printf("\nEscribe el nombre de su provincia (maximo 20 caracteres): ");
    fflush(stdin);

    while((c = getchar()) != '\n' && i < POB){        // Recogemos caracter a caracter para controlar el tamaño de entrada
        nomProvincia[i] = c;
        i++;
    }

    // Comprobamos si el tamaño es correcto, en caso de no serlo, limpiamos la cadena y volvemos a llamar a la función
    if(strlen(nomProvincia) > POB-1){
        fprintf(stderr, "El nombre de la provincia excede los 20 caracteres.");
        free(nomProvincia);
        return NULL;
    }

    if(strlen(nomProvincia) == 0){
        fprintf(stderr, "El nombre de la provincia no puede estar vacio.");
        free(nomProvincia);
        return NULL;
    }

    return nomProvincia;
}

static char *obtenerEmail(){
    int i = 0;
    char c, *nomEmail;

    nomEmail = (char *) calloc(EMAIL, sizeof(char));

    if(nomEmail == NULL){
        fprintf(stderr, "Error en asignacion de memoria.\n");
        exit(1);
    }

    printf("\nEscriba su email (maximo 30 caracteres): ");
    fflush(stdin);

    while((c = getchar()) != '\n' && i < EMAIL){        // Recogemos caracter a caracter para controlar el tamaño de entrada
        nomEmail[i] = c;
        i++;
    }

    // Comprobamos si el tamaño es correcto, en caso de no serlo, limpiamos la cadena y volvemos a llamar a la función
    if(strlen(nomEmail) > EMAIL-1){
        fprintf(stderr, "El email excede los 30 caracteres.");
        free(nomEmail);
        return NULL;
    }

    if(strlen(nomEmail) == 0){
        fprintf(stderr, "El email no puede estar vacio.");
        free(nomEmail);
        return NULL;
    }

    return nomEmail;
}

static char *obtenerContrasenia(){
    int i = 0;
    char c, *contrasenia;

    contrasenia = (char *) calloc(PASS, sizeof(char));

    if(contrasenia == NULL){
        fprintf(stderr, "Error en asignacion de memoria.\n");
        exit(1);
    }

    printf("\nEscribe la contrasena (maximo 15 caracteres): ");
    fflush(stdin);

    while((c = getchar()) != '\n' && i < PASS){        // Recogemos caracter a caracter para controlar el tamaño de entrada
        contrasenia[i] = c;
        i++;
    }

    // Comprobamos si el tamaño es correcto, en caso de no serlo, limpiamos la cadena y volvemos a llamar a la función
    if(strlen(contrasenia) > PASS-1){
        fprintf(stderr, "La contrasena excede los 15 caracteres.");
        free(contrasenia);
        return NULL;
    }

    if(strlen(contrasenia) == 0){
        fprintf(stderr, "La contrasena no puede estar vacio.");
        free(contrasenia);
        return NULL;
    } 

    return contrasenia;
}

static double obtenerCartera() {
    double saldoIni = 0;
    
    printf("\nIndique su saldo (formato 0.00euros): ");
    
    while(scanf("%lf", &saldoIni) != 1 || saldoIni < 0) {
        fflush(stdin);
        fprintf(stderr, "Entrada no esperada. Intente de nuevo.\n");
        printf("Indique su saldo: ");
    }
    
    return saldoIni;
}
