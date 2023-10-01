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
    int sup, inf, dec = 0;
    int i, j, resultado, temp, opt,exp;    
    unsigned int num, mask; 
/* END Local variables -------------------------------------------------------*/


/* User code -----------------------------------------------------------------*/
    while(1){
        clrscr();
        
        printf("Ingrese [ESC] para terminar\n");  

        opt = getch();
        if(opt == 0)
            opt = getch()+1000;
        if(opt == 27)
            break;  
        
        clrscr();
        printf("Ingrese el numero\n");
        scanf("%i", &num);
        //Le pedimos al usuario que ingrese los limites del intervalo
        printf("Ingrese la posicion del bit superior\n");
        scanf("%i", &sup);
        printf("Ingrese la posicion del bit inferior\n");
        scanf("%i", &inf);
        
        //si el usuario ingresa los limites intercambiado, los cambiamos.
        if(inf>sup || sup<inf){
            temp=sup;
            sup=inf;
            inf=temp;
        }
        
        printf("RESULTADOS\n");
        printf("El numero ingresado en decimal es %i\n",num);
        printf("El numero ingresado en hexadecimal es 0X%X\n", num);
        printf("El numero ingresado en binario es ");
        //mask = 1000 0000 0000 0000 0000 0000 0000 0000
        for(mask = 0x80000000; mask!=0; mask>>=1){ //mask = mask>>1
            if(num & mask)
                printf("1");
            else
                printf("0");
        }
        
        //parte para mostrar la seccion entre los bits ingresados por el usuario
        printf("\nEl valor en binario del intervalo entre el bit %i y el bit %i es ",inf,sup);
        
        //lee de izquierda a derecha
        num >>= inf; 
        i = 0;
        dec = 0;
        
        j=sup-inf; //exponente para pasar a decimal
        
        
        for(mask = 0x80000000; mask!=0; mask>>=1){ //mask = mask>>1
            if((i>=(32-(sup-inf+1)))&&i<32){
                //printf("hola");
                if(num & mask){
                    //valores de j correctos
                    printf("1");
                    exp = 0x1; //numero que tomara el valor del binario ingresado
                    exp <<= j;
                    dec += exp;
                    j--;
                }else{
                    printf("0");
                    j--;
                }
            }
            
            i++;
        }
        printf(", en decimal es %i, y en hexadecimal es 0X%X\n", dec,dec);
        getch();
    }
    

/* END User code -------------------------------------------------------------*/

   return 0;
}
