#include <stdio.h>
#include <stdlib.h>		// exit

#include "usuarios.h"	// iniciarSesion()
#include "productos.h"

int main(){
	system("cls");

	int op;

	do {
		printf("\t\tESIZON");

		printf("\n\n\t1. Iniciar Sesion.\n");
		printf("\t2. Registrarse.\n");
		printf("\t0. Salir.\n\n");
		printf("Indique la opcion: ");
		
		if(scanf("%i", &op) != 1 || (op < 0 || op > 2)){      // Con esta condición podemos evitar que el usuario haga una entrada errónea.    
            system("cls");
			fflush(stdin);
            fprintf(stderr, "Entrada no valida. Opcion Incorrecta.\n\n");
        } else {
			switch(op){
				case 0: break;
				case 1: iniciarSesion(); break;
				case 2: registrarse(CON_MENU); break;	// solo puede registrarse como cliente
				default: fprintf(stderr, "Se ha producido un error.\n"); exit(1);
			}
		}

	} while(op < 0 || op > 2);

	system("pause");
	return 0;
}
