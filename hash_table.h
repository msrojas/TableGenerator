#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "memoria_dinamica.h"
#include "enums.h"

struct data
{
	uint8_t style_flag;
	uint8_t posicion_flag;
};

struct Lista
{
	uint8_t * valor;
	struct Lista * next;
};

struct hash_elem_t
{
	struct hash_elem_t * next;
	uint8_t * column_name;
	struct Lista * Lista_Elementos;
};

struct Table
{
	uint16_t columna;
	uint16_t fila;
	uint16_t size_columna;
	uint16_t size_fila;
	struct Lista * ListaColumnas;
	struct hash_elem_t ** table;
};

struct hash_elem_it
{
	struct Table * ht;
	uint32_t index;
	struct hash_elem_t * elem;
};

#define HT_ITERATOR(ht) {ht, 0, ht->table[0]}

uint8_t GetEspecificoElemento(struct Lista * lista, uint16_t fila, uint16_t len, struct data * datos);
uint8_t GetElemento(uint8_t * valor, struct Table * hash, uint16_t fila, uint16_t len, struct data * datos);
uint16_t GetListaElementos(uint8_t * valor, struct Table * hash);
uint16_t ElementoLen(struct Lista * lista);
void destroy_list(struct Lista * current);
struct Lista * get_node(uint8_t * elemento);
void InsertValor(struct Lista * list, uint8_t * elemento);
struct Lista * init_lista();
void PrintElementos(struct Lista * lista, uint16_t len, uint8_t flag);
uint8_t ListarElementos(struct Table * hash, uint8_t * key, uint8_t flag);
uint8_t AgregarElemento(struct Table * hash, uint8_t * key ,uint8_t * elemento);
struct Table * ht_create(uint32_t size);
uint32_t ht_calc_hash(uint8_t * key);
uint8_t AgregarIteracionColumna(struct Table * hash, uint8_t * key);
uint8_t AgregarColumna(struct Table * hash, uint8_t * key);
void * ht_remove(struct Table * hash, uint8_t * key);
uint8_t ht_get(struct Table * hash, uint8_t * key);
struct hash_elem_t * ht_iterate(struct hash_elem_it * iterator);
uint8_t * ht_iterate_keys(struct hash_elem_it * iterator);
void ht_clear(struct Table * hash, int free_data);
void ht_destroy(struct Table * hash);

#endif
