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

void informacion_lockers();

int main(){
    FILE *f;
    char aux,aux2;
    f = fopen("Lockers.txt","r");
    if(f==NULL){
        printf("no se ha encontrado el archivo.\n");
        exit(1);
    }
    while(!feof(f)){//Lock
       aux = fgetc(f);
       printf("%o",aux);
    }
    printf("\n");
    fclose(f);


    f = fopen("Lockers.txt","r");
    if(f==NULL){
        printf("no se ha encontrado el archivo.\n");
        exit(1);
      }
    while(!feof(f)){
      fgets(aux2,100,f);
       printf("%s",aux2);
    }
    printf("\n");
    fclose(f);
return 0;
}
