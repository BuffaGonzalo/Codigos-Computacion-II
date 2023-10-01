/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
/* END Includes --------------------------------------------------------------*/

/* typedef -------------------------------------------------------------------*/
typedef union{
    int numbers;
    char letters[4];
}uData;

typedef struct{
    unsigned short arrow:3;
    unsigned short order:3;
    unsigned short flag:1;
    unsigned short letcont:1; //control letters
    unsigned short arrowcont:1;
    unsigned short f5flag:1; //borrar despues
    unsigned short fFlag:1;
    unsigned short aFlag:1;
    unsigned short arrowFlag:1;
    unsigned short other:2;
}bitField;

/* END typedef ---------------------------------------------------------------*/

/* define --------------------------------------------------------------------*/
#define F1      1059 //tecla f1
#define F2      1060 //tecla f2
#define F3      1061 //tecla f3
#define F4      1062 //tecla f4
#define F5      1063 //tecla f5
#define UP      1072 // arriba
#define LEFT    1075 //izquierda
#define RIGHT   1077 //derecha
#define DOWN    1080 //abajo
#define ENTER   13 //tecla enter
#define ESC     27 //tecla ESC
/* END define ----------------------------------------------------------------*/

int main(){
/* Local variables -----------------------------------------------------------*/
    uData aux;
    bitField control;
    control.flag=0;
    control.order=0;
    control.f5flag=0;
    control.arrowFlag=0; //controla si se muestra la ordenada, si se cambia su valor
    int  matrix[12][12] = {};
    int ordMatrix[12][12] = {};
    int m = 10, n = 10;//posiciones de la matriz, n = filas y m = columnas
    short i, j, k, l;
    int opt=0, varM=10, varN=10, oldM=10, oldN=10, val, pos, temp=0, oldOpt = 0; //posN y posM se usan para guardar la posicion ingresada cuando se presiona F3
    //aux sirve para guardar el valor de la poscion en el ordenamiento
    //order es utilizada para determinar como hacer el ordenamiento
    //num es utilizada para guardar el numero al presionar F2
/* END Local variables -------------------------------------------------------*/

/* User code -----------------------------------------------------------------*/
    while (1){
        system("cls");
        randomize(); //ejecutamos randomize para que se generen numeros aleatorios distintos

        printf("Actividad Matrices\n");
        printf("F1 - Llenar la matriz con caracteres aleatorios entre 0 y 999.\n");
        printf("F2 - Cargar la matriz con numeros aleatorios entre 0 y 500 (sin repetirse).\n");
        printf("F3 - Cargar la matriz con valores que se incrementan en uno partir del valor ingresado por cada celda que rodea la posicion ingresada.\n");
        printf("F4 - cargar la matriz con una combinacion aleatoria de tres caracteres entre A y H.\n");
        printf("F5 - Indicar las posiciones en donde se cumpla la condicion FAG o 245\n");
        printf("M - Cambiar el numero de columnas\n");
        printf("N - Cambiar el numero de filas\n");

        switch (opt) {
            case F1:
                for(i=0;i<n;i++){ //primero se recorre en filas
                    for(j=0;j<m;j++){
                       matrix[i][j] = random(999);
                    }
                }
                control.flag=1;
                control.letcont=0;
                oldOpt=F1;
                control.arrowFlag=0; //controla si se muestra la ordenada, si se cambia su valor
            break;
            case F2:
                for(k=0; k<n; k++) {
                    for(l=0; l<m; l++) {
                        do {
                            temp = random(400) + 100;
                            // verificaci�n de si el n�mero generado ya existe en la matriz
                            for(i=0; i<k+1; i++) {
                                for(j=0; j<m+1; j++) {
                                    if(matrix[i][j] == temp) {
                                        temp = 0; // asignar un valor temporal para indicar que el n�mero generado ya existe
                                        break; // salir del bucle j
                                    }
                                }
                                if(temp == 0) {
                                    break; // salir del bucle i si el n�mero generado ya existe
                                }
                            }
                        } while (temp == 0);
                        matrix[k][l] = temp; // asignaci�n del n�mero aleatorio a la posici�n k,l de la matriz
                    }
                }
                control.flag=1;
                control.letcont=0;
                oldOpt=F2;
                control.arrowFlag=0; //controla si se muestra la ordenada, si se cambia su valor
            break;
            case F3:
                printf("\n\nIngrese el valor de N\n");
                scanf("%i", &varN);
                while(varN<1 || varN>n){
                    printf("Reingrese el valor de N\n");
                    scanf("%i", &varN);
                }

                printf("Ingrese el valor de M\n");
                scanf("%i", &varM);
                while(varM<1 || varM>m){
                    printf("Reingrese el valor de M\n");
                    scanf("%i", &varM);
                }

                printf("Ingrese el numero a partir del cual realizar el incremento - debe de estar entre 0 y 100\n");
                    scanf("%i", &val);
                while(val>100 || val<0){
                    printf("Reingrese el numero\n");
                    scanf("%i", &val);
                }

                varM--;
                varN--;
                matrix[varN][varM]=val; //le asignamos a la posici�n el valor ingresado

                if(m>=n)
                    temp=m;
                if(n>m)
                    temp=n;

                pos=1;
                val++; //aumentamos el valor para utilizarlo la primera vez
                for(k=0;k<temp;k++){
                    for(i=0; i<n; i++){
                        for(j=0;j<m; j++){
                        //i==posN-pos && j==posM-pos)||(i==posN-pos && j==posM)||(i==posN-pos && j==posM+pos)||(i==posN && j==posM-pos)||(i==posN && j==posM+pos)||(i==posN+pos && j==posM-pos)||(i==posN+pos && j==posM)||(i==posN+pos && j==posM+pos)
                            if((i==varN-pos && j>=varM-pos && j<=varM+pos) || (i==varN+pos && j>=varM-pos && j<=varM+pos) || (j==varM-pos && i>varN-pos && i<=varN+pos) || (j==varM+pos && i>varN-pos && i<=varN+pos))
                                   matrix[i][j] = val;
                        }

                    }
                    val++; //aumentamos val en cada bucle
                    pos++; //posicion para colocar los numeros
                }
                control.flag=1;
                control.letcont=0;
                oldOpt=F3;
                control.arrowFlag=0; //controla si se muestra la ordenada, si se cambia su valor
            break;
            case F4:
                for(i=0;i<n;i++){
                    for(j=0;j<m;j++){
                        for(k=2;k>=0;k--){
                            aux.letters[k] = random(8)+'A'; //cargamos 3 numeros random en cada posicion
                        }
                        matrix[i][j] = aux.numbers;
                    }
                }
                control.flag=1;
                oldOpt=F4; //van a ser letras
                control.letcont=1;
                control.arrowFlag=0; //controla si se muestra la ordenada, si se cambia su valor
            break;
            case F5:
                control.fFlag=0;
                control.aFlag=0;
                if(oldOpt==F3 || oldOpt==F2 || oldOpt==F1){ //pasamos los numeros a letras
                    for(i=0;i<n;i++){
                        for(j=0;j<m;j++){
                            aux.letters[2] = matrix[i][j] / 100 + '0';  // obtiene el primer d�gito (2)
                            aux.letters[1] = (matrix[i][j] / 10) % 10 + '0';  // obtiene el segundo d�gito (4)
                            aux.letters[0] = matrix[i][j] % 10 + '0';  // obtiene el tercer d�gito (5)
                            aux.letters[3] = 0x00; //aceramos la posicion

                            matrix[i][j] = aux.numbers;
                        }
                    }
                }

                for(i=0;i<n;i++){
                    for(j=0;j<m;j++){
                        aux.numbers = matrix[i][j];
                        for(k=2;k>=0;k--){
                            if (aux.letters[k] == 'F' || aux.letters[k] == '2') {
                                control.fFlag = 1;
                                control.aFlag = 0;
                            } else if((aux.letters[k] == 'A' && control.fFlag == 1) || (aux.letters[k] == '4' && control.fFlag == 1)) {
                                control.aFlag = 1;
                                control.fFlag = 0;
                            } else if ((aux.letters[k]=='G' && control.aFlag==1)||(aux.letters[k]=='5' && control.aFlag==1)){ //si hubo una a antes, significa que tambien habia una F
                                control.aFlag=0;
                                aux.numbers = matrix[i][j];
                                aux.letters[3] = 0x01<<k; //desplaamos k posiciones el valor para imprimir G
                                if(k==0){ //cuando todos estan en una misma posicion
                                    aux.letters[3] = aux.letters[3]|0x06;
                                    matrix[i][j] = aux.numbers; // guardamos el valor
                                }
                                if(k==1 && j!=0){ //cuando dos estan en una posicion y uno en la anterior
                                    aux.letters[3] = aux.letters[3]|0x04;
                                    matrix[i][j] = aux.numbers; // guardamos el valor
                                    aux.numbers = matrix[i][j-1]; //vamos a la posicion anterior
                                    aux.letters[3] = aux.letters[3]|0x01; //comparamos y no asignamos para que no se nos borre lo cargado previamente
                                    matrix[i][j-1] = aux.numbers; // guardamos el valor
                                }
                                if(k==1 && j==0 && i!=0){ //cuando dos estan en una posicion y uno en la anterior, pero en el final de las lineas y principio de la siguinete
                                    aux.letters[3] = aux.letters[3]|0x04;
                                    matrix[i][j] = aux.numbers; // guardamos el valor
                                    aux.numbers = matrix[i-1][m-1]; //vamos a la posicion anterior
                                    aux.letters[3] = aux.letters[3]|0x01; //comparamos y no asignamos para que no se nos borre lo cargado previamente
                                    matrix[i-1][m-1] = aux.numbers; // guardamos el valor
                                }
                                if(k==1 && j==m-1 && i==n-1){ //cuando dos estan en una posicion y uno en la anterior, pero en las esquinas, a esta la realizamos desde la posicion final y luego apuntamos a la inicial
                                    aux.letters[3] = aux.letters[3]|0x01; //comparamos y no asignamos para que no se nos borre lo cargado previamente
                                    matrix[n-1][m-1] = aux.numbers; // guardamos el valor
                                    aux.numbers = matrix[0][0]; //vamos a la primera posicion
                                    aux.letters[3] = aux.letters[3]|0x06;
                                    matrix[0][0] = aux.numbers; // guardamos el valor
                                }
                                if(k==2 && j!=0){ //cuando uno esta en una posicion y dos en la anterior
                                    aux.letters[3] = aux.letters[3];
                                    matrix[i][j] = aux.numbers; // guardamos el valor
                                    aux.numbers = matrix[i][j-1]; //vamos a la posicion anterior
                                    aux.letters[3] = aux.letters[3]|0x03; //comparamos y no asignamos para que no se nos borre lo cargado previamente
                                    matrix[i][j-1] = aux.numbers; // guardamos el valor
                                }
                                if(k==2 && j==0 && i!=0){ //cuando uno esta en una posicion y dos en la anterior, pero en el final de las lineas y principio de la siguinete
                                    aux.letters[3] = aux.letters[3];
                                    matrix[i][j] = aux.numbers; // guardamos el valor
                                    aux.numbers = matrix[i-1][m-1]; //vamos a la posicion anterior
                                    aux.letters[3] = aux.letters[3]|0x03; //comparamos y no asignamos para que no se nos borre lo cargado previamente
                                    matrix[i-1][m-1] = aux.numbers; // guardamos el valor
                                }
                                if(k==2 && j==m-1 && i==n-1){ //cuando uno esta en una posicion y dos en la anterior, pero en las esquinas,lo realizamo al reves
                                    aux.letters[3] = aux.letters[3]|0x03; //comparamos
                                    matrix[i][j] = aux.numbers; // guardamos el valor
                                    aux.numbers = matrix[0][0]; //vamos a la primera posicion
                                    aux.letters[3] = aux.letters[3]|0x04;
                                    matrix[0][0] = aux.numbers; // guardamos el valor
                                }
                            } else{
                                control.aFlag = 0;
                                control.fFlag = 0;
                            }

                        }
                    }
                }
                control.f5flag=1;
                control.letcont=1;
                oldOpt=F5;
            break;
            case 'm':
            case 'M':
                varM = m; //valor anterior de columnas
                printf("\n\nIngrese el nuevo valor de M\n");
                scanf("%i", &m);

                while(m>12 || m<4){
                    printf("Reingrese el nuevo valor de M\n");
                    scanf("%i", &m);
                }
                if(m>varM){
                    opt = oldOpt; //asignamos el antiguo valor de alguna tecla de funcion a opt
                    oldOpt = 'm'; //asignamos el valor de la entrada actual a opt - en este caso m o M
                }
                if(m!=varM)
                control.arrowFlag=0;//no mostramos la matriz ordenada si se cambia el tama�o
            break;
            case 'n':
            case 'N':
                varN = n; //valor anterior de filas
                printf("\n\nIngrese el nuevo valor de N\n");
                scanf("%i", &n);

                while(n>12 || n<4){
                    printf("Reingrese de nuevo valor de N\n");
                    scanf("%i", &n);
                }
                if(n>varN){
                    opt = oldOpt; //asignamos el antiguo valor de alguna tecla de funcion a opt
                    oldOpt = 'n';
                }
                if(n!=varN)
                control.arrowFlag=0; //no mostramos la matriz ordenada si se cambia el tama�o
            break;
            case RIGHT: // por filas
                control.arrowFlag=1;
                oldN=n;
                oldM=m;
                control.arrow = 1; //bandera - flag
                control.order = 1; //vale 1 si ordena filas de menor a mayor
                if(control.letcont)
                    control.arrowcont = 1;
                else
                    control.arrowcont = 0;
            break;
            case LEFT: // por filas
                control.arrowFlag=1;
                oldN=n;
                oldM=m;
                control.arrow = 1; //bandera - flag
                control.order = 2; //vale 2 si ordena filas de mayor a menor;
                if(control.letcont)
                    control.arrowcont = 1;
                else
                    control.arrowcont = 0;
            break;
            case UP: //por columnas
                control.arrowFlag=1;
                oldN=n;
                oldM=m;
                control.arrow = 2; //bandera - flag
                control.order = 1; //vale 3 si ordena columnas de menor a mayor
                if(control.letcont)
                    control.arrowcont = 1;
                else
                    control.arrowcont = 0;
            break;
            case DOWN: //por columnas
                control.arrowFlag=1;
                oldN=n;
                oldM=m;
                control.arrow = 2; //bandera - flag
                control.order = 2; //vale 4 si ordena columnas de mayor a menor
                if(control.letcont)
                    control.arrowcont = 1;
                else
                    control.arrowcont = 0;
            break;
        }
        if(control.arrow>0){ //utilizado para que no se cambie la matriz ordenada todo el tiempo
            for(i=0;i<n;i++){
                for(j=0;j<m;j++){
                    ordMatrix[i][j]=matrix[i][j];
                }
            }
        }
        //seccion de ordenamiento
        if(control.arrow==1){
            for(k=0;k<12;k++){ //sirve para recorrer
                for(l=0;l<12;l++){ //sirve para recorrer
                    for(i=0;i<n;i++){ //lo recorre por filas
                        for(j=0;j<m;j++){ //restamos uno para que no se salga de la matriz
                            if(control.order == 1){ //filas de menor a mayor
                                if(ordMatrix[i][j]>ordMatrix[i][j+1] && j!=m-1){
                                    temp = ordMatrix[i][j+1];
                                    ordMatrix[i][j+1] = ordMatrix[i][j];
                                    ordMatrix[i][j] = temp;
                                }
                                if(ordMatrix[i][m-1]>ordMatrix[i+1][0] && i!=n-1){
                                    temp = ordMatrix[i+1][0];
                                    ordMatrix[i+1][0] = ordMatrix[i][m-1];
                                    ordMatrix[i][m-1] = temp;
                                }
                            }

                            if(control.order == 2){ //filas de mayor a menor
                                if(ordMatrix[i][j]<ordMatrix[i][j+1] && j!=m-1){
                                    temp = ordMatrix[i][j+1];
                                    ordMatrix[i][j+1] = ordMatrix[i][j];
                                    ordMatrix[i][j] = temp;
                                }
                                if(ordMatrix[i][m-1]<ordMatrix[i+1][0] && i!=n-1){
                                    temp = ordMatrix[i+1][0];
                                    ordMatrix[i+1][0] = ordMatrix[i][m-1];
                                    ordMatrix[i][m-1] = temp;
                                }
                            }
                        }
                    }
                }
            }
        }
        if(control.arrow==2){
            for(k=0;k<12;k++){ //sirve para recorrer
                for(l=0;l<12;l++){ //sirve para recorrer
                    for(j=0;j<m;j++){ //lo recorre por columnas
                        for(i=0;i<n;i++){ //restamos uno para que no se salga de la matriz
                            if(control.order == 1){ //columnas de menor a mayor
                                if(ordMatrix[i][j]>ordMatrix[i+1][j] && i!=n-1){
                                    temp = ordMatrix[i+1][j];
                                    ordMatrix[i+1][j] = ordMatrix[i][j];
                                    ordMatrix[i][j] = temp;
                                }
                                if(ordMatrix[n-1][j]>ordMatrix[0][j+1] && j!=m-1){
                                    temp = ordMatrix[0][j+1];
                                    ordMatrix[0][j+1] = ordMatrix[n-1][j];
                                    ordMatrix[n-1][j] = temp;
                                }
                            }
                            if(control.order == 2){ //columnas de mayor a menor
                                if(ordMatrix[i][j]<ordMatrix[i+1][j] && i!=n-1){
                                    temp = ordMatrix[i+1][j];
                                    ordMatrix[i+1][j] = ordMatrix[i][j];
                                    ordMatrix[i][j] = temp;
                                }
                                if(ordMatrix[n-1][j]<ordMatrix[0][j+1] && j!=m-1){
                                    temp = ordMatrix[0][j+1];
                                    ordMatrix[0][j+1] = ordMatrix[n-1][j];
                                    ordMatrix[n-1][j] = temp;
                                }
                            }
                        }
                    }
                }
            }
        }
        control.arrow=0;
        //mostrar matriz - colocar unavariable de control aca para que no se muestre despues de la primera ejecucion
        if(control.flag==1 && control.f5flag==0){
            printf("\n\nMATRIZ - DESORDENADA\n");
            for(i=0;i<n;i++){
                for(j=0;j<m;j++){
                    if(control.letcont){
                        aux.numbers = matrix[i][j];
                        printf("| ");
                        for(k=2;k>=0;k--)
                            printf("%c", aux.letters[k]);
                        printf(" | ");
                    }
                    else{
                        printf("| %3i | ", matrix[i][j]);
                    }
                }
                printf("\n");
            }
        }

        if(control.f5flag && control.flag){ //mostramos luego de presionar F5 - utilizo la 3 posicion del arreglo de la matriz de caracteres de la union para guardar el valor de impresion
            printf("\n\nMATRIZ - DESORDENADA\n");
            for(i=0;i<n;i++){
                for(j=0;j<m;j++){
                    aux.numbers = matrix[i][j]; // asigno para comprobar
                    printf("| ");
                    for(k=2;k>=0;k--){
                        if(aux.letters[3] & 0x01 << k){ //comparamos, si la posicion tiene un 1 entonces va con color
                            textbackground(GREEN);
                            cprintf("%c", aux.letters[k]);
                            textbackground(BLACK);
                        } else{
                            printf("%c",aux.letters[k]);
                        }
                    }
                    printf(" | ");
                }
                printf("\n");
            }
        }
        control.f5flag=0;

        if(control.arrowFlag==1){ //control.order para controlar que no se muestre si no se presiona flechita
            printf("\n\nMATRIZ - ORDENADA\n");
            for(i=0;i<oldN;i++){
                for(j=0;j<oldM;j++){
                    if(control.arrowcont){ //contarrow corrobora cuando se tocan las flechas si antes se toco F4 o F5
                        aux.numbers = ordMatrix[i][j];
                        printf("| ");
                        for(k=2;k>=0;k--)
                            printf("%c", aux.letters[k]);
                        printf(" | ");
                    } else{
                        printf("| %3i | ", ordMatrix[i][j]);
                    }
                }
                printf("\n");
            }
        }

        if(control.flag==1)
            temp = opt; //gaurdamos el valor de opt anterior, temporalmente
        if(oldOpt!='n' && oldOpt !='m' && oldOpt !='N' && oldOpt !='M'){ //si es igual a m o n entonces se vuelve a cargar con datos nuevos
            opt = getch();

            if(opt==0)
                opt=getch()+1000;
            if(opt==ESC)
                break;
            }
        }
/* END User code -------------------------------------------------------------*/
   return 0;
}
