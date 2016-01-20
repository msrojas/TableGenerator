#include "grafica.h"

int main()
{
    /* Si solo deseas crear un titulo y NO UNA TABLA entera, lo puedes hacer utilizando la funcion PrintBox */
    /* If you just want create a title and not a entire table, you can do it using the function PrintBox */

    PrintBox("Hola mundo", MYSQL_STYLE);
    PrintBox("Hello world", RECTANGULO);
    
    return 0;
}
