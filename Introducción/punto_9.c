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
    int codigo = 0;
    float precio, cantidad = 0;
/* END Local variables -------------------------------------------------------*/


/* User code -----------------------------------------------------------------*/
    printf("Ingrese el codigo del producto (codigo = 1111)\t");
    scanf("%i", &codigo);
    printf("Ingrese el precio del producto\t");
    scanf("%f", &precio);
    printf("Ingrese la cantidad de unidades - maximo 100 unidades\t");
    scanf("%f", &cantidad);
    
    if (cantidad<1 || cantidad>100 || codigo!=1111){
        return 0;
    }
    
    if (cantidad>=25 && cantidad<=100){
        precio=precio-((20*precio)/100);
    }else{
        if(cantidad>=10 && cantidad<25){
            precio=precio-((10*precio)/100);
        }
    } 
    
    printf("El precio total por %.2f unidades del producto es de %.2f", cantidad, precio*cantidad);
/* END User code -------------------------------------------------------------*/
    getch();
    return 0;
}
