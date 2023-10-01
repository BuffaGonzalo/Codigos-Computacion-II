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
#include <stdlib.h>
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
int list [25];
int max, maxInd, min, minInd, opt;
unsigned char i;

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
        randomize();
        max = 0;
        min = 0;
        minInd = 0;
        maxInd = 0;
        
        for(i=0;i<25;i++){
            list[i] = random(900); //numeros pseudorandom entre 900        
        }
        
        for(i=0;i<25;i++){
            if(i==0){
                max=list[i];
                min=list[i];
                //break;
            }
            if(list[i]>max){
                max = list[i];
                maxInd = i;
                //break;
            }
            if(list[i]<min){
                min=list[i];
                minInd=i;
                //break;
            }
        }
        
        printf("Programa Numeros Aleatorios - Numeros Mayores & Menores\n");
        printf("El mayor numero es %i y se encuentra en la posicion %i del array\r\n", max, maxInd);
        printf("El menor numero es %i y se encuentra en la posicion %i del array\r\n", min, minInd);     
    getch();
    }
/* END User code -------------------------------------------------------------*/

   return 0;
}
