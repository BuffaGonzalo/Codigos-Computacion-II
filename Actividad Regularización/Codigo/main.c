/*
===============================================================================
   Filename.c
   (c) 2023 Author: Gonzalo Martín Buffa

   Description:

===============================================================================
*/

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <dos.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include "CP865.h"
#include "graphics.h"
#include "ticker.h"
/* END Includes --------------------------------------------------------------*/


/* typedef -------------------------------------------------------------------*/
typedef struct{
    unsigned char flag1:1; /**< Utilizada para controlar el tiempo en que se actualiza el display*/
    unsigned char flag2:1; /**< Utilizada para mostrar o ocultar el led en el momento requerido*/
    unsigned char flag3:1; /**< No utilizada*/
    unsigned char flag4:1; /**< Utilizada para controlar el cursor del editor*/
    unsigned char flag5:1; /**< Utilizada para limpiar la pantalla una vez al inicio del juego de la memoria*/
    unsigned char flag6:1; /**< No utilizada*/
    unsigned char flag7:1; /**< No utilizada*/
    unsigned char flag8:1; /**< No utilizada*/
} _bitField;

typedef enum{
    GAME_START=0, /**< Estado utilizado para mostrar el cartel inicial - start */
	GAME_IDLE, /**< Estado utilizado para realizar la de espera de 2 segundos */
	GAME_SQ, /**< Estado utilizado para mostrar la secuencia de números dependiendo del nivel en que te encuentres */
	GAME_DATA, /**< Estado utilizado para ingreso datos */
	GAME_RES, /**< Estado utilizado para mostrar el resultado WON o LOST */
}_states;

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
/* END define ----------------------------------------------------------------*/


/* Function prototypes -------------------------------------------------------*/
/** \brief digitalClock
 * Funcion encargada de determinar generar un reloj digital, lleva a cabo esto enviando a las funciones de la librería graphics
 * los numeros  con sus colores correspondietes y las posiciones de cada uno en el display.
 *
 * \return void
 */

void digitalClock();

/** \brief analogClock
 *  Función encargada de generar un reloj analogico, lo lleva a cabo generando una circunferencia y luego imprimiendo las agujas.
 *
 * \return void
 */

void analogClock();

/** \brief memoryGame
 *  Función encargada de realizar un juego de la memoria "Simón dice", el juego cuenta con 10 niveles en los cuales se debe de ingresar los números de la
 *  secuencia mostrasa dependiendo de la dificulatad EASY (numeros de los niveles constantes) HARD numeros de la secuencia se generan nuevamente con cada nivel.
 *  Presionando F3 se cambia de modo de juego, y presionando F2 se inicia o finaliza el juego.
 *
 * \return void
 */

void memoryGame();

/** \brief memoryGame
 *  Función encargada de imprimir un mensaje en morse ingresado en un editor, el mensaje se muestra en un led centrado el cuyo tiempo de encendido y apagado varia
 *  en función de si tenemos una rayo o un punto, el mensaje se comienza a imprimir con F2 y no para hasta que se vuelva a presionar.
 *
 * \return void
 */

void morseCode();

/** \brief led
 *  Funcion encargada de generar un led en la esquina superior izquierda el cual se prende y se apaga en intervalos diferentes dependiendo del modo de juego
 *
 * \return void
 */

void led();
/* END Function prototypes ---------------------------------------------------*/

/* Global variables ----------------------------------------------------------*/
unsigned char display[40][160]; /**< Matriz del display en la cual se guardan los caracteres mostrados*/
unsigned int timeOut = 100; /**< Variable utilizada como control de los temporizadores*/
struct tm *myTm;
short opt; /**< Variable en la cual se guardan los valores ingresados por el usuario */
char editor[256]; /**< Vector utilizado como editor */
time_t myTime;
_bitField control; /**< Campo de bits utilizado como banderas */
_states gameStates; /**< Enumeracion de la maquina de estados del juego de la memoria */
clock_t currentGameTime, lastGameTime;

//arreglo con los cargacteres de codigo morse, primero estan los numeros y luego las letras
const unsigned char morse[45][6] = { "RRRRR", "PRRRR", "PPRRR", "PPPRR", "PPPPR", /**< Matriz global constate la cual contiene los valores del código morse, comienza con los valores de los numeros y luego letras*/
"PPPPP", "RPPPP", "RRPPP", "RRRPP", "RRRRP","","","","","","","","PR", "RPPP",
"RPRP", "RPP", "P", "PPRP", "RRP","PPPP", "PP", "PRRR", "RPR", "PRPP", "RR", "RP",
"RRR", "PRRP", "RRPR", "PRP","PPP", "R", "PPR", "PPPR", "PRR", "RPPR", "RPRR", "RRPP"};

const unsigned char start[10] = {91, 70, 50, 93, 58, 83, 84, 65, 82, 84}; /**< Cartel [F2]:START mostrado en el estado de espera del juego de la memoria*/
const unsigned char won[3] = {87, 79, 78}; /**< Cartel WON mostrado al final del juego de la memoria */
const unsigned char lost[4] = {76, 79, 83, 84}; /**< Cartel LOST mostrado al final del juego de la memoria */
const unsigned char hard[4] = {72, 65, 82, 68}; /**< Cartel correspondiente al modo de juego dificil, se muestra en la sección superior derecha del display */
const unsigned char easy[4] = {69, 65, 83, 89}; /**< Cartel correspondiente al modo de juego facil, se muestra en la sección superior derecha del display */
/* END Global variables ------------------------------------------------------*/

/* Function prototypes user code ----------------------------------------------*/
void digitalClock(){
    int horas=myTm->tm_hour; //variable local
    int minutos=myTm->tm_min; //variable local
    int segundos=myTm->tm_sec; //variable local
    char backgroundColor, fontColor, fontValue; //fontValue es el valor de la font impreso
    int posXmax, posYmax, posX, posY; //posX, posY, posXmax y posYmax son utilizados para mostrar correctamente el display
    char control=8; //variable local utilizada para cargar correctamente los caracteres en el display
    posY=15; //lo definimos fuera y no dentro debido a que todos deben de estar a la misma altura
    posYmax=posY+9;

    //BLACK: 0 BLUE: 1 GREEN: 2 CYAN: 3 RED: 4 MAGENTA: 5 YELLOW: 6 WHITE: 7
    while(control!=0){
        backgroundColor=1;
        fontColor=1;
        switch(control){
            case 1://tomamos la decena de la hora
                fontValue=((horas/10)%10) + '0';
                posX=16; //comenzaba en 8
                control=0;
            break;
            case 2://tomamos la unidad de la hora
                fontValue=(horas%10) + '0';
                posX=32;
                control=1;
            break;
            case 3: //dos puntos
                fontValue=10 + '0';
                posX=48;
                control=2;
                backgroundColor=5;
                fontColor=5;
            break;
            case 4://tomamos la decena de los minutos
                fontValue=((minutos/10)%10) + '0';
                posX=64;
                control=3;
            break;
            case 5://tomamos la unidad de los minutos
                fontValue=(minutos%10) + '0';
                posX=80;
                control=4;
            break;
            case 6: //dos puntos
                fontValue= 10 + '0';
                posX=96;
                control=5;
                backgroundColor=5;
                fontColor=5;
            break;
            case 7://tomamos la decena de los segundos
                fontValue=((segundos/10)%10) + '0';
                posX=112;
                control=6;
            break;
            case 8://tomamos la unidad de los segundos
                fontValue=(segundos%10) + '0';
                posX=128;
                posXmax=posX+16;
                control=7;
            break;
        }
        loadLetters(fontValue, backgroundColor, fontColor, posX, posY); //llamamos a la funcion para cargar los datos en la matriz
        displaySection(posX, posY, posXmax, posYmax); //mostramos los datos cargados en el display
    }
}

void analogClock(){
    int h=15, k=15, r=15, m=26, l=6;
    int agujaX;
    int agujaY;
    int i,j;
    char backgroundColor, fontColor;
    float minRad;
    struct time t;
    gettime(&t);

    //BLACK: 0 BLUE: 1 GREEN: 2 CYAN: 3 RED: 4 MAGENTA: 5 YELLOW: 6 WHITE: 7
    fontColor=5;
    for(i=0;i<31;i++){ //dibujamos la circunferencia
        for(j=0;j<31;j++){
            int x = i-h; //h desplazamiento en x
            int y = j-k; //k desplazamiento en y
            if (fabs(sqrt(x * x + y * y) - r) <= 1) {
                backgroundColor=5;
                display[i+l][2*(j+m)] = 254;
            }else{
                backgroundColor=0;
                display[i+l][2*(j+m)]=' ';
            }
            display[i+l][(2*(j+m))+1]=(backgroundColor&0x0F)|(fontColor<<4); //cargamos en el display el color de fondo
        }
    }

    minRad = ((t.ti_hour*30+(t.ti_min/20)*10.0)-90)*M_PI/180;
    for(r=0;r<7;r++){ //hora
        agujaY = h+floor((r * cos(minRad)+0.5)); //sumamos h para centrarlo en X
        agujaX = k+floor((r * sin(minRad)+0.5)); //sumamos k para centrarlo en Y
        display[agujaX+l][2*(agujaY+m)] = 254;
        backgroundColor=1;
        fontColor=1;
        display[agujaX+l][(2*(agujaY+m))+1]=(backgroundColor&0x0F)|(fontColor<<4);
    }

    minRad = ((t.ti_min*6.0+(t.ti_sec/20)*2.0)-90)*M_PI/180;
    for(r=0;r<14;r++){ //minutero
        agujaY = h+floor((r * cos(minRad)+0.5)); //sumamos h para centrarlo en X
        agujaX = k+floor((r * sin(minRad)+0.5)); //sumamos k para centrarlo en Y
        display[agujaX+l][2*(agujaY+m)] = 254;
        backgroundColor=6;
        fontColor=6;
        display[agujaX+l][(2*(agujaY+m))+1]=(backgroundColor&0x0F)|(fontColor<<4);
    }

    minRad = ((t.ti_sec*6 + (t.ti_hund/20)*1.2)-90)*M_PI/180; //segundos/20 debido a que cuando es 20 daria 1
    for(r=0;r<14;r++){ //segundero  milisegundso /20*1,2   //cientos de milisegundos en los segundos cmabiar los minutos por segundos y los segundos por milisegundos
        //ti_hund -> cientos de milisegundos
        //minutos segundos
        //6/5->1.2
        agujaY = h+floor((r * cos(minRad)+0.5)); //sumamos h para centrarlo en X
        agujaX = k+floor((r * sin(minRad)+0.5)); //sumamos k para centrarlo en Y
        display[agujaX+l][2*(agujaY+m)] = 254;
        backgroundColor=4;
        fontColor=4;
        display[agujaX+l][(2*(agujaY+m))+1]=(backgroundColor&0x0F)|(fontColor<<4);
    }

    displaySection(6,6,160,40);
}

void memoryGame(){
    int posXmax, posYmax;
    static unsigned short i=0;
    static char mode=0;
    static char temp=-1;
    static char color = 0;
    static int posX=0, posY=0, muestreo=80; //posY puede ir hasta 40
    static char niveles[10];
    static char inGame=0; //inGame==0, significa que no estamos en el juego
    static char status=0; //usada para mostrar el cartel lost o won, 0=ninguno, 1=won, 2=lost
    static unsigned char cont, k;

    if(opt==F1)
        gameStates=GAME_START;

    if(opt==F2){
        gameStates =(gameStates==GAME_START)? GAME_IDLE : GAME_START; //0 = fuera del juego - cartel F2

        if(gameStates==GAME_IDLE){ //preparamos el incio del modo EASY
            clearDisplay(0,0,40,160,1);
            control.flag5=1; //usamos para limpiar la pantalla solo una vez
            for(i=0;i<10;i++) //inicializamos
                niveles[i]=NULL;
        }
        cont=k=0;
        lastGameTime = clock();
    }

    if(opt==F3 && !inGame){ //cambiamos de modo
        mode=(mode==0)? 1 : 0; //mode=0 modo facil, mode=1 modo dificil
    }

    if(!mode){ //CARTEL MODO FACIL
        posX=96;
        posY=0;
        posYmax=8;
        for(i=0;i<4;i++){ //cargamos en la matriz la frase
            loadLetters(easy[i], 2, 2, posX, posY); //llamamos a la funcion para cargar los datos en la matriz
            posX+=16;
            posXmax=posX;
        }
        i=0;
        posX=20;
        displaySection(posX, posY, posXmax, posYmax);
    } else{ //CARTEL MODO DIFICIL
        posX=96;
        posY=0;
        posYmax=8;
        for(i=0;i<4;i++){
            loadLetters(hard[i], 6, 6, posX, posY); //llamamos a la funcion para cargar los datos en la matriz
            posX+=16;
            posXmax=posX;
        }
        i=0;
        posX=20;
        displaySection(posX, posY, posXmax, posYmax);
    }

    switch(gameStates){
        case GAME_START: //cartel inicial - START
            gotoxy(60,45);
            printf("             ");
            posY=15;
            posX=0;
            for(i=0;i<10;i++){
                posX+=16;
                loadLetters(start[i], 5, 5, (posX+muestreo)%160,posY); //(posX+muestreo)%160
            }
            muestreo+=4;
            if(muestreo>160)
                muestreo=0;

            posYmax=posY+8;
            displaySection(0, posY, 160, posYmax);
        break;
        case GAME_IDLE: //ingreso datos
            currentGameTime=clock();
            if((currentGameTime-lastGameTime)>=20*timeOut){ //20 porque son 2 segundos
                lastGameTime=clock();
                gameStates=GAME_SQ;
            }
        break;
        case GAME_SQ: //estado de espera
            gotoxy(60,45);
            printf("             ");
            if(control.flag5){ //mostrar al inicio
                if(!mode){ //MODO EASY
                        for(i=0;i<10;i++){
                            niveles[i]=(rand() % 10 + 48);
                        }
//                        for(i=0;i<10;i++){
//                            printf("%c ", niveles[i]);
//                        }
                }
                cont=0;
                k=0;
                color=(rand() % 7 + 1);
                lastGameTime=clock();
                control.flag5=0;
            }

            if(mode && cont>temp){ //MODO HARD - no se tiene que ejecutar una vez porque sino no se generan los demas valores
                for(i=0;i<=cont;i++){
                    niveles[i]=(rand() % 10 + 48);
                }
//                for(i=0;i<=cont;i++){
//                    printf("%c ", niveles[i]);
//                }
                temp=cont;
            }

                currentGameTime=clock();
//                printf("\nK -> %i", k);
//                printf("CONT -> %i", cont);
                if((currentGameTime-lastGameTime)>=3*timeOut){
                    loadLetters(niveles[k], color, color, 72, 15); //5 = color violet
                    displaySection(72, 15, 88 , 23); //mostrar en 36
                }
                if(k<=cont && ((currentGameTime-lastGameTime)>=5*timeOut)){
                    if(k==cont){
                        gameStates=GAME_DATA;
                        lastGameTime=clock();
                        k=0;
                        break;
                    }
                    lastGameTime=clock();
                    color=(rand() % 7 + 1);
                    k++;
                }
        break;
        case GAME_DATA:
            gotoxy(60,45);
            printf("INGRESE DATOS");
            currentGameTime=clock();
                if(((currentGameTime-lastGameTime)>=timeOut)&&(opt==niveles[k]&&isalnum(opt))){
                    color=(rand() % 7 + 1);
                    loadLetters(opt, color, color, 72, 15); //5 = color violet
                    displaySection(72, 15, 88 , 23); //mostrar en 36
                    if(k==cont){
                        cont++;
                        k=0;
                        gameStates=GAME_SQ;
                    }
                    if(cont==10){ //ejecución en caso de vicotoria
                        cont=0;
                        status=1;//ganaste
                        gameStates=GAME_RES;
                        lastGameTime=clock();
                    }
                    k++;
                    lastGameTime=clock();
                    break;
                }

                if(((currentGameTime-lastGameTime)>=40*timeOut)||(opt!=niveles[k]&&isalnum(opt))){ //ejecución derrota
                    status=2;
                    cont=0;
                    lastGameTime=clock();
                    gameStates=GAME_RES;
                }
        break;
        case GAME_RES:
            if(cont<5 && status!=0){ //sirve para mostrar el cartel final
                currentGameTime=clock();
                if(currentGameTime-lastGameTime<=3*timeOut){
                    switch (status){
                        case 1: //mostramos WON
                            posX=56;
                            posY=15;
                            posYmax=23;
                            for(i=0;i<3;i++){
                                loadLetters(won[i], 3, 3, posX, posY); //llamamos a la funcion para cargar los datos en la matriz
                                posX+=16;
                                posXmax=posX;
                            }
                            posX=56;
                            displaySection(posX, posY, posXmax, posYmax); //mostrar en 30
                        break;
                        case 2: //mostramos LOST
                            posX=48;
                            posY=15;
                            posYmax=23;
                            for(i=0;i<4;i++){
                                loadLetters(lost[i], 3, 3, posX, posY); //llamamos a la funcion para cargar los datos en la matriz
                                posX+=16;
                                posXmax=posX;
                            }
                            posX=48;
                            displaySection(posX, posY, posXmax, posYmax); //mostrar en 25
                        break;
                    }
                } else if(currentGameTime-lastGameTime<=6*timeOut){
                    posX=48;
                    posY=15;
                    posYmax=23;
                    for(i=0;i<=4;i++){
                        loadLetters(lost[i], 0, 0, posX, posY); //llamamos a la funcion para cargar los datos en la matriz
                        posX+=16;
                        posXmax=posX;
                    }
                    posX=48;
                    displaySection(posX, posY, posXmax, posYmax); //mostrar en 25
                } else{
                    lastGameTime=currentGameTime;
                    cont++;
                }
            } else{
                gameStates=GAME_START;
            }
        break;
        default:
            gameStates=GAME_START;
        break;
    }
}

void morseCode(){
    static unsigned short j, k;
    static int i;
    unsigned char pos;
    static char mode = 0;

    if(control.flag4){ //ejecucion al entrar por primera vez
        j=0;
        k=0;
        control.flag4=0;
        for(i=0;i<256;i++) //limpiamos todas las posiciones del vector utilizado en el morse
            editor[i]='\0';
    }

    if(mode){
        i=toupper(editor[k])-'0'; //devuelve un numero
        pos=morse[i][j]; //pos -> determina puntos y rayas de las letras

        switch(editor[k]){
        case ' ':
            currentGameTime=clock();
            if((currentGameTime-lastGameTime)<=timeOut*12){ //Lo hago hasta 12 porque al final de cada caracter dejo siempre 300 milisegundos, y quiero llegar a un total de 1,5 segundos
                loadLetters(219, 0, 0, 72, 16);
                displaySection(72,16, 88, 24); //mostrar en 36 //muestreo utilizado para gotoxy, en este cado mismo valor que posX
            }
            else{
                lastGameTime=currentGameTime;
                k++;
            }
        break;
        case NULL:
            currentGameTime=clock();
            if((currentGameTime-lastGameTime)<=timeOut*27){ //Lo hago hasta 27 porque al final de cada caracter dejo siempre 300 milisegundos, y quiero llegar a un total de 3 segundos
                loadLetters(219, 0, 0, 72, 16);
                displaySection(72,16, 88, 24); //mostrar en 36 //muestreo utilizado para gotoxy, en este cado mismo valor que posX
            }
            else{
                lastGameTime=currentGameTime;
                k++;
            }
        break;
        default:
            switch(pos){
                case 'P':
                    currentGameTime=clock();
                    if((currentGameTime-lastGameTime)<=timeOut*3){ //dark
                        loadLetters(219, 6, 6, 72, 16);
                        displaySection(72,16, 88, 24); //mostrar en 36       //muestreo utilizado para gotoxy, en este cado mismo valor que posX
                    } else if (((currentGameTime-lastGameTime)>timeOut*3)&&((currentGameTime-lastGameTime)<=timeOut*6)){
                        loadLetters(219, 0, 0, 72, 16);
                        displaySection(72,16, 88, 24); //mostrar en 36
                    } else{
                        lastGameTime=currentGameTime;
                        j++;
                    }
                break;
                case 'R':
                case '\0': //entre letras hay un caracter \0
                    if((pos==NULL)&&((editor[k+1]==NULL) || (editor[k+1]==' '))){
                        k++;
                        j=0;
                        break;
                    } else{
                        currentGameTime=clock();
                        if((currentGameTime-lastGameTime)<=timeOut*9){
                            loadLetters(219, 6, 6, 72, 16);
                            displaySection(72,16, 88, 24); //mostrar en 36       //muestreo utilizado para gotoxy, en este cado mismo valor que posX
                        } else if (((currentGameTime-lastGameTime)>timeOut*9)&&((currentGameTime-lastGameTime)<=timeOut*12)){
                            loadLetters(219, 0, 0, 72, 16);
                            displaySection(72,16, 88, 24); //mostrar en 36
                        } else{
                            lastGameTime=currentGameTime;
                            if(pos==NULL){
                                k++;
                                j=0;
                            } else {
                                j++;
                            }

                        }
                    }
                break;
            }
        break;
        }
        if(k-1==strlen(editor)){
            k=0;
            j=0;
            i=0;
            lastGameTime=currentGameTime;
        }
    }

    switch(opt){
        case F2:
            if(mode==0){
                clearDisplay(0,0,40,160,1);
                mode=1;
                lastGameTime = clock(); //tomamos el tiempo luego de F2 para que no se tenga en cuenta el tiempo de escritura
            } else{
                clearDisplay(0,0,40,160,1);
                mode=0;
                for(i=strlen(editor);i>=0;i--){ //limpiamos el editor
                    editor[i]='\0';
                }
            }
            j=i=k=0;
        break;
        case DEL: //borramos el caracter a la derecha del cursor
            for(i=j;i<strlen(editor);i++)
                editor[i]=editor[i+1];
        break;
        case BACKSPACE: //borramos el caracter a la izquierda del cursor
            for(i=j-1;i<strlen(editor);i++)
                editor[i]=editor[i+1];
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
            if(k<16 && editor[j]!='\0')
                k++;
            if(j<256 && j<strlen(editor))
                j++;
        break;
        default:
            if((isalnum(opt)!=0 || opt==' ') && (!mode)){ //isascii devuelve 0 si el caracter no es ascii
                    if(editor[j]!='\0'){ //usado cuando queremos cargar caracteres en una posicion donde ya habia
                        for(i=sizeof(editor);i>=j;i--){
                            editor[i]=editor[i-1];
                        }
                        editor[j]=opt;
                        j++;
                    } else{
                        editor[j]=opt;
                        j++;
                    }
                if(k<16)//movemos el cursor
                    k++;
            }
        break;
    }

    if(!mode){
        //BLACK: 0 BLUE: 1 GREEN: 2 CYAN: 3 RED: 4 MAGENTA: 5 YELLOW: 6 WHITE: 7
        textbackground(BLACK);
        if(opt!='\0'){
            gotoxy(60,45);
            if(j<16){
                for(i=0;i<16;i++){
                    if(editor[i]!='\0'){
                        if(i==j){
                            textbackground(5);
                        } else
                            textbackground(2);
                        textcolor(7);
                        cprintf("%c", editor[i]);
                    }
                    else{
                        if(i==j){
                            textbackground(5);
                            textcolor(5);
                        }
                        else{
                            textbackground(2);
                            textcolor(2);
                        }
                        cprintf("G");
                    }
                }
            }
            else{ //muestra los datos cuando tenemos mas de 16 caracteres
                for(i=j-16;i<j;i++){
                    if(editor[i]!='\0'){
                        if(i==j-1){
                            textbackground(5);
                        } else
                            textbackground(2);
                        textcolor(7);
                        cprintf("%c", editor[i]);
                    }
                }
        }
        textbackground(BLACK);
        }

        gotoxy(76,45);
        if(editor[j-17]!='\0' && j>16) //mostramos flechas izquierdas, -17 porque se tiene en cuenta la posicion 0
            printf("%c", 174);
        else
            printf(" ");

        if(editor[16]!='\0' && editor[j]!='\0') //mostramos flechas derechas
            printf("%c\n", 175);
        else
            printf(" \n");
    }
}

void led(){
    int i,j,k=0;
    for(i=0;i<2;i++){
        for(j=0;j<4;j=j+2){
            if(control.flag2){
                display[i][j] = 254;
                display[i][j+1]=(2&0x0F)|(2<<4); //cargamos en el display el color de fondo
                gotoxy(1,1);
            } else{
                clearDisplay(0,0,2,4,0);
                display[i][j] = ' ';
            }
        }
    }
    for(i=0;i<2;i++){
        for(j=0;j<4;j=j+2){
            k++;
            textcolor((0xF0&display[i][j+1])>>4); //0xF0&display[i][j+1]
            textbackground(0x0F&display[i][j+1]);
            gotoxy(k,i+1);
            cprintf("%c", display[i][j]);
        }
        k=0;
    }
}
/* END Function prototypes user code ------------------------------------------*/

int main(){
/* Local variables -----------------------------------------------------------*/
    char mode=1;
    int digitalTimer, analogTimer, memoryGameTimer;

    //int digitalTimer, analogTimer, memoryGameTimer, morseTimer;
    clock_t currentTime, lastTime;
    control.flag2=0;
    control.flag3=0;
    control.flag4=0;

    digitalTimer=TimerAdd();
    TimerConnect(digitalTimer,digitalClock);

    analogTimer=TimerAdd();
    TimerConnect(analogTimer,analogClock);

    memoryGameTimer=TimerAdd();
    TimerConnect(memoryGameTimer,memoryGame);
/* END Local variables -------------------------------------------------------*/

/* User code -----------------------------------------------------------------*/
    textmode(C4350); //definimos el display de 40X80
    _setcursortype(_NOCURSOR); //quitamos el cursor
    lastTime = clock(); //tomamos el valor de linicio para luego comparlo al final del codigo
    createDisplay(&display[0][0], 160, 40); //creamos el display
    randomize(); //ejecutamos randomize para que se generen numeros aleatorios distintos

    while(1){
        opt = '\0';
        if(kbhit()){
            if((opt = getch()) == 0)
                opt = getch() + 1000;
            if(opt == ESC)
                break;
        }

        if(opt==F1){
            switch(mode){
                case 1: //cambiamos del reloj digital al reloj analogico
                    mode=2;
                    TimerStop(digitalTimer);
                    clearDisplay(0,0,40,160,1);
                    lastTime = clock();
                break;
                case 2: //cambiamos del reloj analogico al juego de la memoria
                    mode=3;
                    TimerStop(analogTimer);
                    clearDisplay(0,0,40,160,1);
                    lastTime = clock();
                break;
                case 3: //cambiamos del juego de la memoria al morse
                    mode=4;
                    control.flag4=1; //variable utilizada para controlar el cursor del editor
                    TimerStop(memoryGameTimer);
                    clearDisplay(0,0,40,160,1);
                    lastTime = clock();
                break;
                case 4: //cambiamos del morse al reloj digital
                    mode=1;
                    clearDisplay(0,0,40,160,1);
                    lastTime = clock();
                break;
            }
        }

        currentTime=clock();
        if((currentTime-lastTime) >= timeOut*20) //si se cumplen 2 segundos actualizamos lastTime
            lastTime = clock();

        switch(mode){
            case 1:
                if((currentTime-lastTime)>timeOut)
                    control.flag2=0;
                else
                    control.flag2=1;
                led();

                clearDisplay(15,16,23,144,0);
                TimerStart(digitalTimer,500,PERIODIC);
            break;
            case 2:
                if((((currentTime-lastTime)>timeOut)&&((currentTime-lastTime)<2*timeOut))||(currentTime-lastTime)>3*timeOut) //apagado
                    control.flag2=0;
                else{
                    control.flag2=1;
                }
                led();

                clearDisplay(6,6,40,160,0);
                TimerStart(analogTimer,200,PERIODIC);
            break;
            case 3:
                if((((currentTime-lastTime)>3*timeOut)&&((currentTime-lastTime)<4*timeOut))||(currentTime-lastTime)>5*timeOut) //apagado
                    control.flag2=0;
                else
                    control.flag2=1;
                led();

                clearDisplay(0,0,40,160,0);
                TimerStart(memoryGameTimer,10,PERIODIC);
            break;
            case 4:
                if((((currentTime-lastTime)>3*timeOut)&&((currentTime-lastTime)<4*timeOut))||(((currentTime-lastTime)>5*timeOut)&&((currentTime-lastTime)<6*timeOut))||((currentTime-lastTime)>7*timeOut)) //apagado
                    control.flag2=0;
                else
                    control.flag2=1;
                led();

                clearDisplay(16,72,24,88,0);
                morseCode();
            break;
        }

        gotoxy(5, 45);
        time(&myTime);
        myTm = localtime(&myTime);
        if(mode!=1)
            printf("%0.2d/%0.2d/%4d - %0.2d:%0.2d:%0.2d", myTm->tm_mday, myTm->tm_mon+1, myTm->tm_year+1900,myTm->tm_hour, myTm->tm_min, myTm->tm_sec); //utilizado para imprimir la hora}
        else
            printf("                                                    ");
        TickerTask(); //parte del ticker
    }
/* END User code -------------------------------------------------------------*/
   return 0;
}

