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
    int array[10];
    int i, opt;
/* END Local variables -------------------------------------------------------*/


/* User code -----------------------------------------------------------------*/
    while(1){
        
        clrscr();    
        printf("Ingrese [ESC] para terminar\n");  
        
        opt=getch();
        if(opt==0)
            opt=getch()+1000;
        if(opt==27)
            break;        
        
        clrscr();

        for(i=0;i<10;i++){
            printf("Ingrese un numero para la posicion %i\n", i);
            scanf("%i", &array[i]);
        }


        for(i=0;i<5;i++){
            if(array[i]!=array[9-i])
                break;
        }
        
        if(i==5){ //debido a que al terminar se encuentra con el incremento
            printf("El array es simetrico");
        }
        else{
            printf("El array no es simetrico");
        }     
        getch();
    }
/* END User code -------------------------------------------------------------*/
    
   return 0;
}
