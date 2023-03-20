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
#include <math.h>
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
   int opt = 0;
   double n = 0.0; //valor ingresado por el usuario 
   double x = 0.0; //valor aproximado por el usuario 
   double y = 0.0; //aproximacion de la raiz
   double error = 0.0; //error que se compara con e   
   const double e = 0.000001;
/* END Local variables -------------------------------------------------------*/


/* User code -----------------------------------------------------------------*/
    while(1){        
        printf("Ingrese el numero del que quiere la raiz cuadrada\n");
        scanf("%lf", &n);
        printf("Ingrese una aproximacion de la raiz\n");
        scanf("%lf", &x);
        //raiz valida cuando el numero e es pequeño
        do{
            y=(n/x+x)/2; 
            error = fabs(x-y);
            x=y;
        }while(error<=e);
        printf("La raiz del numero %.2lf es %.1lf", n, y);        
        
        opt = getch();
        if(opt == 0)
            opt = getch() + 1000;
        if(opt == 27)
            break;
        clrscr();
    }

    
/* END User code -------------------------------------------------------------*/   
    return 0;
}
