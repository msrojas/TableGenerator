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

/* Imprime una tabla entera */
void PrintTable(struct Table * table, uint8_t flag)
{
    struct Lista * lista_columnas = table->ListaColumnas->next;
    uint16_t len = GetListaElementos(lista_columnas->valor, table); //Obtenemos el mayor "len" de una cadena y ajustamos dicha longitud al margen
    if(len == 0) 
        exit(1);

    if(flag == MYSQL_STYLE)
        PrintMargen(flag, len+2); //Imprimimos el margen de la parte de arriba
    else
    {
        printf("┌");
        PrintLine(len+2, flag); //Imprimimos el margen de la parte de arriba
        printf("┬");
    }

    PrintMargenRestante(lista_columnas, table, flag, TOP); //Imprimimos el margen restante de la parte de arriba
    if(flag == RECTANGULO)
        printf("┐");

    PrintTitleRestante(lista_columnas, table, flag); //Imprime el titulo de las columnas

    if(flag == MYSQL_STYLE)
        PrintMargen(flag, len+2); //Imprime el margen que separa el titulo de los elementos
    else
    {
        printf("├");
        PrintLine(len+2, flag); //Imprime el margen que separa el titulo de los elementos
        printf("┼");
    }

    PrintMargenRestante(lista_columnas, table, flag,TOP_BOTTOM); //Imprime el margen restante que separa el titulo de los elementos
    if(flag == RECTANGULO)
        printf("┤");

    PrintElementosByLine(lista_columnas, table, flag); //Imprime todos los elementos linea por linea
    
    if(flag == MYSQL_STYLE)
    {
        PrintMargen(flag, len+2); //Imprimimos margen inferior
        PrintMargenRestante(lista_columnas, table, flag, BOTTOM); //Imprimimos margen restante inferior
    }
    else
    {
    	printf("└");
    	PrintLine(len+2, flag); //Imprimimos margen inferior
    	printf("┴");
    	PrintMargenRestante(lista_columnas, table, flag, BOTTOM); //Imprimimos margen restante inferior
    	printf("┘");
    }

    printf("\n");
}

/* Imprime la linea del margen */
void PrintLine(uint16_t len, uint8_t flag)
{
    uint16_t i=0;

    if(flag == MYSQL_STYLE)
    {
        for(;i<len;i++)
            printf("-");
    }
    else
    {
        for(;i<len;i++)
            printf("─");
    }
}

/* Funcion que imprime todos los elementos de una tabla */
void PrintElementosRestantes(struct Lista * lista, struct Table * hash, uint16_t fila, uint8_t flag)
{
    lista = lista->next;
    uint16_t len = 0;
    struct data * datos = init_datos(flag, OTRA_COLUMNA); //Creamos estructura para el tipo de margen y posicion de la columna

    while(lista != NULL)
    {
        len = GetListaElementos(lista->valor, hash); //Obtenemos el mayor "len" de una cadena y ajustamos dicha longitud al margen
        len += (flag == MYSQL_STYLE) ? 0 : 2;
        if(!GetElemento(lista->valor, hash, fila, len, datos)) //Imprimimos el elemento de las columnas restantes
            exit(1);

        lista = lista->next;
    }

    free(datos);
}

/* Funcion que imprime todos los elementos de una tabla */
void PrintElementosByLine(struct Lista * lista, struct Table * hash, uint8_t flag)
{
    printf("\n");
    uint16_t len = 0;
    uint8_t * elemento = NULL;
    uint16_t fila = 0;
    uint16_t indice = 0;
    struct data * datos = init_datos(flag, PRIMERA_COLUMNA); //Creamos estructura para el tipo de margen y posicion de la columna

    while(indice < hash->size_fila)
    {
        len = GetListaElementos(lista->valor, hash); //Obtenemos el mayor "len" de una cadena y ajustamos dicha longitud al margen
        len += (flag == MYSQL_STYLE) ? 2 : 4;
        if(!GetElemento(lista->valor, hash, fila, len,datos)) //Imprimimos el elemento de la PRIMERA COLUMNA
            exit(1);

        PrintElementosRestantes(lista, hash, fila, flag); //Imprimimos los elementos de las columnas restantes
        printf("\n");
        WFree(elemento);
        fila++;
        indice += hash->columna;
    }

    free(datos);
}

/* Funcion que imprime todos los titulos de una tabla */
void PrintTitleRestante(struct Lista * lista, struct Table * hash, uint8_t flag)
{
    printf("\n");
    uint16_t len = 0;
    len = GetListaElementos(lista->valor, hash); //Obtenemos el mayor "len" de una cadena y ajustamos dicha longitud al margen
    len += (flag == MYSQL_STYLE) ? 2 : 4; 

    printf("%s %s%*s", (flag == MYSQL_STYLE) ? "|" : "│",lista->valor, len-strlen(lista->valor), (flag == MYSQL_STYLE) ? "|" : "│");

    lista = lista->next;

    while(lista != NULL)
    {
        len = GetListaElementos(lista->valor, hash); //Obtenemos el mayor "len" de una cadena y ajustamos dicha longitud al margen
        len += (flag == MYSQL_STYLE) ? 2 : 4;
        printf(" %s%*s", lista->valor, len-strlen(lista->valor), (flag == MYSQL_STYLE) ? "|" : "│");
        lista = lista->next;
    }
    printf("\n");
}

/* Esta funcion es para imprimir el margen completo de una la tabla */
void PrintMargenRestante(struct Lista * lista, struct Table * hash, uint8_t flag, uint8_t posicion_flag)
{
    uint16_t len = 0;
    uint16_t contar = 1; //Ya hemos impreso un margen, por lo tanto el valor es uno
    lista = lista->next;

    while(lista != NULL)
    {
        contar++;
        len = GetListaElementos(lista->valor, hash) + 2;  //Obtenemos el mayor "len" de una cadena y ajustamos dicha longitud al margen
        PrintLine(len, flag);
        if(flag == MYSQL_STYLE)
            printf("+");
        else if(flag == RECTANGULO && posicion_flag == TOP && contar != hash->size_columna)
            printf("┬");
        else if(flag == RECTANGULO && posicion_flag == TOP_BOTTOM && contar != hash->size_columna)
            printf("┼");
        else if(flag == RECTANGULO && posicion_flag == BOTTOM && contar != hash->size_columna)
            printf("┴");
        lista = lista->next;
    }
}

/* Funcion que imprime el margen segun el flag que se le pase */
void PrintMargen(uint8_t flag, uint16_t len)
{
    uint16_t i=0;
    if(flag == MYSQL_STYLE)
    {
        printf("+");
        PrintLine(len, flag);
        printf("+");
    }
    else
    {
        printf("┌");
        PrintLine(len, flag);
        printf("┐");
    }

}

/* Funcion que imprime el titulo de la columna */
void PrintTitle(uint8_t * name, uint16_t len, uint8_t flag)
{
    PrintMargen(flag, len); //Imprime el margen de la parte de arriba
    printf("\n");

    if(flag == MYSQL_STYLE)
    	printf("| %s%*c\n", name, len-strlen(name),'|');
    else
        printf("│ %s │\n", name);

    if(flag == MYSQL_STYLE)
        PrintMargen(MYSQL_STYLE, len); //Imprime el margen de la parte baja
    else 
        print_bottom_rectangulo(len); //Imprime el margen de la parte baja
    printf("\n");
}

/* Imprimimos SOLO UNA COLUMNA especificada con sus respectivos elementos*/
void PrintColumna(uint8_t * key, uint8_t flag, struct Lista * lista)
{
    //Para imprimir correctamente el margen del titulo de la columna, deberemos verificar cual es la cadena mas larga de los elementos
    //y ajustar dicha longitud al margen
    uint16_t len_key = strlen(key);  
    uint16_t MaxLen = ElementoLen(lista);
    if(len_key > MaxLen)
        MaxLen = len_key;

    MaxLen += 2;

    PrintTitle(key,MaxLen,flag);
    PrintElementos(lista, MaxLen,flag);
}

/* Funcion para imprimir la parte baja del estilo RECTANGULO */
void print_bottom_rectangulo(uint16_t len)
{
    uint16_t i = 0;

    printf("└");

    for(;i<len;i++)
        printf("─");
    printf("┘\n");
}

/* Imprimir una simple caja */
void PrintBox(uint8_t * output, uint8_t flag)
{
    PrintTitle(output, strlen(output)+2, flag);
}

/* Creamos hash_table para almacenar la columna con sus respectivos elementos */
struct Table * init_table(uint16_t columna, uint16_t fila)
{
    if(columna == 0 && fila == 0)
    {
        fprintf(stderr, "ERROR: columna y fila son cero\n");
        return NULL;
    }

    struct Table * temp = ht_create(columna);
    if(temp == NULL)
        return NULL;

    temp->columna = columna;
    temp->fila = columna*fila;

    return temp;
}

/* Almacenamos estrutura con el estilo del margen y la posicion de la columna actual */
struct data * init_datos(uint8_t style_flag, uint8_t posicion_flag) 
{
    struct data * datos = malloc(sizeof(struct data));
    if(datos == NULL)
    {
        fprintf(stderr, "ERROR: ocurrio un inconveniente en la heap\n");
        return NULL;
    }

    datos->style_flag = style_flag;
    datos->posicion_flag = posicion_flag;
    return datos;
}
