/* ========================================================================== */
/*                                                                            */
/*   Filename.c                                                               */
/*   (c) 2023 Author:                                                         */
/*                                                                            */
/*   Description:                                                             */
/*                                                                            */
/* ========================================================================== */

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <conio.h>
/* END Includes --------------------------------------------------------------*/


/* typedef -------------------------------------------------------------------*/

/* END typedef ---------------------------------------------------------------*/


/* define --------------------------------------------------------------------*/

/* END define ----------------------------------------------------------------*/


/* Function prototypes -------------------------------------------------------*/

/* END Function prototypes ---------------------------------------------------*/


/* Global variables ----------------------------------------------------------*/

/* END Global variables ------------------------------------------------------*/


/* Fuction prototypes user code ----------------------------------------------*/

/* END Fuction prototypes user code ------------------------------------------*/

int main()
{
/* Local variables -----------------------------------------------------------*/
    int entero, posicion, resto, num, opc, digito;

/* END Local variables -------------------------------------------------------*/


/* User code -----------------------------------------------------------------*/
    while(1){   
        clrscr();    
        printf("CONVERSOR DE ENTERO A BINARIO\n");
        printf("Ingrese un numero - entero positivo\n");
        scanf("%i", &num);
         
        entero = num; //asignamos a entero el valor ingresado       
        //convertimos el numero decimal en binario
        posicion = 0, digito = 1;   //igualamos a 0 antes de comenzar  
           
        while(entero>0){
            resto=entero%2;
            posicion=posicion+resto*digito;
            digito = digito*10; //digito =digito*10
            entero = entero/2; //entero = entero/2
        }
        
        printf("El numero entero %i es %i en binario\n",num, posicion);
        printf("Presione ESC para salir, cualquier otra tecla para continuar\n");
        
        opc=getch();        
        if(opc == 0)
            opc = getch() + 1000;
        if(opc == 27)
            break;
    }
/* END User code -------------------------------------------------------------*/

   return 0;
}
