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
    int opt, x, y, z = 0;

/* END Local variables -------------------------------------------------------*/


/* User code -----------------------------------------------------------------*/
    while(1){
        //parte para salida
        printf("Programa que imprime los numeros z, comprendidos entre 1 y 50, que cumplan la expresión: z^2 = x^2 + y^2, donde z, x e y son numeros enteros positivos.\n");
        
        z=1;
        while(z<=50){
            x=1;
            while(x<=50){
               y=1;
                while(y<=50){
                    if((z*z)==(x*x)+(y*y))
                        printf("z: %i, x: %i, y: %i\n", z, x, y);
                    y++;
                }
                x++;
            }
            z++;
        }
         
        printf("Presione ESC para salir, cualquier otra tecla para continuar\n");  
        
        //printf("%i", &opt);
        opt = getch();
        if(opt == 0)
            opt = getch()+1000;
        if(opt == 27)
            break;                
    }
/* END User code -------------------------------------------------------------*/
    //getch();
    return 0;
}
