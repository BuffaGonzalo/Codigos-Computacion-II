#include "graphics.h"
#include "CP865.h"
#include <conio.h>

static unsigned char *libraryDisplay;
static int columns=0;
static int rows=0;

void createDisplay(unsigned char *display, int col, int row){
    libraryDisplay = display;
    columns=col;
    rows=row;
}

void loadLetters(unsigned char fontValue, char backgroundColor, char fontColor, int posX, int posY){ //funcion utilizada para visualizar el display
    unsigned short mask=0x80; //definimos la mascara como una variable local inicializada en 1000 0000
    unsigned short i,j, temp=posX;
    unsigned char k=0,l=0;

    for(i=posY;i<posY+8;i++){ //altura
        gotoxy(5,5);
        posX=temp;
        for(j=posX;j<posX+16;j=j+2){ //largo

            if(j>158){ //utilizado para mostrar el display de manera circular
                temp=posX; //guardamos la posicion de posX para luego volver a la posicion
                posX=(j-posX); //podria ser posX=0;
                j=0;
            }
            if((mask>>k)&font[((fontValue*8)+(l))]){ //desplazamos mask j posiciones, pero no modificamos el valorde mask
                libraryDisplay[i * columns + j] = 254;
                libraryDisplay[i * columns + j+1]=(backgroundColor&0x0F)|(fontColor<<4); //cargamos en el display el color de fondo
            }
            else
                libraryDisplay[i * columns + j] = ' ';
            k++;
        }
        k=0;
        l++;
    }
}

void displaySection(int posX, int posY, int posXmax, int posYmax){ //funcion utilizada para visualizar el display
    int i, j;
    char k;
    k=posX/2;
    for(i=posY;i<posYmax;i++){ //comenzamos en posY para mostrar solamente un sector del display
        for(j=posX;j<posXmax;j=j+2){//comenzamos en posX para mostrar solamente un sector del display
            gotoxy(k+1, i+1);
            textcolor((0xF0&libraryDisplay[i * columns + j+1])>>4); //0xF0&display[i][j+1]
            textbackground(0x0F&libraryDisplay[i * columns + j+1]);
            cprintf("%c", libraryDisplay[i * columns + j]);
            k++; //max valor de k es 8
        }
        k=posX/2;
    }
}

void clearDisplay(int minRow, int minCol, int maxRow, int maxCol, char show){
    textbackground(0);
    int i,j;
    for(i=minRow;i<maxRow;i++){
        for(j=minCol;j<maxCol;j++){
            libraryDisplay[i * columns + j]=' ';
        }
    }
    if(show){
        for(i=minRow;i<maxRow;i++){
            for(j=minCol;j<maxCol;j++){
                cprintf("%c", libraryDisplay[i * columns + j]);
            }
        }
    }
}
