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
//macro siempre en mayusculas y separar con tabulacion
#define UP      1072
#define DOWN    1080
#define RIGHT   1077
#define LEFT    1075
//tablero
#define SIZE    8

/* END define ----------------------------------------------------------------*/

/* Function prototypes -------------------------------------------------------*/

/* END Function prototypes ---------------------------------------------------*/

/* Global variables ----------------------------------------------------------*/

/* END Global variables ------------------------------------------------------*/

/* Fuction prototypes user code ----------------------------------------------*/

/* END Fuction prototypes user code ------------------------------------------*/

int main(){
/* Local variables -----------------------------------------------------------*/
    //variables tablero
    int rowt, colt, num, i;
    //variables de posicion
    int key,col,row;
    int cont = 1;
    char piece,rowl;    
/* END Local variables -------------------------------------------------------*/


/* User code -----------------------------------------------------------------*/
    //inicializamos variables
    col = 1;
    row = 1;
    piece = '*'; 
    
    while(1){
        //mostramos tablero al principio   
        if(cont==1 || key==UP || key==DOWN || key==RIGHT || key==LEFT || key=='C' || key=='T' || key=='A' || key=='R' || key=='c' || key=='t' || key=='a' || key=='r'){          
            clrscr();                
            //utilizado para el manejo de teclas de movimiento 
            printf("              TABLERO DE AJEDREZ               \n\n\r");
            num = 8;
            printf("     A    B    C    D    E    F    G    H\n");
                    
            for (colt = 1; colt <= SIZE; colt++) { //controla la fila
                for(i=0;i<3;i++){ //repetimos 3 veces la fila para lograr 3 de altura                            
                    //imprimimos numeros de las filas a la izquierda
                    if(i==1)
                        printf(" %i ", num);
                    else
                        printf("   ");                             
                    //imprimimos las filas
                    for (rowt = 1; rowt <= SIZE; rowt++) { //5 caracteres de ancho por 3 de alto      
                    
                        if ((rowt + colt) % 2 == 0) { // casillas blancas
                            textbackground(7);
                            textcolor(7);
                            cprintf("GGGGG");
                        }
                        else{ //casillas negras
                            textbackground(2);
                            textcolor(2);
                            cprintf("GGGGG");                          
                        }
                    }
                    //imprimimos numeros de las filas a la derecha
                    if(i==1)
                        printf(" %i ", num);
                                
                    printf("\n"); //para organizar las casillas 
                    //Usé un getch() para testear si la casilla tenia 3 caracteres de alto
                    //getch();
                }
                num--; 
                if(i==2)      
                printf("\n"); // imprimir salto de línea al final de cada fila
            }

            switch(row){
                case 1:
                    rowl = 'A';
                break;
                case 2:
                    rowl = 'B';
                break;
                case 3:
                    rowl = 'C';
                break;
                case 4:
                    rowl = 'D';
                break;
                case 5:
                    rowl = 'E';
                break;
                case 6:
                    rowl = 'F';
                break;
                case 7:
                    rowl = 'G';
                break;
                case 8:
                    rowl = 'H';
                break;
                }
                                
            printf("     A    B    C    D    E    F    G    H\n");
            printf("\tPieza: %c\t Posicion: %c%i",piece,rowl,col);
            textbackground(0);                  
        } //cierre if - primer tablero
    
        //seccion de opciones
        key = getch();

        if(key==0)
            key=getch()+1000;  
        if(key == 27)
            break;
        
            switch(key){
                case UP: //mover hacia arriba
                    //clrscr();
                    //printf("Tecla Arriba");
                    if(col==8){
                        col=1;
                        break;
                    }
                    if(col>0 && col<=7) //row<=7 debido a que sino se va fuera del tablero
                        col++;                
                break;
                case DOWN: //mover hacia abajo
                    //clrscr();
                    //printf("Tecla Abajo");
                    if(col==1){
                        col=8;
                        break;
                    }
                    if(col>=2 && col<=8) //row>=2 debido a que sino se va fuera del tablero
                        col--;              
                break;
                case RIGHT: //mover a la derecha
                    //clrscr();
                    //printf("Tecla Derecha");
                    if(row==8){
                        row=1;
                        break;
                    }
                    if(row>0 && row<=7)
                    row++;
                break;
                case LEFT: //mover a la izquierda
                    //clrscr();
                    //printf("Tecla Izquierda");
                    if(row==1){
                        row=8;
                        break;
                    }
                    if(row>=2 && row<=8)
                        row--;
                break;
                case 'A': //elegir el alfil
                case 'a':               
                    piece = 'A';
                break;
                case 'T': //elegir la torre
                case 't':               
                    piece = 'T';
                break;
                case 'R': //elegir la reina
                case 'r':             
                    piece = 'R';
                break;
                case 'C': //elegir el caballo
                case 'c': 
                    piece = 'C';     
                break;
                case 13:
                    switch (piece){
                        case 'A': //mostramos el alfil
                            clrscr();
                            printf("              TABLERO DE AJEDREZ               \n\n\r");
                            num = 8;
                            printf("     A    B    C    D    E    F    G    H\n");
                            for (colt = 1; colt <= SIZE; colt++) { //controla la fila
                                for(i=0;i<3;i++){ //repetimos 3 veces la fila para lograr 3 de altura
                                    
                                    //imprimimos numeros de las filas a la izquierda
                                    if(i==1)
                                        printf(" %i ", num);
                                    else
                                        printf("   "); 
                                    
                                    //imprimimos las filas
                                    for (rowt = 1; rowt <= SIZE; rowt++) { //5 caracteres de ancho por 3 de alto      
                                        
                                        if(rowt==row && 9-colt==col){ //lugar de la pieza
                                            textbackground(4);
                                            textcolor(4);
                                            cprintf("GGGGG");
                                        }else{ //posibles movimientos
                                            if((rowt-row==(9-colt)-col)||(rowt-row==-(9-colt)+col)){
                                                textbackground(6);
                                                textcolor(6);
                                                cprintf("GGGGG");
                                            }else{
                                                if ((rowt + colt) % 2 == 0) { // casillas blancas
                                                    textbackground(7);
                                                    textcolor(7);
                                                    cprintf("GGGGG");
                                                }
                                                else{ //casillas negras
                                                    textbackground(2);
                                                    textcolor(2);
                                                    cprintf("GGGGG");                          
                                                }
                                            }                    
                                        }
                                    }
                                    //imprimimos numeros de las filas a la derecha
                                    if(i==1)
                                        printf(" %i ", num);
                                        
                                    printf("\n"); //para organizar las casillas 
                                    //Usé un getch() para testear si la casilla tenia 3 caracteres de alto
                                    //getch();
                                }
                                num--; 
                                if(i==2)      
                                    printf("\n"); // imprimir salto de línea al final de cada fila
                            }
                            
                            printf("     A    B    C    D    E    F    G    H\n");                           
                            
                            switch(row){
                                case 1:
                                    rowl = 'A';
                                break;
                                case 2:
                                    rowl = 'B';
                                break;
                                case 3:
                                    rowl = 'C';
                                break;
                                case 4:
                                    rowl = 'D';
                                break;
                                case 5:
                                    rowl = 'E';
                                break;
                                case 6:
                                    rowl = 'F';
                                break;
                                case 7:
                                    rowl = 'G';
                                break;
                                case 8:
                                    rowl = 'H';
                                break;
                            }                  

                            printf("\tPieza: %c\t Posicion: %c%i",piece,rowl,col);    
                            textbackground(0); 
                        break;
                        case 'T': //mostramos la torre
                            clrscr();
                            printf("              TABLERO DE AJEDREZ               \n\n\r");
                            num = 8;
                            printf("     A    B    C    D    E    F    G    H\n");
                            
                            for (colt = 1; colt <= SIZE; colt++) { //controla la fila
                                for(i=0;i<3;i++){ //repetimos 3 veces la fila para lograr 3 de altura
                                    
                                    //imprimimos numeros de las filas a la izquierda
                                    if(i==1)
                                        printf(" %i ", num);
                                    else
                                        printf("   "); 
                                    
                                    //imprimimos las filas
                                    for (rowt = 1; rowt <= SIZE; rowt++) { //5 caracteres de ancho por 3 de alto      
                                        
                                        if(rowt==row && 9-colt==col){ //lugar de la pieza
                                            textbackground(4);
                                            textcolor(4);
                                            cprintf("GGGGG");
                                        }else{ //posibles movimientos
                                            if((rowt==row)||(9-colt==col)){ 
                                                textbackground(6);
                                                textcolor(6);
                                                cprintf("GGGGG");
                                            }else{
                                                if ((rowt + colt) % 2 == 0) { // casillas blancas
                                                    textbackground(7);
                                                    textcolor(7);
                                                    cprintf("GGGGG");
                                                }
                                                else{ //casillas negras
                                                    textbackground(2);
                                                    textcolor(2);
                                                    cprintf("GGGGG");                          
                                                }
                                            }                    
                                        }
                                    }
                                    //imprimimos numeros de las filas a la derecha
                                    if(i==1)
                                        printf(" %i ", num);
                                        
                                    printf("\n"); //para organizar las casillas 
                                    //Usé un getch() para testear si la casilla tenia 3 caracteres de alto
                                    //getch();
                                }
                                num--; 
                                if(i==2)      
                                    printf("\n"); // imprimir salto de línea al final de cada fila
                            }
                            
                            printf("     A    B    C    D    E    F    G    H\n");
                            
                            switch(row){
                                case 1:
                                    rowl = 'A';
                                break;
                                case 2:
                                    rowl = 'B';
                                break;
                                case 3:
                                    rowl = 'C';
                                break;
                                case 4:
                                    rowl = 'D';
                                break;
                                case 5:
                                    rowl = 'E';
                                break;
                                case 6:
                                    rowl = 'F';
                                break;
                                case 7:
                                    rowl = 'G';
                                break;
                                case 8:
                                    rowl = 'H';
                                break;
                            }                  

                            printf("\tPieza: %c\t Posicion: %c%i",piece,rowl,col);      
                            textbackground(0); 
                        break;
                        case 'C': //mostramos el caballo
                            clrscr();
                            printf("              TABLERO DE AJEDREZ               \n\n\r");
                            num = 8;
                            printf("     A    B    C    D    E    F    G    H\n");
                            
                            for (colt = 1; colt <= SIZE; colt++) { //controla la fila
                                for(i=0;i<3;i++){ //repetimos 3 veces la fila para lograr 3 de altura
                                    
                                    //imprimimos numeros de las filas a la izquierda
                                    if(i==1)
                                        printf(" %i ", num);
                                    else
                                        printf("   "); 
                                    
                                    //imprimimos las filas
                                    for (rowt = 1; rowt <= SIZE; rowt++) { //5 caracteres de ancho por 3 de alto      
                                        
                                        if(rowt==row && 9-colt==col){ //lugar de la pieza
                                            textbackground(4);
                                            textcolor(4);
                                            cprintf("GGGGG");
                                        }else{ //posibles movimientos
                                            if(((rowt==row-2)&&(9-colt==col-1))||((rowt==row-2)&&(9-colt==col+1))||((rowt==row-1)&&(9-colt==col-2))||((rowt==row+1)&&(9-colt==col-2))||((rowt==row+2)&&(9-colt==col-1))||((rowt==row+2)&&(9-colt==col+1))||((rowt==row-2)&&(9-colt==col-1))||((rowt==row-2)&&(9-colt==col+1))||((rowt==row-1)&&(9-colt==col-2))||((rowt==row-1)&&(9-colt==col+2))||((rowt==row+1)&&(9-colt==col+2))){
                                                textbackground(6);
                                                textcolor(6);
                                                cprintf("GGGGG");
                                            }else{
                                                if ((rowt + colt) % 2 == 0) { // casillas blancas
                                                    textbackground(7);
                                                    textcolor(7);
                                                    cprintf("GGGGG");
                                                }
                                                else{ //casillas negras
                                                    textbackground(2);
                                                    textcolor(2);
                                                    cprintf("GGGGG");                          
                                                }
                                            }                    
                                        }
                                    }
                                    //imprimimos numeros de las filas a la derecha
                                    if(i==1)
                                        printf(" %i ", num);
                                        
                                    printf("\n"); //para organizar las casillas 
                                    //Usé un getch() para testear si la casilla tenia 3 caracteres de alto
                                    //getch();
                                }
                                num--; 
                                if(i==2)      
                                    printf("\n"); // imprimir salto de línea al final de cada fila
                            }
                            
                            printf("     A    B    C    D    E    F    G    H\n");
                            
                            switch(row){
                                case 1:
                                    rowl = 'A';
                                break;
                                case 2:
                                    rowl = 'B';
                                break;
                                case 3:
                                    rowl = 'C';
                                break;
                                case 4:
                                    rowl = 'D';
                                break;
                                case 5:
                                    rowl = 'E';
                                break;
                                case 6:
                                    rowl = 'F';
                                break;
                                case 7:
                                    rowl = 'G';
                                break;
                                case 8:
                                    rowl = 'H';
                                break;
                            }                  

                            printf("\tPieza: %c\t Posicion: %c%i",piece,rowl,col);    
                            textbackground(0);
                        break;
                        case 'R': //mostramos la reina                  
                            clrscr();
                            printf("              TABLERO DE AJEDREZ               \n\n\r");
                            num = 8;
                            printf("     A    B    C    D    E    F    G    H\n");
                            
                            for (colt = 1; colt <= SIZE; colt++) { //controla la fila
                                for(i=0;i<3;i++){ //repetimos 3 veces la fila para lograr 3 de altura
                                    
                                    //imprimimos numeros de las filas a la izquierda
                                    if(i==1)
                                        printf(" %i ", num);
                                    else
                                        printf("   "); 
                                    
                                    //imprimimos las filas
                                    for (rowt = 1; rowt <= SIZE; rowt++) { //5 caracteres de ancho por 3 de alto      
                                        
                                        if(rowt==row && 9-colt==col){ //lugar de la pieza
                                            textbackground(4);
                                            textcolor(4);
                                            cprintf("GGGGG");
                                        }else{ //posibles movimientos
                                            if((rowt-row==(9-colt)-col)||(rowt-row==-(9-colt)+col)||(rowt==row)||(9-colt==col)){
                                                textbackground(6);
                                                textcolor(6);
                                                cprintf("GGGGG");
                                            }else{
                                                if ((rowt + colt) % 2 == 0) { // casillas blancas
                                                    textbackground(7);
                                                    textcolor(7);
                                                    cprintf("GGGGG");
                                                }
                                                else{ //casillas negras
                                                    textbackground(2);
                                                    textcolor(2);
                                                    cprintf("GGGGG");                          
                                                }
                                            }                    
                                        }
                                    }
                                    //imprimimos numeros de las filas a la derecha
                                    if(i==1)
                                        printf(" %i ", num);
                                        
                                    printf("\n"); //para organizar las casillas 
                                    //Usé un getch() para testear si la casilla tenia 3 caracteres de alto
                                    //getch();
                                }
                                num--; 
                                if(i==2)      
                                    printf("\n"); // imprimir salto de línea al final de cada fila
                            }
                            
                            printf("     A    B    C    D    E    F    G    H\n");
                            
                            switch(row){
                                case 1:
                                    rowl = 'A';
                                break;
                                case 2:
                                    rowl = 'B';
                                break;
                                case 3:
                                    rowl = 'C';
                                break;
                                case 4:
                                    rowl = 'D';
                                break;
                                case 5:
                                    rowl = 'E';
                                break;
                                case 6:
                                    rowl = 'F';
                                break;
                                case 7:
                                    rowl = 'G';
                                break;
                                case 8:
                                    rowl = 'H';
                                break;
                            }                  

                            printf("\tPieza: %c\t Posicion: %c%i",piece,rowl,col);  
                            textbackground(0);
                        break;                
                    } //final switch(piece)         
                break;
            }//final main switch
        cont=0;      
    }
/* END User code -------------------------------------------------------------*/
   return 0;
}
