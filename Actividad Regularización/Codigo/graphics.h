#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED

/** \brief crearDisplay
 *
 * \param[in] display: dirección del array ingresado
 * \param[out] display
 * \param[in] columns: cantidad de columnas máxima del array
 * \param[in] rows: cantidad de filas máxima del array
 *
 *  Funcion encargada de recibir el display del main, y adignarlo a un puntero, con el cual luego nos desplazaremos en la librería con el fin de realizar modificaciones
 *
 * \return void
 */

void createDisplay(unsigned char *display, int columns, int rows);

/** \brief loadLetters
 *
 * \param[in] fontValue: posición en la ROM del carácter
 * \param[in] backgroundColor: valor del color de fondo
 * \param[in] fontColor: valor del color del carácter
 * \param[in] posX
 * \param[in] posY
 *
 * Función encargada de cargar numeros en el display tomando un valor (fontValue) el cual luego de dependiendo del valor del archivo FONT,
 * cargamos en las posiciones del display caracteres 254 o espacios.
 *
 * \return void
 */

void loadLetters(unsigned char fontValue, char backgroundColor, char fontColor, int posX, int posY);

/** \brief displaySection
 *
 * \param[in] posX
 * \param[in] posY
 * \param[in] posXMax
 * \param[in] posYMax
 *
 * Funcion encargada de mostrar un sector del display en el cual tendriamos letras.
 *
 * \return void
 */

void displaySection(int posX, int posY, int posXmax, int posYmax);

/** \brief clearDisplay
 *
 * \param[in] rowMin: tamaño inicial de filas
 * \param[in] colMin: tamaño inicial de columnas
 * \param[in] rowMax: tamaño máximo de filas
 * \param[in] colMax: tamaño máximo de columnas
 * \param[in] show: imprimir la pantalla limpia (1=imprimir)
 *
 * Función encargada de limpiar la totalidad o una sección del display
 *
 * \return void
 */

void clearDisplay(int minRow, int minCol, int maxRow, int maxCol, char show);


#endif // GRAPHICS_H_INCLUDED
