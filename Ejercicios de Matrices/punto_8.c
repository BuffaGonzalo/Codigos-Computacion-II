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
char alphabet [26]; //lista de caracteres
int i, opt;

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
        printf("Alfabeto Ingles\n\n");
        
        alphabet[0] = 'a';
        for(i=1;alphabet[i-1] != 'z';i++)
            alphabet[i] = alphabet[i-1]+1;
        alphabet[i]='\0'; //con esto armamos la cadena de caracteres
        printf("%s\r\n\n", alphabet);
        
        alphabet[0] = 'A';
        for(i=1;alphabet[i-1] != 'Z';i++)
            alphabet[i] = alphabet[i-1]+1; 
        alphabet[i]='\0'; //convertimos en cadena de caracteres
        printf("%s\r\n\n", alphabet);
        
        getch();     
    }
/* END User code -------------------------------------------------------------*/

   return 0;
}
