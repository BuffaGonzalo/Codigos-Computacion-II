/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
/* END Includes --------------------------------------------------------------*/

/* typedef -------------------------------------------------------------------*/
typedef struct{
    unsigned int id;
    char name[80];
    char phone[16];
    char address[80];
}sItemAgenda;

typedef struct{
    unsigned char flag1:1;
    unsigned char flag2:1;
    unsigned char flag3:1;
    unsigned char flag4:1;
    unsigned char flag5:1;
    unsigned char flag6:1;
    unsigned char flag7:1;
    unsigned char flag8:1;
}bitField;
/* END typedef ---------------------------------------------------------------*/

/* define --------------------------------------------------------------------*/
#define INS         1082
#define DEL         1083
#define F1          1059
#define F2          1060
#define LEFT        1075
#define RIGHT       1077
#define ENTER       13
#define BACKSPACE   8
#define ESC         27
/* END define ----------------------------------------------------------------*/

int main(){
/* Local variables -----------------------------------------------------------*/
    short opt, pos=0, posMax=0, emp, temp=0; //pos - valor de las flechas, posicion actual & emp - usado para saber si esta vacio
    unsigned short i=0, j=0, k=0;
    char editorData[256] = {};
    sItemAgenda agenda[10] = {};//agenda es de tipo sItemAgenda
    sItemAgenda *pointer; //declaramos el puntero del mismo tipo que la agenda
    bitField control;
/* END Local variables -------------------------------------------------------*/
/* User code -----------------------------------------------------------------*/
    while (1){
        clrscr();
        emp = 0; //utilizado para encontrar que posiciones estan vacias
        control.flag6=0;

        for(i=0;i<10;i++) //revisamos si esta vacia la agenda
            if(agenda[i].id == 0)
                emp++;

        textcolor(RED); //cambiamos el color e los caracteres
        cprintf("ACTIVIDAD CADENA");
        if(emp<10 && emp>0)
            cprintf("  POS: %i   ", pos+1);
        else if (emp==10)
            cprintf("  AGENDA VACIA");
        else
            cprintf(" AGENDA LLENA");

        textcolor(WHITE); //volvemos al color blanco
        printf("\nINS. Agregar elemento\n");
        printf("DEL. Borrar elemento\n");
        printf("F1. Editar elemento\n");
        printf("F2. Buscar elemento\n");

        if(emp != 10){  //imprimimos los datos
            printf("\nDatos\t");
            if(emp<9){ //mostramos cuando hay mas de un elemento
                for(i=pos;i>0;i--){
                    if(agenda[i-1].id!=0){ //mostramos flechas superiores izquierdas, pos comienza en 0 va de (0 a 9)y controlamos que la siguinete no este vacia
                        printf("<");
                        i=0;
                        control.flag6=1;
                        break;
                    }

                }

                if(!control.flag6){
                    printf(" ");
                    control.flag6=0;
                }

                for(i=pos;i<10;i++){
                    if(agenda[i+1].id!=0){ //mostramos flechas superiores izquierdas, pos comienza en 0 va de (0 a 9)y controlamos que la siguinete no este vacia
                        printf(">");
                        i=10;
                        break;
                    }
                }
            }
            printf("\nID: %i\n", agenda[pos].id);
            printf("Nombre: %s\n", agenda[pos].name);
            printf("Telefono: %s\n", agenda[pos].phone);
            printf("Direccion: %s\n", agenda[pos].address);
        }

        gotoxy(1,14); //debe comenzar en 1, la posicion 0 no existe
        printf("EDITOR");
        if(opt!=F1){ //mostramos el cursor en rojo
            gotoxy(1,15);
            textcolor(RED);
            textbackground(RED);
            cprintf("RRRRRRRRRRRRRRRR");
            textcolor(WHITE);
            textbackground(BLACK);
            _setcursortype(0);
        }

        opt = getch();
        if(opt==0)
            opt=getch()+1000;
        if(opt==ESC)
            break;

        switch(opt){ // switch principal
            case INS: //ingresar datos agenda
            case F1: //modificar
            case F2: //buscar
                if((opt==INS && emp>0) || opt==F1 || opt==F2){
                    _setcursortype(1);
                    control.flag1=0;
                    control.flag2=0;
                    control.flag3=0;
                    control.flag4=0;
                    control.flag5=0;
                    j=0;
                    k=0;
                    i=0;

                    if(opt==INS){ //utilizado para imprimir en la primera posicion vacia
                        while(i<10){ //guardamos el valor de la primera posicion vacia
                            if(agenda[i].id==0){
                                pos=i;
                                break;
                            }
                            i++;
                        }
                    }

                    if(opt==F2)
                        control.flag5=1; //bandera que activa las secciones de busqueda

                    if(pos>=posMax) //comparamos para guardar la posicion mayor
                        posMax=pos;

                    pointer = agenda; //igualamos el puntero a la direccion en memoria del primer elemento del array
                    pointer += pos; //realizamos aritmetica de punteros para ir a la posicion deseada

                    for(i=0;i<256;i++) //limpiamos todas las posiciones asignanado \0
                        editorData[i]='\0';

                    while(1){
                        gotoxy(1,14);

                        if(!control.flag1 && !control.flag5){ //si son distintos de F2 y las respectivas banderas
                            printf("EDITOR - NOMBRE ");
                        } else if(control.flag2 && opt!=F2){
                            printf("EDITOR - TELEFONO ");
                        }  else if(control.flag3 && opt!=F2){
                            printf("EDITOR - DIRECCION ");
                        }

                        if(control.flag5) //si se presiona el F2
                            printf("EDITOR - BUSQUEDA ");

                        if(editorData[j-17]!='\0' && j>16) //mostramos flechas izquierdas, -17 porque se tiene en cuenta la posicion 0
                            printf("%c", 174);
                        else
                            printf(" ");

                        if(editorData[16]!='\0' && editorData[j]!='\0') //mostramos flechas derechas
                            printf("%c\n", 175);
                        else
                            printf(" \n");

                        gotoxy(1,15);
                        textbackground(GREEN);

                        if(j<16){
                            for(i=0;i<16;i++){
                                if(editorData[i]!='\0'){
                                    cprintf("%c", editorData[i]);
                                }
                                else{
                                    textcolor(GREEN);
                                    cprintf("G");
                                    textcolor(WHITE);
                                }
                            }
                        } else{ //muestra los datos cuando tenemos mas de 16 caracteres
                            for(i=j-16;i<j;i++){
                                if(editorData[i]!='\0'){
                                    cprintf("%c", editorData[i]);
                                }
                                else{
                                    textcolor(GREEN);
                                    cprintf("G");
                                    textcolor(WHITE);
                                }
                            }
                        }
                        textbackground(BLACK);

                        gotoxy(k+1,15); //mostramos el cursor

                        opt = getch(); //introducimos datos
                        if(opt==0)
                            opt=getch()+1000;

                        switch(opt){
                            case ENTER:
                                if(!control.flag5){
                                    pointer->id=pos+1; //asignamos el valor al id
                                    if (!control.flag1){ //presionado luego de ingredar el nombre
                                        control.flag1=1;
                                        control.flag2=1;
                                        for(i=0;i<80;i++){ //guardamos el valor en la agenda
                                            pointer->name[i]=editorData[i];
                                        }
                                        for(i=0;i<80;i++)
                                            editorData[i]='\0';
                                    } else if (control.flag2){ //presionado luego de ingrasar el numero telefonico
                                        control.flag2=0;
                                        control.flag3=1;
                                        for(i=0;i<16;i++){ //guardamos
                                            pointer->phone[i]=editorData[i];
                                        }
                                        for(i=0;i<16;i++)
                                            editorData[i]='\0';
                                    } else if (control.flag3){ //presionado luego de ingresar el domicilio
                                        control.flag3=0;
                                        control.flag4=1;
                                        for(i=0;i<80;i++){ //guardamos
                                            pointer->address[i]=editorData[i];
                                        }
                                        for(i=0;i<80;i++)
                                            editorData[i]='\0'; //asignamos a todas las posiciones el valor de \0
                                        break;
                                    }
                                } else{ //seccion de busqueda
                                    for(i=pos;i<10;i++){
                                        if(strstr(agenda[i].name,editorData)!=NULL){
                                            pos=i;
                                            i=10;
                                        }
                                    }
                                    control.flag4=1;
                                }
                                j=0; //hacemos 0 la posicion para cargarlo
                                k=0; //hacemos cero la posicion del cursor
                                for(i=0;i<256;i++)
                                    editorData[i]='\0';
                            break;
                            case ESC: //si presionamos ESC no guardamos los cambios
                                if(!control.flag5){
                                    if(!control.flag1){
                                        control.flag1=1;
                                        control.flag2=1;
                                    } else if (control.flag2){
                                        control.flag2=0;
                                        control.flag3=1;
                                    } else if (control.flag3){
                                        control.flag3=0;
                                        control.flag4=1;
                                    }
                                } else{
                                    control.flag4=1;
                                }
                                j=0;
                                k=0;
                                for(i=0;i<256;i++) //limpiamos el vector
                                    editorData[i]='\0';
                            break;
                            case DEL: //borramos el caracter a la derecha del cursor
                                for(i=j;i<strlen(editorData);i++)
                                    editorData[i]=editorData[i+1];
                            break;
                            case BACKSPACE: //borramos el caracter a la izquierda del cursor
                                for(i=j-1;i<strlen(editorData);i++)
                                    editorData[i]=editorData[i+1];
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
                                if(k<16 && editorData[j]!='\0')
                                    k++;
                                if(j<256 && j<strlen(editorData))
                                    j++;
                            break;
                            default:
                                if(isascii(opt)!=0){ //isascii devuelve 0 si el caracter no es ascii
                                        if(editorData[j]!='\0'){ //usado cuando queremos cargar caracteres en una posicion donde ya habia
                                            for(i=sizeof(editorData);i>=j;i--){
                                                editorData[i+1]=editorData[i];
                                            }
                                            editorData[j]=opt;
                                            j++;
                                        } else{
                                            editorData[j]=opt;
                                            j++;
                                        }
                                    if(k<16)//movemos el cursor
                                        k++;
                                }
                            break;
                        }
                        if((opt==ENTER&&control.flag4) || (opt==ESC&&control.flag4)) //salida si ya se ingresaron los datos
                            break;
                    }
                }
            break;
            case DEL: //eliminar elementos
                clrscr();
                agenda[pos].id = 0;
                strcpy(agenda[pos].name,"\0");
                strcpy(agenda[pos].phone,"\0");
                strcpy(agenda[pos].address,"\0");

                if(pos==0){
                    while(agenda[pos].id==0){ //mostramos las posiciones de la agenda
                        pos++;
                        if(pos==posMax)
                            break;
                    }
                } else if(pos==posMax){
                    while(agenda[pos].id==0){ //mostramos las posiciones de la agenda
                        pos--;
                        if(pos==0)
                            break;
                    }
                } else
                    pos++;
            break;
            case LEFT:
                if(pos>0 && emp<9){
                    if(agenda[pos].id!=0) //curadamos la ultima posicion que tiene datos
                        temp=pos;
                    pos--;

                    while(agenda[pos].id==0){ //mostramos las posiciones de la agenda
                        if(pos==0){
                            pos=temp;
                            break;
                        }
                        pos--;
                    }
                }
            break;
            case RIGHT:
                if(pos<posMax && emp<9 ){
                    if(agenda[pos].id!=0) //guardamos la ultima posicion que tiene datos
                        temp=pos;
                    pos++;

                    while(agenda[pos].id==0){ //mostramos las posiciones de la agenda
                        if(pos==posMax){
                            pos=temp;
                            break;
                        }
                        pos++;
                    }
                }
            break;
        }
    }
/* END User code -------------------------------------------------------------*/
   return 0;
}
