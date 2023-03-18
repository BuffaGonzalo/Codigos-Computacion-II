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
    unsigned char byte, newByte, bitsAltos, bitsBajos = 0;
    //int mask = 0x0F;
/* END Local variables -------------------------------------------------------*/


/* User code -----------------------------------------------------------------*/
    printf("Ingrese el byte del que desea invertir los bits mas significarivos con los menos significativos desde 0 a 255\t");
    scanf("%hhd", &byte); //registro A contiene la entrada inicial
    
    bitsBajos = byte & 0x0F;
    bitsAltos = byte & 0x0F0;

    newByte = (bitsAltos>>4) | (bitsBajos<<4);
    
    printf("El nuevo byte en hexadecimal es 0x%X\n", newByte);
    printf("El nuevo byte en decimal es %hhd \n", newByte);

    
/* END User code -------------------------------------------------------------*/
    getch();
    return 0;
}
