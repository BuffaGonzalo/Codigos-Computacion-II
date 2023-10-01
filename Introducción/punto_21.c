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
#include <math.h>
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
    int opc;
    float a, b, c, d, x, y, raiz1, raiz2;
    //raiz1 es para el signo positiva y raiz2 es para el signo negativo
/* END Local variables -------------------------------------------------------*/


/* User code -----------------------------------------------------------------*/
    while(1){
    
        printf("Calculadora de funciones cuadraticas\n");
        printf("Ingrese el termino cuadratico\n");
        scanf("%f",&a);
        printf("Ingrese el termino lineal\n");
        scanf("%f",&b);
        printf("Ingrese el termino independiente\n");
        scanf("%f", &c);
        
        //calculamos el discriminante
        //para imprimir un double debemos de usar el identificador %lf
        d = (b*b)-4*a*c;
        //en base al discriminante realizamos las siguientes conclusiones
        if(d>0){
            if (a==0 && b==0){
                printf("La ecuacion es degenerada\n");
            }else{
                if(a==0 && b!=0){
                    raiz1 = -c/b;
                    printf("Hay solamente una raiz unica la cual es %f\n", raiz1);
                }else{
                    raiz1 = ((-b + sqrt(d))/(2*a)); //raiz por signo positivo
                    raiz2 = ((-b - sqrt(d))/(2*a)); //raiz por signo negativo
                    clrscr();
                    //printf("Calculadora de funciones cuadraticas\n");
                    //printf("Termino cuadratico es %f\n", a);
                    //printf("Termino lineal es %f\n", b);
                    //printf("Termino independiente es %f\n", c);
                    clrscr();
                    printf("La ecuacion es:  %.1fx%c%.1fx%.1f\n",a,253,b,c);
                    printf("Existen dos raices reales\n");
                    printf("La primera raiz es %f\n", raiz1);
                    printf("La segunda raiz es %f\n", raiz2);       
                }
            } 
        }          
        if(d<0){
            clrscr();
            printf("Existen dos raices complejas\n");
            printf("La primera raiz compleja es %.1f+%.1fi/%.1f\n",-b/2,sqrt(-d)/2,a);
            printf("La segunda raiz compleja es %.1f-%.1fi/%.1f\n",-b/2,sqrt(-d)/2,a);
            
        } 

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
