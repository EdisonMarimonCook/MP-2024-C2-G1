#ifndef LOCKERS_H
#define LOCKERS_H

#define IDLK 11
#define UBI 21
#define POB 21
#define PRO 21
#define TComp 50
#define OComp 50

typedef struct {
    char ID_Locker[IDLK];
    char Ubicacion[UBI];
    char Provincia[PRO];
    char Poblacion[POB];
    char Compartimentos_totales[TComp];
    char Compartimentos_ocupados[OComp];
} tLockers;

void modificarInformacion(tLockers *lock, int numLockers);
void guardarModificaciones(tLockers *lock, int numLockers);
void vaciar(char temp[]);
void copiar(char temp[], int i);

#endif /* LOCKERS_H */
