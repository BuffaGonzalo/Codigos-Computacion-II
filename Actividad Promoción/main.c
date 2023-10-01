/*! \mainpage THE MAZE - ACTIVIDAD PROMOCION
 * \date Fecha de Inicio: 12/06/2023
 * \author Autor: Gonzalo Martin Buffa
 *
 * \section General
 * Programa encargado de generar un laberintos aleatorios (importarlos y exportarlos), ademas permite encontrar la solucion al laberinto. Tambien se puede manejar el autito para poder dibujar algo.
 *
 * \section Observaciones
 * Las funciones que presento son las de importar un archivo .bpm, determinar el punto de inicio y final, tambien la de limpiar la pantalla. Ademas tambien la funcion del laberinto la cual tiene algunas fallas, en esta funcion estuve varios dias pero no pude solucionar los problemas.
 *
 * \section Cambios
 *
 * |    Fecha   | Descripcion                                                                                       |
 * |:----------:|:--------------------------------------------------------------------------------------------------|
 * | 12/06/2023 | Creacion del documento                                                                            |
 * | 12/06/2023 | Trabajo libreria del editor                                                                       |
 * | 16/06/2023 | Avance en la libreria editor                                                                      |
 * | 21/06/2023 | Avance en la libreria editor                                                                      |
 * | 22/06/2023 | Finalizacion en la libreria editor                                                                |
 * | 24/06/2023 | Inicio Trabajo Laberinto                                                                          |
 * | 25/06/2023 | Inicio Trabajo Laberinto                                                                          |
 * | 26/06/2023 | Avance Trabajo Laberinto                                                                          |
 * | 27/06/2023 | Avance Trabajo Laberinto (cambio de metodo) - cambio de metodo                                    |
 * | 28/06/2023 | Trabajo en el Laberinto  (nuevo metodo)                                                           |
 * | 29/06/2023 | Trabajo en el Laberinto                                                                           |
 * | 30/06/2023 | Trabajo en el Laberinto                                                                           |
 * | 01/07/2023 | Dando el formato correcto a los datos del editor                                                  |
 * | 01/07/2023 | Trabajando con los comandos, munu y librerias                                                     |
 * | 02/07/2023 | Comienzo y finalización de la impotacion de un archivo .BMP                                       |
 * | 03/07/2023 | Organizando las funciones en los comandos y trabajo en el laberinto                               |
 * | 04/07/2023 | Trabajo en funciones de posicion inicial y final                                                  |
 * | 09/07/2023 | Trabajo rotar izquierda y rotar derecha                                                           |
 * | 10/07/2023 | Trabajo funcion adelante                                                                          |
 * | 11/07/2023 | Trabajo funcion atras y settime                                                                   |
 * | 12/07/2023 | Arreglo en algunas de las funciones                                                               |
 * | 13/07/2023 | Funciones brushon y brushoff                                                                      |
 * | 13/07/2023 | Arreglo de errores                                                                                |
 * | 13/07/2023 | Arreglo de errores                                                                                |


 * | 18/07/2023 | Comienzo de Trabajo en la funcion steptime() y resetmapa()                                        |
 * | 19/07/2023 | Arreglo de errores                                                                                |


 * | 21/07/2023 | Inicio  exportar mapa - buscando informacion sobre archivo .bmp                                   |
 * | 22/07/2023 | Avance exportar mapa - completando cabeceras                                                      |
 * | 23/07/2023 | Trabajo en funcion exportar mapa                                                                  |
 * | 24/07/2023 | Comienzo de Trabajo resolucion del laberinto - Algoritmo A*                                       |
 * | 25/07/2023 | Trabajo en la resolucion del laberinto                                                            |
 * | 26/07/2023 | Trabajo en la resolucion del laberinto                                                            |
 * | 27/07/2023 | Trabajo en resolucion del laberinto - trabajo con las listas                                      |
 * | 28/07/2023 | Trabajo en la resolucion del laberinto y solucion de error del savemapa()                         |
 * | 29/07/2023 | Trabajo en la resolucion del laberinto                                                            |
 * | 30/07/2023 | Finalizacion de la solucion del laberinto, añadiendo steptime a las funciones adelante y atras    |
 */

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <time.h>
#include <math.h>

#include <limits.h>
#include <stdbool.h>

//librerias del usuario
#include "graphics.h"
#include "editor.h"
#include "ticker.h"
/* END Includes --------------------------------------------------------------*/


/* typedef -------------------------------------------------------------------*/
typedef struct{
    unsigned char cursorBlink:1; /**< cursorBlink: Utilizado para determinar el parpadeo del cursor del editor*/
    unsigned char isError:1; /**< isError: Utilizado para determinar si el comando ingresado es correcto o no, en caso de no ser correcto imprime un mensaje */
    unsigned char firExe:1; /**< firExe: Utilizado para controlar la primera ejecucion del programa */
    unsigned char isCarMap:1; /**< isCarMap: Utilizado para determianr si hay o no mapa generado o auto en el mapa, para determinar la posicion correcta en donde colocar el auto y en la direccion correcta*/
    unsigned char isDef:1; /**< isDef: Usado para ejecutar comandos solo si se ingreso la posicion de inicio o si se limpio a pantalla*/
    unsigned char timeConf:1; /**< timeConf: Usado para conectar el timeStart de la libreria ticker*/
    unsigned char exeFunc:1; /**< exeFunc: Ejecutamos la funcion*/
    unsigned char var8:1; /**< var8: Sin usar */
} sBitField; /**< sBitField: Campo de bits utilizado como control*/


typedef struct {
    int row;
    int col;
} sPosition; /**< sPosition: Estructura utilizada para almacenar todas las posiciones recorridas durante la creacion del laberinto*/

/** \brief
 *
 * \param[in] pos: Posicion del comando, utilizada para la ejecucion
 * \param[in] *name: Nombre del comando, utilizado para comparar con el valor ingresado en el editor
 * \param[in] param: Cantidad de parametros de cada comando
 * \return
 *
 */

typedef struct{
    unsigned char pos;
    const char *name;
    char param;
} sCommand; /**< sCommand: Estructura utilizada para guardar los diferentes modos*/

//usada para exportar la imagen
typedef struct __attribute__((packed, aligned(1))){
    char ID[2]; //BM para archivos .bmp
    int sizeBMP; //tamaño total del bmp
    short reserved0;
    short reserved1;
    int dataOffset; //lugar en donde comienzan los datos
} sBMPHeader;

//Usada para exportar la imagen
typedef struct __attribute__((packed, aligned(1))){
    int bytesDIBHeader; //Tamaño de la cabecera
    int widthPixels; // anchura de los pixeles
    int heightPixels; //altura de los pixels
    short planeColors; //valor igual a 1
    short bpp; //bits per pixel - 24 para imagenes de 24bits
    int compresion; //metodo de compresion - valor de 0 para no comprimidas
    int imageSize; //Tamaño de los datos (height*columns*bytes)
    int xResolution;
    int yResolution;
    int colors; //colors used - tiene el valor de 0 en imagen de 24 bits
    int iColors; //important colors - tiene el valor de 0 en la imagen de 24 bits
} sBIDHeader;

//almacena los datos del automovil
typedef struct{
    char direction; /**< direction: Utilizado para saber hacia donde apunta en el siguiente orden arriba,abajo,izquierda,derecha respectivamente*/
    char pathColor; /**< pathColor: Color del camino*/
    unsigned char posX; /**< posX: Casillas actual en X*/
    unsigned char posY; /**< posY: Casillas actual en Y */
} sCar;

//usado en el metodo de busqueda A*
// Structure representing a node in the grid
typedef struct node {
    int x, y;               // Coordinates of the node
    int g, h, f;            // Cost and heuristic values for A* algorithm
    struct node* next;    // Parent node in the path
} sNode;

typedef struct path{
    int x, y;
} sPath;

//typedef struct myCommands{
//    char comName[20];
//    char firstParamChar[20], secondParamChar[20];
//    int firstParamInt, secondParamInt;
//}myCommands;

//// Structure representing a node in the priority queue
//typedef struct PriorityQueue {
//    Node* node;                 // Node in the priority queue
//    struct PriorityQueue* next; // Pointer to the next node in the queue
//} PriorityQueue;



/* END typedef ---------------------------------------------------------------*/


/* define --------------------------------------------------------------------*/
#define DEL         1083
#define F1          1059
#define F2          1060
#define F3          1061
#define LEFT        1075
#define RIGHT       1077
#define BACKSPACE   8
#define ESC         27
#define ENTER       13
/* END define ----------------------------------------------------------------*/


/* Function prototypes -------------------------------------------------------*/
int manhattanDistance(int startX, int startY, int endX, int endY);
int isValidMove(int posX, int posY);

void startPoint();
void loadMapa();
void saveMapa();
void maze();/**< maze: funcion tipo void la cual genera el laberinto aleatorio*/
void solve();
void move();
void adelante();
void atras();
void girarIzquierda();
void girarDerecha();
void brushon();
void brushoff();
void clrscr();
void loadsequence();
void gosequence();



/* END Function prototypes ---------------------------------------------------*/


/* Global variables ----------------------------------------------------------*/
short opt; /**< Variable donde se almacenan los valoren ingresados */
unsigned char display[40][160]; /**< Matriz del display en la cual se guardan los caracteres mostrados*/
static clock_t currentTime, lastTime; /**< Variable utilizada para el parpadeo del cursor */
static char mainEditor[1024]; /**< Vector utilizado en el editor */
unsigned char comPos=0;
char comName[20], paramAmount;
char *paramStart, *paramEnd; //CommandName
int comLength;


char firstParamChar[20], secondParamChar[20];
int firstParamInt, secondParamInt;
int oldMazeRows=0, oldMazeCols=0;
unsigned char startX, startY, endX, endY;


char command[50][20] = {{NULL}};//usado en secuencia

int forwardSpeed, backwardSpeed, steptime=500; //usado para guardar el tiempo de la secuencia

int cells, cont=0; //usado par ir hacia delante y atras
int pathCont; //usado en el goMapa()
sPath path[1000]; //usado para el goMapa()
//int front; //utilizada para determinar el frente del vehiculo
sBitField bitField; /**< Campo de bits utilizado como banderas*/
sCar carData; /**< Utilizado para determinar los datos del auto*/
sBMPHeader bmpHeader; /**< Utilizado para trabajar con el archivo BMP*/
sBIDHeader bidHeader; /**< Utilizado para trabajar con el archivo BMP*/


const sCommand commands[21]={{1,"setinicio",2},{2,"setfinal",2},{3,"resetmapa",0},{4,"loadmapa",1},{5,"savemapa",1},{6,"genmapa",2},{7,"resolver",0},{8,"gomapa",0}, {9,"steptime",1},
    {10,"clrscr",0},{11,"adelante",1},{12,"atras",1},{13,"girarizquierda",1},{14,"girarderecha",1},{15,"repetir",1},{16,"brushon",1},{17,"brushoff",0},{18,"loadsecuencia",1},
    {19,"gosecuencia",1},{20,"resetsecuencia",0},{21,"stop",0},};

/* END Global variables ------------------------------------------------------*/

/* Function prototypes user code ----------------------------------------------*/
int manhattanDistance(int startY, int startX, int endY, int endX) {
    return abs(endY - startY) + abs(endX - startX); //corroborar
}

int isValidMove(int posX, int posY){
    //posX == Cantidad de columnas
    //posY == Cantidad de filas
    if(posY<oldMazeRows && posY>=0 && posX<oldMazeCols && posX>=0 && display[posY][posX*2]!=1)
        return 1;
    return 0;
}

void startPoint() {
    int i,j,temp;
    int rows=40;
    int columns=80;
    int x=firstParamInt;
    int y=secondParamInt;

    textbackground(4); //ROJO
    textcolor(7); //BLANCO
    gotoxy(10,45);

    if(x>=40 && y>=80){
        cprintf("ERROR FILAS Y COLUMNAS            ");
        bitField.isError=1;
        return;
    }
    if(x>=39){
        cprintf("ERROR FILAS                       ");
        bitField.isError=1;
        return;
    }
    if(y>=79){
        cprintf("ERROR COLUMNAS                    ");
        bitField.isError=1;
        return;
    }

    if(display[x][2*y]==1 || display[x+1][2*y]==1 || display[x][2*(y+1)]==1 || display[x+1][2*(y+1)]==1){
        cprintf("POSICION OCUPADA                  ");
        bitField.isError=1;
        return;
    }

    carData.direction=rand()%4; //generamos un numero aleatorio para orientar el auto al en el centro del tablero
    //CORROBORAMOS LAS ESQUINAS
    if(x==0 && y==0)//esquina superior
        carData.direction=(rand()%2)+1; //generamos con rand un valor entre 0 y 1, luego generamos un impar con ellos
    else if(x==0 && y==columns-2)
        carData.direction=(rand()%2)+2;
    else if(x==rows-2&& y==0)
        carData.direction=rand()%2;
    else if(x==rows-2 && y==columns-2)
        carData.direction=(rand()%2)*3;

    //CORROBORAMOS LOS BORDES
    else if(y==0) //izquiera mapa
        while(carData.direction==3)
            carData.direction=rand()%4;
    else if(x==rows-2) //abajo mapa
        while(carData.direction==2)
            carData.direction=rand()%4;
    else if(y==columns-2) //arriba mapa
        while(carData.direction==1)
            carData.direction=rand()%4;
    else if(x==0) //arriba mapa
        while(carData.direction==0)
            carData.direction=rand()%4;

    switch(carData.direction){
        case 0: //UP
            temp=6;
            for(i=0;i<2;i++){
                for(j=0;j<2;j++){
                    display[x+i][2*(y+j)] = 3;
                    display[x+i][(2*(y+j))+ 1] = temp;
                }
                temp=4;
            }
        break;
        case 1: //RIGHT
            temp=4;
            for(j=0;j<2;j++){
                for(i=0;i<2;i++){
                    display[x+i][2*(y+j)] = 3;
                    display[x+i][(2*(y+j))+ 1] = temp;
                }
                temp=6;
            }

        break;
        case 2: //DOWN
            temp=4;
            for(i=0;i<2;i++){
                for(j=0;j<2;j++){
                    display[x+i][2*(y+j)] = 3;
                    display[x+i][(2*(y+j))+ 1] = temp;
                }
                temp=6;
            }
        break;
        case 3: //LEFT
            temp=6;
            for(j=0;j<2;j++){
                for(i=0;i<2;i++){
                    display[x+i][2*(y+j)] = 3;
                    display[x+i][(2*(y+j))+ 1] = temp;
                }
                temp=4;
            }
        break;
    }

    carData.posX=x;
    startX=y;
    carData.posY=y;
    startY=x;
    bitField.isCarMap=1; //Hay un auto en la pantalla
    displaySection(2*y,x,2*(y+2),x+2);//mostrar el auto
}

void endPoint() {
    textbackground(4); //ROJO
    textcolor(7); //BLANCO
    gotoxy(10,45);
    int x=firstParamInt;
    int y=secondParamInt;

    if(x>40 && y>80){
        cprintf("ERROR FILAS Y COLUMNAS            ");
        bitField.isError=1;
        return;
    }
    if(x>40){
        cprintf("ERROR FILAS                       ");
        bitField.isError=1;
        return;
    }
    if(y>80){
        cprintf("ERROR COLUMNAS                    ");
        bitField.isError=1;
        return;
    }

    if(display[x][2*y]==1 || display[x+1][2*y]==1 || display[x][2*(y+1)]==1 || display[x+1][2*(y+1)]==1){
        cprintf("POSICION OCUPADA                  ");
        bitField.isError=1;
        return;
    }


    endY=x;
    endX=y;
}

void loadMapa(){
    int databyte=0,rows=0,columns=0;
    char header[54]; //cabecera compuesta por 54 chars

    strcat(firstParamChar,".bmp"); //añadimos .bmp para que el usuario no tenga que añadirlo

    FILE* file = fopen(firstParamChar, "rb");
    fread(header,sizeof(char),54,file);

    databyte = header[10]|(header[11] << 8)|(header[12] << 16)|(header[13] << 24);
    rows = header[22]|(header[23] << 8)|(header[24] << 16)|(header[25] << 24);
    columns = header[18]|(header[19] << 8)|(header[20] << 16)|(header[21] << 24);

    unsigned char image[(columns*3)*rows];

    fseek(file,databyte, SEEK_SET);

    fread(image,sizeof(char),(columns*3)*rows,file);

    gotoxy(1,1);

    for (int i=rows-1;i>=0;i--) {
        for (int j=0;j<columns;j++) {
            if(image[i * columns*3 + j*3] & 0xff)
                textbackground(0);
            else
                textbackground(7);
            cprintf(" ");
        }
    }
    fclose(file);
}

void saveMapa(){
    int i,j;
    unsigned char white[3] = {255,255,255};
    unsigned char black[3] = {0,0,0};
    unsigned int imageSize = oldMazeRows*oldMazeCols*3;
    unsigned int padding = oldMazeCols*(oldMazeRows%4);

    //concatenamos esta sentencia para no tener que ingresar el .bmp
    strcat(firstParamChar,".bmp");
    // Crear un archivo BMP.

    FILE *file = fopen(firstParamChar, "wb"); //creamos un archivo con el nombre ingresado

    gotoxy(10,45);
    textbackground(RED);
    textcolor(WHITE);

    if (file == NULL) {
        cprintf("ERROR CREAR ARCHIVO     \n");
        return;
    } else {
        cprintf("ARCHIVO CREADO          \n");
    }

    //completamos los datos del header
    bmpHeader.ID[0]='B';
    bmpHeader.ID[1]='M';
    bmpHeader.sizeBMP =  sizeof(bmpHeader) + sizeof(bidHeader) + oldMazeCols*oldMazeRows*3 + (oldMazeCols*oldMazeRows%4); //tamaño es igual a 54 bytes + tamaño de los datos
    bmpHeader.reserved0 = 0;
    bmpHeader.reserved1 = 0;
    bmpHeader.dataOffset = sizeof(bmpHeader) + sizeof(bidHeader); //seccion a partir de la cual comienzan los datos

    //la cabecera bid brinda la informacion de como debe de ser leido el archivo .bmp
    bidHeader.bytesDIBHeader=40; //tamaño de la cabecera
    bidHeader.widthPixels=oldMazeCols;
    bidHeader.heightPixels=oldMazeRows;
    bidHeader.planeColors=1; //debe de ser si o si 1
    bidHeader.bpp=24; //debido a que es una imagen de 24 bits
    bidHeader.compresion=0;
    bidHeader.imageSize=imageSize+padding;
    bidHeader.xResolution=2835; // calidad de la imagen - pixeles por metro
    bidHeader.yResolution=2835; // calidad de la imagen - pixeles por metro
    bidHeader.colors=0;
    bidHeader.iColors=0;

    fwrite(&bmpHeader,sizeof(bmpHeader),1,file);
    fwrite(&bidHeader,sizeof(bidHeader),1,file);

    for(i=oldMazeRows-1;i>=0;i--){
        for(j=0;j<oldMazeCols;j++){ //rows
            if(display[i][j*2]==1) //no se puede intercambiar
                fwrite(white,sizeof(char),3,file);
            else
                fwrite(black,sizeof(char),3,file);
        }
        fwrite(white,sizeof(char),oldMazeRows%4,file); //completamos la fila para que sea multiplo de 4
    }

    gotoxy(10,45);
    textbackground(RED);
    textcolor(WHITE);
    cprintf("DATOS CARGADOS     \n");


    fclose(file);
}

void maze(){ // int density
    int **matrix;
    float density = 1;
    int fWalls = density * 8;
    int i, j;
    int rows=firstParamInt;
    int columns=secondParamInt;

    textbackground(4); //ROJO
    textcolor(7); //BLANCO
    gotoxy(10,45);

    if((columns>=79 || columns<15) && (rows>=39 || rows<15)){
        cprintf("ERROR FILAS Y COLUMNAS              ");
        bitField.isError=1;
        return;
    }

    if(columns>=79 || columns<15){
        cprintf("ERROR COLUMNAS                     ");
        bitField.isError=1;
        return;
    }
    if(rows>=39 || rows<15){
        cprintf("ERROR FILAS                        ");
        bitField.isError=1;
        return;
    }

    //si el numero de filas y columnsa no es multiplo de 3, lo convertimos a uno que lo sea pero que sea inferior
    if(rows%3!=0){
        int temp = rows%3;
        rows=rows-temp;
    }
    if(columns%3!=0){
        int temp = columns%3;
        columns=columns-temp;
    }

    //aumentamos en uno para que entre el borde del mapa
    ++rows;
    ++columns;

    density = rows*columns*density / 4;

    //damos el tamaño a la matriz de forma dinamica
    matrix = malloc(sizeof(int*)*(rows));
    for(i=0;i<rows;i++){
        matrix[i] = malloc(sizeof(int)*(columns));
    }


    //imprimimos el borde del laberinto
    for ( i = 0; i < rows; i++) {
        for ( j = 0; j < columns; j++) {
            if (i == 0 || j == 0 || i == rows-1 || j == columns-1){
                matrix[i][j] = 1;
            }
            else {
                matrix[i][j] = 0;
            }
        }
    }

    //generamos el laberinto
    for ( i = 0; i < density; i++) {

        int x = rand() % (columns - 7) + 3; // 2 18
        x = (x / 3) * 3;
        int y = rand()% (rows - 7) + 3;
        y = (y / 3) * 3;


        matrix[y][x] = 1;
        for (j = 0; j < fWalls; j++) {
            int mx[4] = { x,  x,  x + 3, x - 3 };
            int my[4] = { y + 3,y - 3, y ,  y };
            int r = rand() % 4;
            if (matrix[my[r]][mx[r]] == 0) {
                matrix[my[r]][mx[r]] = 1;
                matrix[my[r]+(y-my[r])*1/3][mx[r]+(x-mx[r])*1/3] = 1;
                matrix[my[r]+(y-my[r])*2/3][mx[r]+(x-mx[r])*2/3] = 1;
            }
        }
    }

    //imprimimos el laberinto generado
	for(i=0;i<rows;i++){
        for(j=0;j<columns;j++){
            if(matrix[i][j]==1)
                display[i][(j*2)+1]=7;
            else
                display[i][(j*2)+1]=0;
            display[i][j*2]=matrix[i][j];
        }
	}

	displaySection(0,0,columns*2,rows);
    bitField.isCarMap=1; //tenemos mapa en pantalla

    //guadamos el valor del utlimo laberinto para limpiar la pantalla
    oldMazeCols=columns;
    oldMazeRows=rows;


    free(matrix); //liberamos la memoria asignada dinamicamente
}

void solve(){
    int i, j=0;
    int nextX, nextY, minF, minInd;
    sNode* openList[40*80] = {NULL}; //utilizado para guardar los nodos evaluados
    int closedList[40][80] = {{0}}; //utilizado para guardar los nodos visitados
    //int path[1000]={0};

    int move[4][2] = {
        {-1,0},     //Arriba
        {1, 0},     //Abajo
        {0,-1},     //Izquierda
        {0, 1}      //Derecha
    };

    //guadamos el elemento de inicio
    sNode* firstNode = (sNode*)malloc(sizeof(sNode));
    firstNode->x=startX;
    firstNode->y=startY;
    firstNode->g=0; //costo para llegar al inicio desde el punto (startX, startY)
    firstNode->h=manhattanDistance(startY,startX,endY,endX);
    firstNode->f=firstNode->g+firstNode->h;
    firstNode->next=NULL;
    openList[startY*oldMazeCols+startX] = firstNode;

    while(1){
        minF=INT_MAX; //INT_MAX=2147483647
        minInd=-1;

        for(i=0;i<oldMazeCols*oldMazeRows;i++){
            sNode* actualNode = openList[i];
            if(actualNode != NULL && actualNode->f < minF){
                minF=actualNode->f;
                minInd = i;
            }
        }

        //verificamos si encontramos solucion
        if(minInd==-1){
            textbackground(4); //ROJO
            textcolor(7); //BLANCO
            gotoxy(10,45);
            cprintf("NO HAY SOLUCION            ");
            bitField.isError=1;
            return;
        }

        sNode* actualNode = openList[minInd];
        openList[minInd] = NULL;
        closedList[actualNode->y][actualNode->x] = 1;

        //verificacion si llegas al nodo final
        if(actualNode->y == endY && actualNode->x ==endX){
            sNode* node=actualNode;
            while(node != NULL){
                j++;
                display[node->y][(node->x)*2]=2;
                //display[node->y][((node->x)*2)+1]=GREEN<<4;
                node = node->next;
            }
            pathCont=j-1;
            //displaySection(0,0,oldMazeCols,oldMazeRows);
                gotoxy(1,1);
                for(i=0;i<oldMazeRows;i++){
                    for(j=0;j<oldMazeCols;j++){

                        if(display[i][j*2]==1){
                            textbackground(7);
                            textcolor(7);
                            cprintf(" ");
                        }
                        if(display[i][j*2]==0){
                            textbackground(0);
                            textcolor(0);
                            cprintf(" ");
                        }
                        if(display[i][j*2]==2){
                            textbackground(3);
                            textcolor(3);
                            cprintf(" ");
                        }
                        if(display[i][j*2]==3){
                            textbackground(4);
                            textcolor(4);
                            cprintf(" ");
                        }

                    }
                    printf("\n");
                }
                free(firstNode);
            return;
        }

        //si no llegas al nodo final
        for(i=0;i<4;i++){
            //sumamos uno en cada posicion con el fin de encontrar la nueva posicion
            nextX=actualNode->x+move[i][0]; //+dx[i];
            nextY=actualNode->y+move[i][1]; //dy[i];

            if(isValidMove(nextX,nextY)&&isValidMove(nextX+1,nextY+1)&&isValidMove(nextX,nextY+1)&&isValidMove(nextX+1,nextY)){
                if(closedList[nextY][nextX]){ //closedList[nextY][nextX]==1
                    continue; //salteamos el elemento
                }

                sNode* nextNode = (sNode*)malloc(sizeof(sNode));
                nextNode->x=nextX;
                nextNode->y=nextY;
                nextNode->g=actualNode->g+1;
                nextNode->h=manhattanDistance(nextY,nextX,endY,endX);
                nextNode->f=firstNode->g+firstNode->h;
                nextNode->next=actualNode;

                if(openList[nextY*oldMazeCols+nextX] != NULL){
                    sNode* existNode = openList[nextY * oldMazeCols + nextX];
                    //comparamos los valores de f, y si es menor lo cambiamos
                    if(nextNode->f < existNode->f){
                        //solamente cambiamos los valores de g,h y f porque las posiciones son las mismas
                        existNode->g=nextNode->g;
                        existNode->h=nextNode->h;
                        existNode->f=nextNode->f;
                        existNode->next = nextNode->next;
                    } else{
                        free(nextNode);
                    }

                } else {
                    openList[nextY*oldMazeCols+nextX] = nextNode;
                    }
                }
            }
        }
    }

void loadSequence(){
    int i,j=0;
    int cont=0;

    strcat(firstParamChar,".txt");
    FILE *file = fopen(firstParamChar,"r");

    textbackground(4); //ROJO
    textcolor(7); //BLANCO
    gotoxy(10,45);
    if(file!=NULL){
        cprintf("SECUENCIA CARGADA     ");
    } else{
        cprintf("ERROR                 ");
    }

    //buscar el \n que es el separador de comandos
    gotoxy(1,1);
    while(fgets(&command[1][j],sizeof(command),file)!=NULL){ //mientras que no sea NULL
        //printf("%s", &command[50][j]);
        puts(&command[1][j]);
        j++;
    }
}

void goSequence(){
    int i,j,k;
    int mode=0;

    mode=0;

    if(!strcmp(firstParamChar,"go")){ //strcpy es igual a 0 asi que lo negamos
        gotoxy(10,45);
        printf("GO");
        mode=0;
    }
    if(!strcmp(firstParamChar,"step")){
        gotoxy(10,45);
        printf("STEP");
        mode=1;
    }


    switch(mode){
//    case 0:
//        for(k=0;k<20;k++){
//
//            comLength = strcspn(&command[1][k],"("); //stringLenth
//            strncpy(comName, &command[1][k], comLength); //copiamos la cadena hasta el (, por lo tanto solo tendriamos los caracteres
//
//            for(i=0;i<sizeof(comName);i++) //convertimos los posibles caracteres que esten en mayusculas a minusculas
//                comName[i]=tolower(comName[i]);
//
//            //CONTROLAMOS LOS PARAMETROS QUE SE INGRESAN
//            paramStart=strchr(&command[1][k],'(');
//            paramEnd=strchr(&command[1][k],')');
//
//            if (paramStart != NULL && paramEnd != NULL) {
//                paramStart++;
//                char* comma = strchr(paramStart, ',');
//                if (comma != NULL && comma < paramEnd) {
//                    paramAmount=2;
//                } else {
//                    paramAmount=1;
//                }
//            } else {
//                paramAmount=0;
//            }
//
//            switch(paramAmount){
//                case 1: //Solo un parametro buscamos ()
//                    paramStart=strchr(&command[1][k],'(');
//                    paramEnd=strchr(&command[1][k],')');
//
//                    //paramStart++;
//                    strncpy(firstParamChar,paramStart+1,(paramEnd-1)-(paramStart));
//                    firstParamInt = atoi(firstParamChar);
//                break;
//                case 2: //dos parametros buscamos ( , )
//                    //tomamos los valores entre la coma de innicio y la coma
//                    paramStart=strchr(&command[1][k],'(');
//                    paramEnd=strchr(&command[1][k],',');
//
//                    strncpy(firstParamChar,paramStart+1,(paramEnd-1)-(paramStart));
//                    firstParamInt = atoi(firstParamChar);
//
//                    //tomamos los valores entre la coma y el parentesis de cierre
//                    paramStart=strchr(&command[1][k],',');
//                    paramEnd=strchr(&command[1][k],')');
//
//                    //paramStart++;
//                    strncpy(secondParamChar,paramStart+1,(paramEnd-1)-(paramStart));
//                    secondParamInt = atoi(secondParamChar);
//
//                break;
//            }
//
//            if(!bitField.exeFunc){
//               for(i=0;i<21;i++){
//                    if(strcmp(comName,commands[i].name)!=0 || paramAmount!=commands[i].param){ //si no se encuntra el comando
//                        bitField.isError=1;
//                    } else{
//                        bitField.isError=0;
//                        comPos=i;
//                        i=21; //salimos del for
//                    }
//                }
//            }
//
//            gotoxy(10,45);
//            textbackground(RED);
//            if(bitField.isError){
//                textcolor(WHITE);
//                cprintf("ERROR COMANDO                  ");
//            } else{
//                textcolor(RED);
//                cprintf("                               ");
//            }
//
//            if(!bitField.isError){ //ejecutamos un comando solo si los caracteres ingresados corresponden con un comando de la lista
//                switch(commands[comPos].pos){
//                    case 1://setinicio
//                        for(i=0;i<39;i++){
//                            for(j=0;j<78;j++){
//                                if(display[i][j*2] == 3 || display[i][j*2] == 2){
//                                    display[i][j*2]=0; //posicion vacia, limpiamos para que al determinar un nuevo punto no quede el auto viejo
//                                    display[i][(j*2)+1]=0;
//                                }
//                            }
//                        }
//                        displaySection(0,0,159,40);
//
//                        startPoint();
//                        bitField.isDef=1; //usado como control para no mover si no se coloco la posicion inicial
//                    break;
//                    case 2://setfinal
//                        endPoint();
//                    break;
//                    case 3://resetmapa
//                        clearDisplay(0,0,40,80,1);
//                        firstParamInt=0;
//                        secondParamInt=0;
//                        startPoint();
//                    break;
//                    case 4://loadmapa
//                        loadMapa();
//                    break;
//                    case 5://savemapa
//                        saveMapa();
//                    break;
//                    case 6: //genmapa
//                        gotoxy(1,1);
//                        if(oldMazeRows<40)
//                            oldMazeRows++;
//                        if(oldMazeCols<79)
//                            oldMazeCols++;
//
//                        for(i=0;i<oldMazeRows;i++){
//                            for(j=0;j<oldMazeCols;j++){
//                                printf(" ");
//                            }
//                            printf("\n\r");
//                        }
//                        maze();
//                    break;
//                    case 7://resolver
//                        for(i=0;i<39;i++){
//                            for(j=0;j<78;j++){
//                                if(display[i][j*2] == 3 || display[i][j*2] == 2){
//                                    display[i][j*2]=0; //posicion vacia, limpiamos para que al determinar un nuevo punto no quede el auto viejo
//                                    display[i][(j*2)+1]=0;
//                                }
//                            }
//                        }
//                        displaySection(0,0,159,40);
//                        solve();
//                    break;
//                    case 8://gomapa
//                        move();
//                    break;
//                    case 9://steptime
//                        steptime=firstParamInt;
//                        bitField.timeConf=1; //igualamos a uno para que el tiempo en el que el auto se desplaza de modifique en tiempo de ejecucion
//                    break;
//                    case 10: //clrscr
//                        clrscr();
//                        bitField.isDef=1;
//                    break;
//                    case 11://adelante
//                        if(bitField.isDef){ //si se definio el punto de inicio entonces comenzar a mover
//                            TimerStart(forwardSpeed,steptime,PERIODIC);
//                        } else{
//                            textbackground(4); //ROJO
//                            textcolor(7); //BLANCO
//                            gotoxy(10,45);
//                            cprintf("DEFINA INICIO     ");
//                        }
//                    break;
//                    case 12://atras
//                        bitField.timeConf=1;
//                        if(bitField.isDef){
//                            TimerStart(backwardSpeed,steptime,PERIODIC);
//                            atras();
//                        } else{
//                            textbackground(4); //ROJO
//                            textcolor(7); //BLANCO
//                            gotoxy(10,45);
//                            cprintf("DEFINA INICIO     ");
//                        }
//                    break;
//                    case 13://girarizquierda
//                        if(bitField.isDef){
//                            bitField.firExe=1;
//                            girarIzquierda();
//                        } else{
//                            textbackground(4); //ROJO
//                            textcolor(7); //BLANCO
//                            gotoxy(10,45);
//                            cprintf("DEFINA INICIO     ");
//                        }
//                    break;
//                    case 14://girarderecha
//                        if(bitField.isDef){
//                            bitField.firExe=1;
//                            girarDerecha();
//                        } else{
//                            textbackground(4); //ROJO
//                            textcolor(7); //BLANCO
//                            gotoxy(10,45);
//                            cprintf("DEFINA INICIO     ");
//                        }
//                    break;
//                    case 15://repeat
//
//                    break;
//                    case 16://brushOn
//                        brushon();
//                    break;
//                    case 17://brushOff
//                        brushoff();
//                    break;
//                    case 18://loadsecuencia
//                        loadSequence();
//                    break;
//                    case 19://gosecuencia
//                        goSequence();
//                    break;
//                    case 20://resetsecuencia
//
//                    break;
//                    case 21://stop
//
//                    break;
//                }
//            }
//        }
    break;
    case 1:

    break;
    }
}

void move(){

}

void adelante(){
    static int i=0,j=0, k=0, l=0,temp=0;
    int x=carData.posX;
    int y=carData.posY;
    cells=firstParamInt;

    cont++;
    switch(carData.direction){ //dependiendo dela direccion movemos
        case 0: //UP
            if(carData.posX-1>=0){
                x--; //calculamos x para posicionar el auto en la posicion
            } else{
                cont=cells;
            }
            //pintamos el auto
            temp=6;
            for(k=0;k<2;k++){
                for(l=0;l<2;l++){
                    display[x+k][2*(y+l)] = 3;
                    display[x+k][(2*(y+l))+ 1] = temp;
                }
                temp=4;
            }


            //pintamos las casillas por donde pasa el auto
            display[x+2][2*y]=2; //igualamos a 2 las posiciones en donde hay colores
            display[x+2][2*(y+1)]=2;
            display[x+2][(2*y)+1]=carData.pathColor;
            display[x+2][(2*(y+1))+1]=carData.pathColor;

            for(i=0;i<1;i++){
                for(j=0;j<2;j++){
                    display[x+1-i][2*(y+j)]=2;
                    display[x+1-i][(2*(y+j))+1]=carData.pathColor;
                }
            }
        break;
        case 1: //RIGHT
            if(carData.posY+1<=78){
                y++;
            } else{
                cont=cells;
            }

            temp=4;
            for(l=0;l<2;l++){
                for(k=0;k<2;k++){
                    display[x+k][2*(y+l)] = 3;
                    display[x+k][(2*(y+l))+ 1] = temp;
                }
                temp=6;
            }

            //pintamos las casillas por donde pasa el auto
            for(i=0;i<1;i++){
                for(j=0;j<2;j++){
                    display[x+j][2*(y+i-1)]=2;
                    display[x+j][(2*(y+i-1))+1]=carData.pathColor;
                }
            }
        break;
        case 2: //DOWN
            if(carData.posX+1<=38){
                x++; //movemos en una posicion
            } else{
                cont=cells;
            }
            //pintamos el auto
            temp=4;
            for(k=0;k<2;k++){
                for(l=0;l<2;l++){
                    display[x+k][2*(y+l)] = 3;
                    display[x+k][(2*(y+l))+ 1] = temp;
                }
                temp=6;
            }

            //pintamos las casillas por donde pasa el auto
            for(i=0;i<1;i++){
                for(j=0;j<2;j++){
                    //habilitamos la casilla
                    display[x+i-1][2*(y+j)]=2;
                    display[x+i-1][(2*(y+j))+1]=carData.pathColor;
                }
            }
        break;
        case 3: //LEFT
            if(carData.posY-1>=0){
                y--;
            } else{
                cont=cells;
            }
            temp=6;
            //dibujamos el auto
            for(l=0;l<2;l++){
                for(k=0;k<2;k++){
                    display[x+k][2*(y+l)] = 3;
                    display[x+k][(2*(y+l))+ 1] = temp;
                }
                temp=4;
            }

            //pintamos el camino
            display[x][2*(y+2)]=2;
            display[x+1][2*(y+2)]=2;
            display[x][(2*(y+2))+1]=carData.pathColor;
            display[x+1][(2*(y+2))+1]=carData.pathColor;

            for(i=0;i<1;i++){
                for(j=0;j<2;j++){
                    //habilitamos la casilla
                    display[x+j][2*(y-i+1)]=2;
                    display[x+j][(2*(y-i+1))+1]=carData.pathColor;
                }
            }
        break;
    }

    if(cont==cells){
        cont = 0; //igualamos a 0 para la siguiente ejecucion
        TimerStop(forwardSpeed);
        displaySection(0,0,159,40); //testear!!!!
        return;
    }

    comPos=11;
    carData.posX=x;
    carData.posY=y;
    displaySection(0,0,159,40);
}

void atras(){
    int i,j,temp;
    int cells=firstParamInt;
    int x=carData.posX;
    int y=carData.posY;

    cont++;
    switch(carData.direction){
        case 0: //UP
            //conrolamos que no se vaya afuera en caso de que sea muy grande el numero ingresado
            if(carData.posX+1<=38){
                x++; //movemos en una posicion
            } else{
                cont=cells;
            }

            temp=6;
            for(i=0;i<2;i++){
                for(j=0;j<2;j++){
                    display[x+i][2*(y+j)] = 3;
                    display[x+i][(2*(y+j))+ 1] = temp;
                }
                temp=4;
            }

            //pintamos las casillas recorridas
            for(i=0;i<1;i++){
                for(j=0;j<2;j++){
                    //habilitamos la casilla
                    display[x+i-1][2*(y+j)]=2;
                    display[x+i-1][(2*(y+j))+1]=carData.pathColor;
                }
            }
        break;
        case 1: //RIGHT
            if(carData.posY-1>=0){
                y--;
            } else{
                cont=cells;
            }

            //pintamos el auto
            temp=4;
            for(j=0;j<2;j++){
                for(i=0;i<2;i++){
                    display[x+i][2*(y+j)] = 3;
                    display[x+i][(2*(y+j))+ 1] = temp;
                }
                temp=6;
            }

            //pintamos las casillas
            for(i=0;i<1;i++){
                for(j=0;j<2;j++){
                    display[x+i][2*(y+j+1)]=2;
                    display[x+i][(2*(y+j+1))+1]=carData.pathColor;
                }
            }
        break;
        case 2: //DOWN
            if(carData.posX-1>=0){
                x--; //calculamos x para posicionar el auto en la posicion
            } else{
                cont=cells;
            }

            //pintamos el auto
            temp=4;
            for(i=0;i<2;i++){
                for(j=0;j<2;j++){
                    display[x+i][2*(y+j)] = 3;
                    display[x+i][(2*(y+j))+ 1] = temp;
                }
                temp=6;
            }




            temp=6;
            for(i=0;i<2;i++){
                for(j=0;j<2;j++){
                    display[x+i][2*(y+j)] = 3;
                    display[x+i][(2*(y+j))+ 1] = temp;
                }
            }
            temp=4;

            //pintamos las casillas por donde pasa el auto
            display[x+2][2*y]=2;
            display[x+2][2*(y+1)]=2;
            display[x+2][(2*y)+1]=carData.pathColor;
            display[x+2][(2*(y+1))+1]=carData.pathColor;

            for(i=0;i<1;i++){
                for(j=0;j<2;j++){
                    //habilitamos la casilla
                    display[x-i+1][2*(y+j)]=2;
                    display[x-i+1][(2*(y+j))+1]=carData.pathColor;
                }
            }
        break;
        case 3: //LEFT
            if(carData.posY+1<=78){
                y++;
            } else{
                cont=cells;
            }

            //pintamos el auto
            temp=6;
            for(j=0;j<2;j++){
                for(i=0;i<2;i++){
                    display[x+i][2*(y+j)] = 3;
                    display[x+i][(2*(y+j))+ 1] = temp;
                }
                temp=4;
            }

            //pintamos el camino
            for(i=0;i<1;i++){
                for(j=0;j<2;j++){
                    //habilitamos la casilla
                    display[x+j][2*(y+i-1)]=2;
                    display[x+j][(2*(y+i-1))+1]=carData.pathColor;
                }
            }
        break;
    }

    if(cont==cells){
        cont = 0; //igualamos a 0 para la siguiente ejecucion
        TimerStop(backwardSpeed);
        displaySection(0,0,159,40); //testear!!!!
        return;
    }

    comPos=12;
    carData.posX=x;
    carData.posY=y;
    displaySection(0,0,159,40);
}

void girarIzquierda(){
    int i,j,temp;
    int times=firstParamInt;
    int x=carData.posX;
    int y=carData.posY;

    for(i=0;i<times;i++){
        carData.direction--;
        if(carData.direction<0)
            carData.direction=3;
    }

    switch(carData.direction){
        case 0: //UP
            temp=6;
            for(i=0;i<2;i++){
                for(j=0;j<2;j++){
                    display[x+i][2*(y+j)] = 1;
                    display[x+i][(2*(y+j))+ 1] = temp;
                }
                temp=4;
            }
        break;
        case 1: //RIGHT
            temp=4;
            for(j=0;j<2;j++){
                for(i=0;i<2;i++){
                    display[x+i][2*(y+j)] = 1;
                    display[x+i][(2*(y+j))+ 1] = temp;
                }
                temp=6;
            }

        break;
        case 2: //DOWN
            temp=4;
            for(i=0;i<2;i++){
                for(j=0;j<2;j++){
                    display[x+i][2*(y+j)] = 1;
                    display[x+i][(2*(y+j))+ 1] = temp;
                }
                temp=6;
            }
        break;
        case 3: //LEFT
            temp=6;
            for(j=0;j<2;j++){
                for(i=0;i<2;i++){
                    display[x+i][2*(y+j)] = 1;
                    display[x+i][(2*(y+j))+ 1] = temp;
                }
                temp=4;
            }
        break;
    }

    carData.posX=x;
    carData.posY=y;
   // displaySection(2*y,x,2*(y+2),x+2);
   displaySection(0,0,159,40);
}

void girarDerecha(){
    int i,j,temp;
    int times=firstParamInt;
    int x=carData.posX;
    int y=carData.posY;

    for(i=0;i<times;i++){
        carData.direction++;
        if(carData.direction>3)
            carData.direction=0;
    }

    switch(carData.direction){
        case 0: //UP
            temp=6;
            for(i=0;i<2;i++){
                for(j=0;j<2;j++){
                    display[x+i][2*(y+j)] = 1;
                    display[x+i][(2*(y+j))+ 1] = temp;
                }
                temp=4;
            }
        break;
        case 1: //RIGHT
            temp=4;
            for(j=0;j<2;j++){
                for(i=0;i<2;i++){
                    display[x+i][2*(y+j)] = 1;
                    display[x+i][(2*(y+j))+ 1] = temp;
                }
                temp=6;
            }

        break;
        case 2: //DOWN
            temp=4;
            for(i=0;i<2;i++){
                for(j=0;j<2;j++){
                    display[x+i][2*(y+j)] = 1;
                    display[x+i][(2*(y+j))+ 1] = temp;
                }
                temp=6;
            }
        break;
        case 3: //LEFT
            temp=6;
            for(j=0;j<2;j++){
                for(i=0;i<2;i++){
                    display[x+i][2*(y+j)] = 1;
                    display[x+i][(2*(y+j))+ 1] = temp;
                }
                temp=4;
            }
        break;
    }

    carData.posX=x;
    carData.posY=y;
    displaySection(0,0,159,40);
}

void brushon(){
    if(!strcmp(firstParamChar, "negro")){
        carData.pathColor=0;
    } else if(!strcmp(firstParamChar, "azul")){
        carData.pathColor=1;
    } else if(!strcmp(firstParamChar, "verde")){
        carData.pathColor=2;
    } else if(!strcmp(firstParamChar, "cian")){
        carData.pathColor=3;
    } else if(!strcmp(firstParamChar, "rojo")){
        carData.pathColor=4;
    } else if(!strcmp(firstParamChar, "magenta")){
        carData.pathColor=5;
    } else if(!strcmp(firstParamChar, "amarillo")){
        carData.pathColor=6;
    } else if(!strcmp(firstParamChar, "blanco")){
        carData.pathColor=7;
    } else{
        textbackground(4); //ROJO
        textcolor(7); //BLANCO
        gotoxy(10,45);
        cprintf("ERROR COLOR");

    }
}

void brushoff(){
    carData.pathColor=0; //cuando no queremos dibujar, pintamos en negro
}

void clrscr(){
    if(bitField.isCarMap){ //para limpiar solamente en caso de que haya algo
        clearDisplay(0,0,40,80,1);
        bitField.firExe=1;
    }

    bitField.isCarMap=0;
//    firstParamInt=0;
//    secondParamInt=0;
//    startPoint();
}

/* END Function prototypes user code ------------------------------------------*/

int main(){
    /* Local variables -----------------------------------------------------------*/
    int i, j;
    int cont=0;


    //VARIABLES DEL CAMPO DE BITS
    bitField.isError = 0;
    bitField.cursorBlink=1;
    bitField.firExe=1;
    bitField.isCarMap=0;
    bitField.isDef=0; //no se definio todavia la posicion inicial
    bitField.timeConf=0;
    bitField.exeFunc=0;

    //INICIALIZACION DE VARIBALES DE STRUCT
    carData.pathColor=0;//igualamos a cero para pintar las casillas de color negro

    //ticker
    forwardSpeed=TimerAdd();
    backwardSpeed=TimerAdd();

    TimerConnect(forwardSpeed,adelante);
    TimerConnect(backwardSpeed,atras);

    /* END Local variables -------------------------------------------------------*/

    /* User code -----------------------------------------------------------------*/
    textmode(C4350); //definimos el display de 40X80
    createDisplay(&display[0][0], 160, 40); //creamos el display de 160X40
    _setcursortype(_NOCURSOR); //quitamos el cursor
    srand(time(NULL)); //generamos numeros aleatorio
    lastTime=clock();

    while(1){
        opt = '\0';
        if(kbhit()){
            if((opt = getch()) == 0)
                opt = getch() + 1000;
            if(opt == ESC)
                break;
        }

        //control tiempo
        currentTime=clock();
        if(((currentTime-lastTime)>500)&&bitField.cursorBlink){
            bitField.cursorBlink=0;
            lastTime=clock();
        } else if(((currentTime-lastTime)>500)&&!bitField.cursorBlink){
            bitField.cursorBlink=1;
            lastTime=clock();
        }

        if(opt==ENTER){
            for(i=0;i<20;i++){
                firstParamChar[i]=NULL;
                secondParamChar[i]=NULL;
                comName[i]=NULL;
            }

            for(i=0;i<sizeof(mainEditor);i++){
                if(mainEditor[i]=='\n')
                    cont++;
            }

            parser(1024,mainEditor); // sformateamos el texto ingresado

            comLength = strcspn(mainEditor,"("); //stringLenth
            strncpy(comName, mainEditor, comLength); //copiamos la cadena hasta el (, por lo tanto solo tendriamos los caracteres

            for(i=0;i<sizeof(comName);i++) //convertimos los posibles caracteres que esten en mayusculas a minusculas
                comName[i]=tolower(comName[i]);

            //CONTROLAMOS LOS PARAMETROS QUE SE INGRESAN
            paramStart=strchr(mainEditor,'(');
            paramEnd=strchr(mainEditor,')');

            if (paramStart != NULL && paramEnd != NULL) {
                paramStart++;
                char* comma = strchr(paramStart, ',');
                if (comma != NULL && comma < paramEnd) {
                    paramAmount=2;
                } else {
                    paramAmount=1;
                }
            } else {
                paramAmount=0;
            }

            switch(paramAmount){
                case 1: //Solo un parametro buscamos ()
                    paramStart=strchr(mainEditor,'(');
                    paramEnd=strchr(mainEditor,')');

                    //paramStart++;
                    strncpy(firstParamChar,paramStart+1,(paramEnd-1)-(paramStart));
                    firstParamInt = atoi(firstParamChar);
                break;
                case 2: //dos parametros buscamos ( , )
                    //tomamos los valores entre la coma de innicio y la coma
                    paramStart=strchr(mainEditor,'(');
                    paramEnd=strchr(mainEditor,',');

                    strncpy(firstParamChar,paramStart+1,(paramEnd-1)-(paramStart));
                    firstParamInt = atoi(firstParamChar);

                    //tomamos los valores entre la coma y el parentesis de cierre
                    paramStart=strchr(mainEditor,',');
                    paramEnd=strchr(mainEditor,')');

                    //paramStart++;
                    strncpy(secondParamChar,paramStart+1,(paramEnd-1)-(paramStart));
                    secondParamInt = atoi(secondParamChar);

                break;
            }

            if(!bitField.exeFunc){
               for(i=0;i<21;i++){
                    if(strcmp(comName,commands[i].name)!=0 || paramAmount!=commands[i].param){ //si no se encuntra el comando
                        bitField.isError=1;
                    } else{
                        bitField.isError=0;
                        comPos=i;
                        i=21; //salimos del for
                    }
                }
            }

            gotoxy(10,45);
            textbackground(RED);
            if(bitField.isError){
                textcolor(WHITE);
                cprintf("ERROR COMANDO                  ");
            } else{
                textcolor(RED);
                cprintf("                               ");
            }

            if(!bitField.isError){ //ejecutamos un comando solo si los caracteres ingresados corresponden con un comando de la lista
                switch(commands[comPos].pos){
                    case 1://setinicio
                        for(i=0;i<39;i++){
                            for(j=0;j<78;j++){
                                if(display[i][j*2] == 3 || display[i][j*2] == 2){
                                    display[i][j*2]=0; //posicion vacia, limpiamos para que al determinar un nuevo punto no quede el auto viejo
                                    display[i][(j*2)+1]=0;
                                }
                            }
                        }
                        displaySection(0,0,159,40);

                        startPoint();
                        bitField.isDef=1; //usado como control para no mover si no se coloco la posicion inicial
                    break;
                    case 2://setfinal
                        endPoint();
                    break;
                    case 3://resetmapa
                        clearDisplay(0,0,40,80,1);
                        firstParamInt=0;
                        secondParamInt=0;
                        startPoint();
                    break;
                    case 4://loadmapa
                        loadMapa();
                    break;
                    case 5://savemapa
                        saveMapa();
                    break;
                    case 6: //genmapa
                        gotoxy(1,1);
                        if(oldMazeRows<40)
                            oldMazeRows++;
                        if(oldMazeCols<79)
                            oldMazeCols++;

                        for(i=0;i<oldMazeRows;i++){
                            for(j=0;j<oldMazeCols;j++){
                                printf(" ");
                            }
                            printf("\n\r");
                        }
                        maze();
                    break;
                    case 7://resolver
                        for(i=0;i<39;i++){
                            for(j=0;j<78;j++){
                                if(display[i][j*2] == 3 || display[i][j*2] == 2){
                                    display[i][j*2]=0; //posicion vacia, limpiamos para que al determinar un nuevo punto no quede el auto viejo
                                    display[i][(j*2)+1]=0;
                                }
                            }
                        }
                        displaySection(0,0,159,40);
                        solve();
                    break;
                    case 8://gomapa
                        move();
                    break;
                    case 9://steptime
                        steptime=firstParamInt;
                        bitField.timeConf=1; //igualamos a uno para que el tiempo en el que el auto se desplaza de modifique en tiempo de ejecucion
                    break;
                    case 10: //clrscr
                        clrscr();
                        bitField.isDef=1;
                    break;
                    case 11://adelante
                        if(bitField.isDef){ //si se definio el punto de inicio entonces comenzar a mover
                            TimerStart(forwardSpeed,steptime,PERIODIC);
                        } else{
                            textbackground(4); //ROJO
                            textcolor(7); //BLANCO
                            gotoxy(10,45);
                            cprintf("DEFINA INICIO     ");
                        }
                    break;
                    case 12://atras
                        bitField.timeConf=1;
                        if(bitField.isDef){
                            TimerStart(backwardSpeed,steptime,PERIODIC);
                            atras();
                        } else{
                            textbackground(4); //ROJO
                            textcolor(7); //BLANCO
                            gotoxy(10,45);
                            cprintf("DEFINA INICIO     ");
                        }
                    break;
                    case 13://girarizquierda
                        if(bitField.isDef){
                            bitField.firExe=1;
                            girarIzquierda();
                        } else{
                            textbackground(4); //ROJO
                            textcolor(7); //BLANCO
                            gotoxy(10,45);
                            cprintf("DEFINA INICIO     ");
                        }
                    break;
                    case 14://girarderecha
                        if(bitField.isDef){
                            bitField.firExe=1;
                            girarDerecha();
                        } else{
                            textbackground(4); //ROJO
                            textcolor(7); //BLANCO
                            gotoxy(10,45);
                            cprintf("DEFINA INICIO     ");
                        }
                    break;
                    case 15://repeat

                    break;
                    case 16://brushOn
                        brushon();
                    break;
                    case 17://brushOff
                        brushoff();
                    break;
                    case 18://loadsecuencia
                        loadSequence();
                    break;
                    case 19://gosecuencia
                        goSequence();
                    break;
                    case 20://resetsecuencia

                    break;
                    case 21://stop

                    break;
                }
            }
        }

        //imprimimos el valor del steptime constantemente
        gotoxy(6,46);
        textbackground(6);
        textcolor(7);
        cprintf("%i                       ", steptime);

        if(bitField.firExe){ //primera ejecucion
            for(i=0;i<1024;i++)
                mainEditor[i]=NULL;

            gotoxy(1,41);
            textbackground(3); //violeta
            textcolor(3); //violeta
            for(i=0;i<80;i++)
                cprintf("G");

            //dibujamos la seccion roja inferior
            gotoxy(1,45);
            textbackground(4); //ROJO
            textcolor(7); //BLANCO
            cprintf("WARNING:");
            textcolor(4); //ROJO
            for(i=0;i<72;i++)
            cprintf("G");

            gotoxy(1,46);
            textbackground(6); //AMARILLO
            textcolor(7); //BANCO
            cprintf("TIME:");
            textcolor(6); //AMARILLO
            for(i=0;i<75;i++)
            cprintf("G");

            bitField.firExe=0;
        }

        editor(1024, 24, mainEditor,opt, 5, 43, 2, 5, bitField.cursorBlink);
        TickerTask(); //parte del ticker
                    gotoxy(1,50);
//            printf("com %i | dir %i", commands[comPos].pos, carData.direction);
    }
//                gotoxy(30,30);
//            printf("CONT %i", sizeof(mainEditor));

    return 0;
}
/* END User code -------------------------------------------------------------*/

