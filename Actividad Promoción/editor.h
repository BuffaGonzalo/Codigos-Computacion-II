#ifndef EDITOR_H_INCLUDED
#define EDITOR_H_INCLUDED

/** \brief editor
 *
 * \param[in] bufferLenth: Utilizado para comunicar la longitud total del buffer
 * \param[in] seenBuffer: Utilizado para comunicar a la funcion la seccion visible del editor
 * \param[in] *eVector: Puntero al primer elemento de la cadena mainEditor
 * \param[out] *eVector: Devuelve los datos ingresados por el usuario
 * \param[in] opt: Utilizada para comunicar a la funcion las teclas presionadas por el usuario
 * \param[in] posX: Utilizada para determinar la posicion en X del editor en la consola
 * \param[in] posY: Utilizada para determinar la posicion en Y del editor en la consola
 * \param[in] bkgColor: Utilizada para determinar el color de fondo del editor
 * \param[in] ltrColor: Utililizado para dar el color de los caracacteres
 * \param[in] cursorBlink: Utilizado para determinar cuando parpadea el cursor
 * \return
 *
 */

void editor(unsigned short bufferLenth, unsigned short seenBuffer,char *eVector, int opt, int posX, int posY, unsigned char bkgColor, unsigned char ltrColor, char cursorBlink);

/** \brief
 *
 * \param[in] bufferLenth: Utilizada para brindar la longitud total del buffer
 * \param[in] *eVector: Puntero de tipo char que recibe la direccion del primer elemento del vector mainEditor
 * \param[out] *eVector: Devuelve los valores de la cadena en el formato correcto sin espacios.
 * \return
 *
 */

void parser(unsigned short bufferLenth, char *eVector);

#endif // EDITOR_H_INCLUDED
