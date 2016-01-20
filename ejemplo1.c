/*	
    TableGenerator
    Copyright (C) 2016  Alejandro Torres Hernandez

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

    Email: alez011@hotmail.com
*/  

#include "grafica.h"
#include <time.h>

int main()
{
    clock_t start = clock();

    struct Table * table = init_table(3,5);  //Definimos la tabla: columnas, filas
    if(table == NULL)
        exit(1);


    if(!AgregarColumna(table, "Name")) //Agregamos una columna
    {		
        ht_destroy(table);
        exit(1);
    }

    if(!AgregarElemento(table, "Name", "Alex")) //Agregamos un elemento a la columna: Name
    {
        ht_destroy(table);
        exit(1);
    }

    if(!AgregarElemento(table, "Name", "Saul")) //Agregamos un elemento a la columna: Name
    {
        ht_destroy(table);
        exit(1);
    }

    if(!AgregarElemento(table, "Name", "Gerardo Torres")) //Agregamos un elemento a la columna: Name
    {
        ht_destroy(table);
        exit(1);
    }


    if(!AgregarColumna(table, "Edad")) //Agregamos otra columna
    {		
        ht_destroy(table);
        exit(1);
    }

    if(!AgregarElemento(table, "Edad", "13")) //Agregamos un elemento a la columna: Edad
    {
        ht_destroy(table);
        exit(1);
    }

    if(!AgregarElemento(table, "Edad", "19")) //Agregamos un elemento a la columna: Edad
    {
        ht_destroy(table);
        exit(1);
    }

    if(!AgregarElemento(table, "Edad", "24")) //Agregamos un elemento a la columna: Edad
    {
        ht_destroy(table);
        exit(1);
    }

    if(!AgregarColumna(table, "Direccion")) //Agregamos una columna mas
    {		
        ht_destroy(table);
        exit(1);
    }

    if(!AgregarElemento(table, "Direccion", "Col. Hidalgo")) //Agregamos un elemento a la columna: Direccion
    {
        ht_destroy(table);
        exit(1);
    }

    if(!AgregarElemento(table, "Direccion", "Insurgentes")) //Agregamos un elemento a la columna: Direccion
    {
        ht_destroy(table);
        exit(1);
    }

    if(!AgregarElemento(table, "Direccion", "Calle Morelos")) //Agregamos un elemento a la columna: Direccion
    {
        ht_destroy(table);
        exit(1);
    }


    PrintTable(table, MYSQL_STYLE); //Imprimimos la tabla pasandole el estilo de los margenes 
    //Por el momento solo hay dos estilos: MYSQL_STYLE y RECTANGULO
    PrintTable(table, RECTANGULO);

    ht_destroy(table); //Destruimos la tabla

    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%f\n", seconds);
	
    return 0;
}
