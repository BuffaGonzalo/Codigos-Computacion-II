/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <conio.h>
//#include <ctype.h>
#include <string.h>
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

int main(){
/* Local variables -----------------------------------------------------------*/
  char cadena [20][100] = {}; //lista de caracteres
  char cadenaSearch[20]; //usada para fin
  int i, j, k, opt, cont;
  int pos = 0;
/* END Local variables -------------------------------------------------------*/

/* User code -----------------------------------------------------------------*/
    while (1){
        clrscr();
        //menu ingresar mas strings buscar strings salir
        printf("MENU\n");
        printf("1. Ingresar cadenas de caracteres\n");
        printf("2. Mostrar cadenas de caracteres\n");
        printf("3. Borrar cadenas de caracteres\n");
        printf("4. Salir\n");
        
        if(opt==0)
            opt=getch()+1000;
        if(opt=='4')
            break;
        
        //scanf("%i", &opt);
        opt = getch();
        //con fin dejas de escribir y con escape salis del programa

        switch(opt){
            case '1': //ingresar elementos
                clrscr();
                //printf("POSICION %i", pos);
                if(pos==19){
                    printf("No puede ingresar mas elementos, arreglo lleno\n");
                }else{
                    for(i=pos;i<20 && strcmp(cadena[i-1],"FIN")!=0;i++){
                        printf("Elemento N%i \t", i+1);
                        gets(cadena[i]);
                        pos = i; //utilizad para guardar la posicion de carga de datos y no sobre escribir
                    }
                    //cambiamos la cadena de caracteres FIN por el caracter \0, caracter NULL
                    if(strcmp(cadena[i-1],"FIN")==0)
                        cadena[i-1][0] = '\0';
                }
            break;
            case '2': //mostrar elementos
                clrscr();
                for(i=0;i<=pos;i++){
                    if(cadena[i][0] != '\0'){ //comparamos dentro sino simpre comparariamos con la posicion [0][0] y se mostraría el \0 cuando esta en una posicion distinta.
                        printf("Elemento N%i \t %s\n", i+1, cadena[i]);
                    }
                }
                getch();
            break;
            case '3': //eliminar un elemento
                clrscr();
                //Se guarda un FIN, falla en el arreglo - SOLUCIONADO
                if(cadena[0][0]=='\0'){
                printf("No puede eliminar mas elementos, arreglo vacio\n");
                getch();
                break;
                }
        
                printf("Ingrese el elemento a eliminar\n");
                gets(cadenaSearch);
                
                cont = 0; //igualamos a cero para eliminar el error
                for(i=0;i<20;i++)
                    if(strcmp(cadena[i],cadenaSearch)==0)
                        cont++;
                
                for(k=0;k<cont;k++){ //lo usamos para eliminar elementos repetidos
                    for(i=0; cadena[i][0]!='\0' && i<20; i++){
                        if(strcmp(cadena[i],cadenaSearch)==0){ //analizamos si son iguales
                            for(j=i+1;cadena[i][0] && j<20; j++){ //recorremos el array
                                //ahora eliminamos el contenido repetido copiando lo que esta en la posición siguiente
                                strcpy(cadena[j-1],cadena[j]); 
                            }
                        }

                    }
                    if(pos!=0)
                        pos--;
                }

            break;
            case '4':
                //opt=27;
            break;
        }
    }
/* END User code -------------------------------------------------------------*/

   return 0;
}
