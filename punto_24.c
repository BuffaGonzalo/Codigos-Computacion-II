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
    int opc, caracteres, palabras, lineas;
    char text;  
/* END Local variables -------------------------------------------------------*/


/* User code -----------------------------------------------------------------*/
    while (1){    
        clrscr();     
        printf("Introduzca caracteres y presione Ctrl + D (Unix) o Ctrl + Z (Windows) para finalizar:\n"); 
        lineas = 0;
        palabras = 0;
        caracteres = 0;
        while((text=getchar())!=EOF){ //EOF = ctrl + Z
                caracteres ++; //cantidad de caracteres, teniendo en cuanta que el \n, \t y el espacio son caracteres
                if ((text == '\t') || (text == '\n') || (text == ' ')){ //cantidad de palabras
                        palabras++;
                    }             
                if(text == '\n'){ //la cantidad de lineas se define mediante el \n
                    lineas++;
                }                 
            } //llave while 
                   
        printf("Hay en total %i caracteres\n", caracteres);
        printf("Hay en total %i palabras\n", palabras);        
        printf("Hay en total %i lineas\n", lineas);
        printf("Presione ESC para salir, cualquier otra tecla para continuar\n");
        
        opc=getch();
        if(opc == 0)
            opc = getch()+1000;
        if(opc == 27)
            break;  
               
        } //llave while(1)   
/* END User code -------------------------------------------------------------*/

   return 0;
}
