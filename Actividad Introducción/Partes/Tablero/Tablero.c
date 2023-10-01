#include <stdio.h>
#include <conio.h>

#define SIZE 8 // tamaño del tablero

int main() {
    int row, col, num, i;

    num = 1;
    printf("     A    B    C    D    E    F    G    H\n");
    
    for (row = 0; row < SIZE; row++) { //controla la fila
        for(i=0;i<3;i++){
            //imprimimos numeros de las filas a la izquierda
            if(i==1)
                printf(" %i ", num);
            else
                printf("   "); 
            for (col = 0; col < SIZE; col++) { //5 caracteres de ancho por 3 de alto      
            
                if ((row + col) % 2 == 0) { // casillas blancas
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
            getch();
        }
        

        num++; 
        if(i==2)      
            printf("\n"); // imprimir salto de línea al final de cada fila
    }
    
    printf("     A    B    C    D    E    F    G    H\n");     
    
    getch();    
    return 0;
}
