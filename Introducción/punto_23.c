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
#include <ctype.h>
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
    int a, e, i, o, u, opc, valor, salir,contador, vocalesDistintas;
    char text, palabra;
    
    
/* END Local variables -------------------------------------------------------*/


/* User code -----------------------------------------------------------------*/
    while (1){  
        clrscr();       
        printf("Introduzca caracteres y presione Ctrl + D (Unix) o Ctrl + Z (Windows) para finalizar:\n");
        
        //text = getchar( ); //inicializamos la variable text
         //aceramos el contadores al inicio
        contador = 0; 
        a=0; 
        e=0;
        i=0;
        o=0;
        u=0;        
        vocalesDistintas = 0; 
        
        while((text=getchar()) != EOF){ //EOF = ctrl + Z
                switch (text){
                    case 'A':
                    case 'a':
                        if(a == 0){
                            a++;
                            vocalesDistintas++;
                            //printf("\nTEST\n");
                            } 
                            break; 
                    case 'E':
                    case 'e':
                        if(e == 0){
                            e++;
                            vocalesDistintas++;
                            //printf("\nTEST\n");
                            }  
                            break;
                    case 'I':
                    case 'i':
                        if(i == 0){
                            i++;
                            vocalesDistintas++;
                            //printf("\nTEST\n");
                            }  
                            break;
                    case 'O':
                    case 'o':
                        if(o == 0){
                           o++;
                           vocalesDistintas++;
                           //printf("\nTEST\n");
                            }                    
                            break;
                    case 'U':
                    case 'u':
                        if(u == 0){
                            u++;
                            vocalesDistintas++;
                            //printf("\nTEST\n");
                            }
                            break;  
                } //llaves switch
                if ((text == '\t') || (text == '\n') || (text == ' ')){
                    if (vocalesDistintas >= 4){
                        //printf("Palabra con vocales distintas\n");
                        vocalesDistintas = 0;
                        contador++;
                    }                    
                    a = 0;
                    e = 0;
                    i = 0;
                    o = 0;
                    u = 0;
                    vocalesDistintas = 0; //debo acerar esta varable debido a que sino me guarda los valores de las otras palabras
                    //printf("Hay un espacio");
            } //llave if
            
        } //llaves whiles
         
        printf("La cantidad de palabras con mas de 4 vocales son %i\n", contador);
        printf("Presione ESC para salir, cualquier otra tecla para continuar\n");
    
        opc=getch();
        if(opc == 0)
            opc = getch()+1000;
        if(opc == 27)
            break;        
    }
/* END User code -------------------------------------------------------------*/

   return 0;
}
