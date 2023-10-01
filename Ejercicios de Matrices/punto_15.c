/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <conio.h>
/* END Includes --------------------------------------------------------------*/

/* typedef -------------------------------------------------------------------*/
typedef struct{
    int id;
    char nombre[80];
    char tel[16];
}sItemAgenda
/* END typedef ---------------------------------------------------------------*/

/* define --------------------------------------------------------------------*/
#define F1 1059 //tecla f1 
#define F2 1060 //tecla f2
#define F3 1061 //tecla f3
#define LEFT 1075 //izquierda
#define RIGHT 1077 //derecha
#define ENTER 13 //tecla enter
/* END define ----------------------------------------------------------------*/

int main(){
/* Local variables -----------------------------------------------------------*/
    unsigned char i = 0;
    sItemAgenda Agenda[10];
/* END Local variables -------------------------------------------------------*/
/* User code -----------------------------------------------------------------*/
    while (1){
        clrscr();
        //menu ingresar mas strings buscar strings salir
        printf("MENU\n");
        printf("1. Ingresar elementos\n");
        printf("2. Borrar elementos\n");
        printf("3. Mostrar elementos\n");
        printf("Presione ESC para salir\n");
        
        if(Agenda[10] == '\0')
            pritnf("La agenda esta vacia\n");        
        
        if(opt==0)
            opt=getch()+1000;
        if(opt==27)
            break;
        
        //scanf("%i", &opt);
        opt = getch();
        //con fin dejas de escribir y con escape salis del programa

        switch(opt){
            case F1: //ingresar datos agenda
                clrscr();
                for(i=0;)
            break;
            case F2: //mostrar elementos
                clrscr();

            break;
            case F3: //eliminar un elemento
                clrscr();

            break;
            case LEFT:

            break;
            case RIGHT:
            
            break;
            case ENTER: //usado para modificar
                
            break;
        }
    }
/* END User code -------------------------------------------------------------*/
   return 0;
}
