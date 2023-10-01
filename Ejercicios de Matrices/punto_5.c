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
int students [3][30];
int opt, prom, let;
unsigned char i,j; //definidos como unsigned char para utilizar menos memoria
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
        
        randomize();
        prom = 0;
        let = 65;
        
        for(i=0;i<3;i++){
            for(j=0;j<30;j++){
                students[i][j] = random(7)+3; //random(7)+3 offset                
            }           
        }
        
        printf("LAS NOTAS\n");
        //printf("Aprobaron del curso de Ingeniería");
        for(i=0;i<3;i++){
            for(j=0;j<30;j++){
                printf("%i ", students[i][j]);
                if(students[i][j]>=6)
                    prom++;             
            }      
            printf(" -- Promedio de la Clase %c\t %i\n",let, prom*100/30); 
            let++; 
            prom = 0; 
        }
        
    getch();
    }
/* END User code -------------------------------------------------------------*/

   return 0;
}
