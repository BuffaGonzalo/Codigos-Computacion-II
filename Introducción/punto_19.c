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
    char caracter;
    unsigned char x,y;
    int opt = 0;
/* END Local variables -------------------------------------------------------*/


/* User code -----------------------------------------------------------------*/
    while(1){
        printf("Programa constructor de un triangulo a partir de un caracter ASCII ingresado\n");        
        printf("Ingrese la tecla a partir de la cual realizar el triangulo\n");
        scanf("%c", &caracter);
        //scanf("%hhd", &caracter); para introducir el numero del caracter en ASCII
        for(x=0;x<=6;x++){
            for(y=0;y<x;y++){
                printf("%c\t", caracter);
                caracter++;            
                }
            printf("\n");       
        }
        
        printf("Presione ESC para salir, cualquier otra tecla para continuar\n");
        
        opt = getch();
        if(opt == 0)
            opt = getch() + 1000;
        if(opt == 27)
            break;
    }
  
/* END User code -------------------------------------------------------------*/
    return 0;
}
