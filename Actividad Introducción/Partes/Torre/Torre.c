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
    int i, j, m, num, fila, columnaNum, columna, opt;
/* END Local variables -------------------------------------------------------*/


/* User code -----------------------------------------------------------------*/
    while(1){ 
    
        printf("Ingrese [ESC] para terminar\n");  
        
        //printf("%i", &opt);
        opt = getch();
        if(opt == 0)
            opt = getch()+1000;
        if(opt == 27)
            break;      
          
        clrscr();
    
        printf("Programa de Ajedrez solo con Alfil\n");
        printf("Ingrese la posicion en la que quiere al alfil\n");
        printf("Ingrese la columna\n");
        printf("Teniendo en cuenta que A=1 B=2 C=3 D=4 E=5 F=6 G=7 H=8\n");  
        scanf ("%i", &columna);      
        printf("Ingrese la fila - numero\n");
        scanf ("%i", &fila);
        
        
        printf("\nTablero de Ajedrez - Torre\n");    
        num = 1;
        printf("  A  B  C  D  E  F  G  H\n");
        
        //J = Columna I = Linea
        for(i=1;i<=8;i++){
            printf("%i", num);
            for(j=1;j<=8;j++){
                    printf("[");
                    if(i==fila && j==columna){
                        printf("+"); //funciona
                    }else{ //posibles movimientos
                        if((j==columna)||(i==fila)){ 
                            printf("*");
                        }else{
                            printf(" "); //funciona
                        }                    
                    }
                    printf("]");
                } 
            printf("%i", num);
            printf("\n");
            num++;                   
        }   
        printf("  A  B  C  D  E  F  G  H\n");
    }
    
/* END User code -------------------------------------------------------------*/
   return 0;
}
