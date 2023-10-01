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
    float FrtNum, ScdNum, TrdNum = 0;
/* END Local variables -------------------------------------------------------*/


/* User code -----------------------------------------------------------------*/
    printf("Ingrese el primer numero\t");
    scanf("%f", &FrtNum);
    printf("Ingrese el segundo numero\t");
    scanf("%f", &ScdNum);
    printf("Ingrese el tercer numero\t");
    scanf("%f", &TrdNum);
        
    if((FrtNum<ScdNum)&&(FrtNum<TrdNum)){
        printf("El numero menor es \t %f",FrtNum);
    }else{
        if((ScdNum<FrtNum)&&(ScdNum<TrdNum)){
            printf("El numero menor es \t %f",ScdNum);
        }else{
            if((TrdNum<FrtNum)&&(TrdNum<ScdNum)){
                printf("El numero menor es \t %.2f",TrdNum);
            }else{
                printf("Entre los numeros ingresados hay repetidos");
            }
        }        
    }
/* END User code -------------------------------------------------------------*/
    getch();
    return 0;
}
