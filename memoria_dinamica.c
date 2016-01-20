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

#include "memoria_dinamica.h"

uint8_t * WMalloc(const uint8_t * cadena)
{
	uint8_t * retorna = malloc(strlen(cadena)+1);
	if(!retorna)
	{
		fprintf(stderr, "ERROR: ocurrio un inconveniente en la heap\n");
		return NULL;
	}

	return strcpy(retorna, cadena);
}

void WFree(uint8_t * var)
{
	if(var == NULL)
		return;
	free(var);
	var = NULL; //EVITA DANGLING POINTER
}
