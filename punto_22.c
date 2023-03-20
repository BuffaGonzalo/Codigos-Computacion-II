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
    int numeros, opc, num, pos, neg, max, min;
     
/* END Local variables -------------------------------------------------------*/


/* User code -----------------------------------------------------------------*/
    while(1){
        //printf("Ingrese un numero\n");
        //scanf("%i", &num);
        max = -2147483648;
        min = 2147483647;
        pos = 0;
        neg = 0;
        do{
            printf("Ingrese un numero\n");
            scanf("%i", &num);
            if(num>max){
                max = num;
                //printf("%i", max);
                }            
            if(num<min)
                min = num;
            if(num>0)
                pos++;
            if(num<0)
                neg++;
            }while(num!=0);
        
        printf("\nRESULTADOS\n");
        if(pos==0)
            printf("No se ingresaron numeros positivos\n");
        if(neg==0)
            printf("No se ingresaron numeros negativos\n");
            
        printf("El numero mayor es %i\n", max);
        printf("El numero menor es %i\n", min);
        
        printf("Presione ESC para salir, cualquier otra tecla para continuar\n");
        
        opc=getch();
        if(opc==0)
            opc = getch() + 1000;
        if(opc==27)
            break;
    }
/* END User code -------------------------------------------------------------*/

   return 0;
}
