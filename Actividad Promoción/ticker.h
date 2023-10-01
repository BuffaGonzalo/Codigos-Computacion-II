#ifndef TICKER_H_INCLUDED
#define TICKER_H_INCLUDED

#include <time.h>

/**\brief Función on Timer.
    Define el tipo de función que se llama cuando se cumple el timer especificado.
*/
typedef void (*OnTimer)();

/**\brief Modos de ejecución del timer.
*/
typedef enum{
    PERIODIC = 0,
    ONESHOT,
} _eTypeTimer;

/** \brief TimerAdd
    Agrega un nuevo timer a la lista. Esta tiene que crearse primero con TimerCreate.

    \return
    Devuelve 0 en caso de no poder agregar un nuevo timer.
    Distinto de 0 cuando pudo agregarlo.
*/
int TimerAdd();

/** \brief TimerConnect
    Conecta el timer a una función que se ejecutara cuando este se cumpla.

    \param[in] aTimerId: número identificador del timer.
    \param[in] aOnTimerFun: función a ejecutar.
*/

void TimerConnect(int aTimeId, OnTimer aOnTimerFun);

/** \brief TimerStart
    Inicializa el timer para empezar a contar el tiempo.

    \param[in] aTimerId: número identificador del timer.
    \param[in] ms: tiempo en milisegundos.
    \param[in] mode: forma en que se ejecutara el timer.
*/

void TimerStart(int aTimerId, int ms, _eTypeTimer mode);

/** \brief TimerStop
    Detiene la ejecución del timer

    \param[in] aTimerId: número identificador del timer.
*/

void TimerStop(int aTimerId);

/** \brief TickerTask
    Esta función debe llamarse continuamente en el programa principal en un lugar que no se
    bloqueado por niguna otra función, es la encargada de controlar el tiempo que pasa en cada
    uno de los timers configurados.

    Por ejemplo:

    .
    .
    .
    while(1){
        .
        .
        .
        TickerTask();
        .
        .
        .
    }
    .
    .
    .
*/

void TickerTask();


#endif // TICKER_H_INCLUDED
