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

#ifndef GRAFICA_H
#define GRAFICA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "hash_table.h"

void PrintTable(struct Table * table, uint8_t flag);
void PrintLine(uint16_t len, uint8_t flag);
void PrintElementosRestantes(struct Lista * lista, struct Table * hash, uint16_t fila, uint8_t flag);
void PrintElementosByLine(struct Lista * lista, struct Table * hash, uint8_t flag);
void PrintTitleRestante(struct Lista * lista, struct Table * hash, uint8_t flag);
void PrintMargenRestante(struct Lista * lista, struct Table * hash, uint8_t flag, uint8_t posicion_flag);
void PrintMargen(uint8_t flag, uint16_t len);
void PrintTitle(uint8_t * name, uint16_t len, uint8_t flag);
void PrintColumna(uint8_t * key, uint8_t flag, struct Lista * lista);
void print_bottom_rectangulo(uint16_t len);
void PrintBox(uint8_t * output, uint8_t flag);
struct Table * init_table(uint16_t columna, uint16_t fila);
struct data * init_datos(uint8_t style_flag, uint8_t posicion_flag);

#endif 
