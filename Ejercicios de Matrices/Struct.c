/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <conio.h>
/* END Includes --------------------------------------------------------------*/

/* typedef -------------------------------------------------------------------*/
typedef struct{
    int id;
    char name[80];
    char phone[16];
}sItemAgenda;
/* END typedef ---------------------------------------------------------------*/

/* define --------------------------------------------------------------------*/
#define F1 1059 //tecla f1 
#define F2 1060 //tecla f2
#define F3 1061 //tecla f3
#define LEFT 1075 //izquierda
#define RIGHT 1077 //derecha
#define ENTER 13 //tecla enter
#define ESC 27 //tecla ESC
/* END define ----------------------------------------------------------------*/

int main(){
/* Local variables -----------------------------------------------------------*/
    int opt, pos, emp;
    unsigned char i = 0;
    int tempId = 0;
    char tempName[80] = {};
    char tempPhone[80] = {};
     //agenda es de tipo sItemAgenda
    sItemAgenda agenda[10] = {0};
    pos = 0; //utilizado para manipular la posicion actual
/* END Local variables -------------------------------------------------------*/
/* User code -----------------------------------------------------------------*/
    while (1){
        emp = 0; //utilizado para encontrar que posiciones estan vacias
        clrscr();
        //menu ingresar mas strings buscar strings salir
        //printf("Presione ESC para salir\n");
         //inicializarla
        for(i=0;i<10;i++) 
            if(agenda[i].name[0] == '\0')
                emp++;
        
        //printf("POSITION %i", pos+1);
        if(pos!=0) //mostrar flacha izquierda
            printf("<\t");
        else
            printf(" \t"); //usado para colocar las tabulaciones cuando no se imprime la flecha izquierda
            
        if(agenda[pos].id == 0) //imprimimos el valor del id dependiendo del valor que tenga
            printf ("\t          ");
        else           
            printf("\t%10i", agenda[pos].id);
            
        printf("\t%80s\t", agenda[pos].name);
        printf("\t%16s\t", agenda[pos].phone);
        
        if(pos!=9){ //imprimimos la flecha derecha
            printf("\t>\n");
            _setcursortype(_NOCURSOR); //ocultar el cursor 
        }
        else
            printf("\t \n");
            
        printf("\t\t\tF1. Ingresar elementos\t\t\t");
        printf("F2. Borrar elementos\t\t\t");
        printf("F3. Mostrar elementos\n");    

        if(emp == 10){
            /*
            */
            printf("\t\t\t\t\t\t\t\t    AGENDA VACIA\n");
        }        

        opt = getch();
        
        if(opt==0)
            opt=getch()+1000;
        if(opt==ESC)
            break;

        switch(opt){
            case F1: //ingresar datos agenda
                clrscr();
                if(agenda[pos].name[0]=='\0'){
                    printf("Ingrese el ID\n");
                    scanf("%i%*c",&agenda[pos].id); 
                    //%*c sirve para no permitir que el enter se guarde en name
                    printf("Ingrese el Nombre\n");
                    gets(agenda[pos].name);
                    printf("Ingrese el Numero Telefonico\n");
                    gets(agenda[pos].phone);
                }
            break;
            case F2: //eliminar elementos
                clrscr();
                agenda[pos].id = 0;
                strcpy(agenda[pos].name,"\0");
                strcpy(agenda[pos].phone,"\0");
            break;
            case F3: //modificar un elemento
                clrscr();
                printf("Ingrese el ID\n");
                scanf("%i%*c",&tempId); 
                //%*c sirve para no permitir que el enter se guarde en name
                printf("Ingrese el Nombre\n");
                gets(tempName);
                printf("Ingrese el Numero Telefonico\n");
                gets(tempPhone);
            
                printf("Confirmar los cambios"); //confirmar cambios
                while(1){ // para que salga solamente si se presiona ESC
                    opt = getch(); //pedimos datos
                    if(opt == ENTER){
                        agenda[pos].id = tempId;
                        strcpy(agenda[pos].name, tempName);
                        strcpy(agenda[pos].phone, tempPhone);
                        break;
                    }
                    if(opt == ESC)
                        break;
                }
            break;
            case LEFT:
                //clrscr();
                if(pos>0)
                    pos--;
            break;
            case RIGHT:
                //clrscr();
                if(pos<9)
                    pos++;
            break;
        }
    }
/* END User code -------------------------------------------------------------*/
   return 0;
}
