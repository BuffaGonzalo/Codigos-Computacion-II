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
    int month, year = 0;
/* END Local variables -------------------------------------------------------*/


/* User code -----------------------------------------------------------------*/
    printf("ingrese la fecha mm/aaaa\n");
    printf("Ingrese el anio\t");
    scanf("%i\n", &year);
    printf("ingrese el mes\t");
    scanf("%i\n", &month);
    
    //controlamos que el mes no sea superior a diciembre
    if((month>12)||month<0){
        return 0;
    } 
    
    switch(month){
        case 1: //enero
        case 3: //marzo
        case 5: //mayo
        case 7: //julio
        case 8: //agosto
        case 10: //octubre
        case 12: //diciembre
            printf("El dia tiene 31 dias");
        break;
        
        case 2: //febrero
            if((year/4)||(year/400)){
                printf("El mes tiene 29 dias");
            }else{
                printf("El mes tiene 28 dias");
            }            
        break;
        
        case 4: //abril
        case 6: //junio
        case 9: //septiembre
        case 11: //noviembre
            printf ("El mes tiene 30 dias");
        break;
    }
    
/* END User code -------------------------------------------------------------*/
    getch();
    return 0;
}
