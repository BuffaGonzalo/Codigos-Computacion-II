#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <conio.h>
#include "editor.h"

#define ENTER       13
#define SPACE       32
#define DEL         1083
#define LEFT        1075
#define RIGHT       1077
#define BACKSPACE   8

static unsigned short j, k;
static int i;
static char *Editor;

void editor(unsigned short bufferLenth, unsigned short seenBuffer, char *eVector, int opt, int posX, int posY, unsigned char bkgColor, unsigned char ltrColor, char cursorBlink){ /**< seenBuffer cantidad de caracteres máximos mostrados en un momento */
    Editor = (char*)malloc(bufferLenth);

    if(Editor==NULL){
        cprintf("Espacio de memoria insuficiente");
    }

    switch(opt){
            case ENTER:
                for(i=strlen(Editor);i>=0;i--) //limpiamos el editor
                    Editor[i]='\0';
                j=i=k=0;
            break;
            case DEL: //borramos el caracter a la derecha del cursor
                for(i=j;i<strlen(Editor);i++)
                    Editor[i]=Editor[i+1];
            break;
            case BACKSPACE: //borramos el caracter a la izquierda del cursor
                for(i=j-1;i<strlen(Editor);i++)
                    Editor[i]=Editor[i+1];
                if((k>0) && (j==k)) //controlamos el valor de k para mostrar
                    k--;
                if(j>0)
                    j--;
            break;
            case LEFT:
                if((k>0) && (j==k))
                    k--;
                if(j>0)
                    j--;
            break;
            case RIGHT:
                if(k<seenBuffer && Editor[j]!='\0')
                    k++;
                if(j<bufferLenth && j<strlen(Editor))
                    j++;
            break;
            default:
                if((isalnum(opt)!=0 || opt==' ' || opt=='(' || opt==')' || opt==',')&&j<bufferLenth){ //isascii devuelve 0 si el caracter no es ascii
                        if(Editor[j]!=NULL){ //usado cuando queremos cargar caracteres en una posicion donde ya habia
                            for(i=bufferLenth;i>=j;i--){     //strlen(Editor)
                                Editor[i]=Editor[i-1];
                            }
                            Editor[j]=opt;
                            j++;
                        } else{
                            Editor[j]=opt;
                            j++;
                        }
                    if(k<seenBuffer)//movemos el cursor
                        k++;
                }
            break;
        }

        textbackground(BLACK);

            gotoxy(posX,posY);
            if(j<seenBuffer){
                for(i=0;i<seenBuffer;i++){
                    if((Editor[i])!='\0'){
                        if(i==j && cursorBlink){
                            textbackground(ltrColor); //5
                        } else
                            textbackground(bkgColor); //2
                        textcolor(7);
                        cprintf("%c", Editor[i]);
                    }
                    else{
                        if(i==j && cursorBlink){
                            textbackground(ltrColor);
                            textcolor(ltrColor);

                        }else{
                            textbackground(bkgColor);
                            textcolor(bkgColor);
                        }
                        cprintf("G");
                    }
                }
            }
            else{ //muestra los datos cuando tenemos mas de 16 caracteres
                for(i=j-seenBuffer;i<j;i++){
                    if(Editor[i]!='\0'){
                        if(i==j-1 && cursorBlink){
                            textbackground(ltrColor);
                        } else
                            textbackground(bkgColor);
                        textcolor(7);
                        cprintf("%c", Editor[i]);
                    }
                }
        }
        textbackground(BLACK);

        gotoxy(posX-2,posY);
        if(Editor[j-(seenBuffer+1)]!='\0' && j>seenBuffer) //mostramos flechas izquierdas, -17 porque se tiene en cuenta la posicion 0
            cprintf("%c", 174);
        else
            cprintf(" ");

        gotoxy(posX+seenBuffer+1,posY);
        if(Editor[seenBuffer]!='\0' && (Editor[j])!='\0') //mostramos flechas derechas
            cprintf("%c\n", 175);
        else
            cprintf(" \n");

        for(i=0;i<bufferLenth;i++){ //utilizado par devolver los datos al main
            *(eVector+i)=Editor[i];
        }

        free(Editor);
}

void parser(unsigned short bufferLenth, char *eVector){
    int temp[bufferLenth];
    int i, j=0;

    for(i=0;i<bufferLenth;i++)
        temp[i]=0;

    for( i=0;i<bufferLenth;i++){
        if(*(eVector+i) != ' '){
            temp[j++]=*(eVector+i);
        }
    }

    for(int i=0;i<bufferLenth;i++){
        *(eVector+i)=temp[i];
    }
}

