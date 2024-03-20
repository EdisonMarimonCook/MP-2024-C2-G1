#include <stdio.h>
#include <stdlib.h>		// exit
#include <string.h>
#include "lockers.h"
#include "clientes.h"
void vaciarl(char temp[]);
void mostrarMenu();
void buscarLocker(tLockers *lock, int numLockers);
void copiarl(char temp[],int i);
int main(){
	//*system("cls");

	//int op;

	//do {
		//printf("\t\tESIZON");

		//printf("\n\n\t1. Iniciar Sesion.\n");
		//printf("\t2. Registrarse.\n");
		//printf("\t0. Salir.\n\n");
		//printf("Indique la opcion: ");
		
		//if(scanf("%i", &op) != 1 || (op < 0 || op > 2)){      // Con esta condición podemos evitar que el usuario haga una entrada errónea.    
            //system("cls");
			//fflush(stdin);
            //fprintf(stderr, "Entrada no valida. Opcion Incorrecta.\n\n");
       // } else {
			//switch(op){
				//case 0: break;
				//case 1: iniciarSesionCliente(); break;
				//case 2: registrarCliente(); break;
				//default: fprintf(stderr, "Se ha producido un error.\n"); exit(1);
			//}
		//}

	//} while(op < 0 || op > 2);

	//system("pause");


    int i, j;
    char temp[100];
    char aux;
    int cont = 0;
    FILE *f;
    f = fopen("Lockers.txt","r");
    if(f==NULL){
        printf("no se ha encontrado el archivo.\n");
        exit(1);
    }
    while(!feof(f)){
       char temp[100];
       fgets(temp,100,f);
      cont++;
    }
    rewind(f);

    tLockers *lock;
    lock = (tLockers*)malloc(cont * sizeof(tLockers));
    if (lock == NULL){
        printf("no se ha podido reservar la memoria.\n");
        exit(1);
    }
    for(int i = 0; !feof(f); i++) {
        char temp[100];
        vaciarl(temp);
        char aux = '0';
        for(int j = 0; aux != '-'; j++) {
            aux = fgetc(f);
            if(aux != '-') {
                temp[j] = aux;
            }
        }
        copiarl(temp, i);
        fgets(temp, 100, f);
        printf("ID %s\n", lock[i].ID_Locker);
    }

    modificarInformacion(lock, cont);
    guardarModificaciones(lock, cont);
    mostrarMenu();

    for (int i = 0; i < cont; i++) {
        free(lock[i].ID_Locker);
    }
    free(lock);

    return 0;
}

void mostrarMenu(tLockers *lock, int numLockers,int cont) {
    int opcion;
    do {
        printf("\n---- MENU ----\n");
        printf("1. Buscar un locker por ID\n");
        printf("2. Modificar información de un locker\n");
        printf("3. Guardar modificaciones\n");
        printf("4. Salir\n");
        printf("Ingrese una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                buscarLocker(lock, cont);
                break;
            case 2:
                modificarInformacion(lock, cont);
                break;
            case 3:
                guardarModificaciones(lock, cont);
                break;
            case 4:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opción no válida. Por favor, ingrese una opción válida.\n");
        }
    } while (opcion != 4);
}

void buscarLocker(tLockers *lock, int numLockers) {
    char idBuscar[IDLK];
    printf("Ingrese el ID del locker que desea buscar: ");
    scanf("%s", idBuscar);

    for (int i = 0; i < numLockers; i++) {
        if (strcmp(lock[i].ID_Locker, idBuscar) == 0) {
            printf("Locker encontrado:\n");
            printf("ID: %s\n", lock[i].ID_Locker);
            printf("Ubicacion: %s\n", lock[i].Ubicacion);
            printf("Provincia: %s\n", lock[i].Provincia);
            printf("Poblacion: %s\n", lock[i].Poblacion);
            printf("Compartimentos totales: %s\n", lock[i].Compartimentos_totales);
            printf("Compartimentos ocupados: %s\n", lock[i].Compartimentos_ocupados);
            return;
        }
    }
    printf("Locker con ID %s no encontrado.\n", idBuscar);
}


void vaciarl(char temp[]) {
    for(int i = 0; i < 100; i++) {
        temp[i] = '\0';
    }
}
void copiarl(char temp[], int i){
    int N = strlen(temp) + 1;
    lock[i].ID_Locker = (char*)malloc(N * sizeof(char));
    if (lock[i].ID_Locker == NULL) {
        printf("No se ha podido reservar la memoria.\n");
        exit(1);
    }
    strcpy(lock[i].ID_Locker, temp);

}
