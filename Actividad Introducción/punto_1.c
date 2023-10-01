/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <conio.h>
/* END Includes --------------------------------------------------------------*/

/* define --------------------------------------------------------------------*/
#define ESC 27
#define F6 1064
/* END define ----------------------------------------------------------------*/

int main()
{
/* Local variables -----------------------------------------------------------*/
    int opt, charSinEspacios, charConEspacios, palabras, lineas, temp, controlP, controlL;
    char text;
    char oldText;
/* END Local variables -------------------------------------------------------*/

/* User code -----------------------------------------------------------------*/
    while (1){
        oldText=0; //asignamos el 0 para que marque que no hay filas en caso de salida inmediata
        clrscr();
        printf("Ingrese [ESC] para terminar\n");
        opt = getch();
        if(opt == 0)
            opt = getch()+1000;
        if(opt == ESC)
            break;

        clrscr();
        printf("Introduzca caracteres y presione Ctrl + D (Unix) o Ctrl + Z (Windows) para finalizar:\n");
        lineas = 0;
        palabras = 0;
        charConEspacios = 0;
        charSinEspacios = 0;
        temp = 1;

        controlP = 0; //control de palabras
        controlL = 0; //control de lineas

        while(1){ //EOF = ctrl + Z
            text=getchar();

            if(text != EOF) //no contamos EOF como caracter
                charConEspacios ++; //cantidad de caracteres, teniendo en cuanta que el \n, \t y el espacio son caracteres

            if ((text == '\t') || (text == '\n') || (text == ' ') || (text == EOF)){ //cantidad de palabras
                temp = 1; //significa que no estoy en una palabra
                controlP = 0;
            }

            if ((text != '\t') && (text != '\n') && (text != ' ') && (text != EOF)){ //si se encuentra algun elemento de separacion
                charSinEspacios++; //caracteres sin espacios
                //controlP, controla las palabras para que no se me guarden las palabras como si fueran caracteres
                if (controlP) //utilizado para saber si estoy en una palabra y para que no me cuente cada letra como palabra
                    temp = 1;
                if (!controlP)
                    temp = 0;

            }
//&& (oldText!=' ' || oldText!='\n' || oldText!='\t')
            if(text==EOF && oldText!=0 && oldText!='\n')
                controlL = 1;
//oldText!='/n'
            if(text=='\n') //control de lineas
                controlL = 1;

            if(controlL){
                lineas++;
                controlL = 0;
            }

            if(!temp){
                palabras++;
                controlP = 1;
                temp=1; //significa que estoy en una palabra
            }

            oldText=text; //guardamos el valor antiguo
            if(text==EOF) //utilizado para la salida
                break;
        } //llave while

        rewind(stdin);
        printf("Hay en total %i caracteres con espacios\n", charConEspacios);
        printf("Hay en total %i caracteres sin espacios\n", charSinEspacios);
        printf("Hay en total %i palabras\n", palabras);
        printf("Hay en total %i lineas\n", lineas);
        getch();
    } //llave while(1)
/* END User code -------------------------------------------------------------*/

   return 0;
}
