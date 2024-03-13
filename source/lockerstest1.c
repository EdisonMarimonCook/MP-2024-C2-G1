#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define IDLK 11
#define UBI 21
#define POB 21
#define PRO 21
#define TComp 50
#define OComp 50

typedef struct{
    char ID_Locker[IDLK];
    char Ubicacion[UBI];
    char Provincia[PRO];
    char Poblacion[POB];
    char Compartimentos_totales[TComp];
    char Compartimentos_ocupados[OComp];
}tLockers;

tLockers *lock;
void modificarInformacion(tLockers *lock, int numLockers);
void guardarModificaciones(tLockers *lock, int numLockers);
void vaciar(char temp[]);
void copiar(char temp[],int i);
int main(){
    int i,j;
     char temp[100];
     char aux;
     int cont = 0;
    FILE *f;
    f = fopen("Lockers.txt","r");
    if(f==NULL){
        printf("no se ha encontrado el archivo.\n");
        exit(1);
    }
    while(!feof(f)){//Lock
       fgets(temp,100,f);
      cont++;
    }
    rewind(f);

    lock=(tLockers*)malloc(cont*sizeof(tLockers));
    if (lock == NULL){
        printf("no se ha podido reservar la memoria.\n");
        exit(1);
    }
    for(i=0;!feof(f);i++){
        vaciar(temp);
        aux='0';
        for(j=0;aux!='-';j++){
            aux = fgetc(f);
            if(aux!='-'){
                temp[j]=aux;
            }
        }
        copiar(temp,i);
        fgets(temp,100,f);
        printf("ID %s\n",lock[i].ID_Locker);
    }
        modificarInformacion(lock, cont);
        guardarModificaciones(lock, cont);
        for (int i = 0; i < cont; i++) {
        free(lock[i].ID_Locker);
    }
    free(lock);

return 0;
}
void vaciar(char temp[]){
    int i;

    for(i=0;i<100;i++){
        temp[i]='\0';
    }
}
void copiar(char temp[], int i) {
    int N = strlen(temp) + 1;
    lock[i].ID_Locker = (char*)malloc(N * sizeof(char));//error aqui
    if (lock[i].ID_Locker == NULL) {
        printf("No se ha podido reservar la memoria.\n");
        exit(1);
    }
    strcpy(lock[i].ID_Locker, temp);
}
void modificarInformacion(tLockers *lock, int numLockers) {
    char idBuscar[IDLK];
    printf("Ingrese el ID del locker que desea modificar: ");
    scanf("%s", idBuscar);

    for (int i = 0; i < numLockers; i++) {
        if (strcmp(lock[i].ID_Locker, idBuscar) == 0) {
            printf("Ingrese la nueva información del locker:\n");
            printf("Ubicacion: ");
            scanf("%s", lock[i].Ubicacion);
            printf("Provincia: ");
            scanf("%s", lock[i].Provincia);
            printf("Poblacion: ");
            scanf("%s", lock[i].Poblacion);
            printf("Compartimentos totales: ");
            scanf("%s", lock[i].Compartimentos_totales);
            printf("Compartimentos ocupados: ");
            scanf("%s", lock[i].Compartimentos_ocupados);
            break;
        }
    }
}

void guardarModificaciones(tLockers *lock, int numLockers) {
    FILE *f = fopen("Lockers.txt", "w");
    if (f == NULL) {
        printf("Error al abrir el archivo para escritura.\n");
        exit(1);
    }

    for (int i = 0; i < numLockers; i++) {
        fprintf(f, "%s-%s-%s-%s-%s-%s\n", lock[i].ID_Locker, lock[i].Ubicacion, lock[i].Provincia,
                lock[i].Poblacion, lock[i].Compartimentos_totales, lock[i].Compartimentos_ocupados);
    }

    fclose(f);
}
