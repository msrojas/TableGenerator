#include "hash_table.h"

/*
    Este symbol table esta basado en el hash table de Pierre-Henri Symoneaux
    Para mas informacion: https://gist.github.com/phsym/4605704

	(My english is not good)

    This symbol table is based on Pierre-Henri Symoneaux
    More info: https://gist.github.com/phsym/4605704
*/

uint8_t GetEspecificoElemento(struct Lista * lista, uint16_t fila, uint16_t len, struct data * datos)
{
    uint16_t i=0;
    while(lista != NULL)
    {
        if(i == fila)
            break;
        lista = lista->next;
        i++;
    }

    if(lista == NULL)
    {
        if(datos->posicion_flag == OTRA_COLUMNA && datos->style_flag == MYSQL_STYLE)
            printf("%*c", len+3, '|');
        else if(datos->posicion_flag == PRIMERA_COLUMNA && datos->style_flag == MYSQL_STYLE)
            printf("| %*c", len, '|');
        else if(datos->posicion_flag == OTRA_COLUMNA && datos->style_flag == RECTANGULO)
            printf("%*s", len+3, "│");
        else if(datos->posicion_flag == PRIMERA_COLUMNA && datos->style_flag == RECTANGULO)
            printf("│ %*s", len, "│");
    }
    else
    {
        if(datos->posicion_flag == OTRA_COLUMNA && datos->style_flag == MYSQL_STYLE)
            printf(" %s%*c", lista->valor, (len - strlen(lista->valor)) + 2, '|');
        else if(datos->posicion_flag == PRIMERA_COLUMNA && datos->style_flag == MYSQL_STYLE)
            printf("| %s%*c", lista->valor, len - strlen(lista->valor), '|');
        else if(datos->posicion_flag == OTRA_COLUMNA && datos->style_flag == RECTANGULO)
            printf(" %s%*s", lista->valor, (len - strlen(lista->valor)) + 2, "│");
        else if(datos->posicion_flag == PRIMERA_COLUMNA && datos->style_flag == RECTANGULO)
            printf("│ %s%*s", lista->valor, len - strlen(lista->valor), "│");
    }

    return 1;
}

uint8_t GetElemento(uint8_t * valor, struct Table * hash, uint16_t fila, uint16_t len, struct data * datos)
{
    uint32_t h = ht_calc_hash(valor) % hash->columna;
    struct hash_elem_t * e = hash->table[h];

    while(e != NULL)
    {
        if(strcmp(valor, e->column_name) == 0)
        {
            if(!GetEspecificoElemento(e->Lista_Elementos->next, fila, len, datos))
                return 0;
           
            return 1;
        }
        e = e->next;
    }

    fprintf(stderr, "ERROR: bug en funcion: GetElemento\n");
    return 0;
}

uint16_t GetListaElementos(uint8_t * valor, struct Table * hash)
{
    uint32_t h = ht_calc_hash(valor) % hash->columna;
    struct hash_elem_t * e = hash->table[h];

    while(e != NULL)
    {
        if(strcmp(e->column_name, valor) == 0)
        {
            uint16_t len = strlen(valor);
            uint16_t MaxLen = ElementoLen(e->Lista_Elementos->next);
            if(len > MaxLen)
                MaxLen = len;
            return MaxLen;
        }
        e = e->next;
    }

    fprintf(stderr, "ERROR: bug en funcion: GetListaElementos()\n");
    return 0;
}

uint16_t ElementoLen(struct Lista * lista)
{
    uint16_t len = strlen(lista->valor);
    while(lista != NULL)
    {
        if(strlen(lista->valor) > len)
            len = strlen(lista->valor);  
        lista = lista->next;
    }

    return len;
}

void destroy_list(struct Lista * current)
{
    struct Lista * temp = NULL;
    while(current != NULL)
    {
        temp = current;
        current = current->next;
        WFree(temp->valor);
        free(temp);
    }
}

struct Lista * get_node(uint8_t * elemento)
{
    struct Lista * temp = malloc(sizeof(struct Lista));
    if(temp == NULL)
    {
        printf("Errno: ocurrio un inconveniente en la heap\n");
        return NULL;
    }
	
    temp->valor = WMalloc(elemento);	
    temp->next = NULL;
    return temp;
}

void InsertValor(struct Lista * list, uint8_t * elemento)
{	
    struct Lista * temp = list;
    struct Lista * newNode = get_node(elemento);
    if(newNode == NULL)
        exit(1);
    while(temp->next != NULL)
        temp = temp->next;

    temp->next = newNode;
}

struct Lista * init_lista()
{
    struct Lista * temp = malloc(sizeof(struct Lista));
    if(temp == NULL)
    {
        printf("ERROR: ocurrio un inconveniente en la heap\n");
        return NULL;
    }

    temp->next = NULL;
    return temp;
}

void PrintElementos(struct Lista * lista, uint16_t len, uint8_t flag)
{
    uint16_t diferencia = 0;
    while(lista != NULL)
    {
        diferencia = len - strlen(lista->valor);
        printf("| %s%*c\n",lista->valor, diferencia,'|');
        lista = lista->next;
    }
    PrintMargen(flag, len);
    printf("\n");
}

uint8_t ListarElementos(struct Table * hash, uint8_t * key, uint8_t flag)
{
    uint32_t h = ht_calc_hash(key) % hash->columna;
    struct hash_elem_t * e = hash->table[h];

    while(e != NULL)
    {
        if(strcmp(e->column_name, key) == 0)
        {
            PrintColumna(key, flag,e->Lista_Elementos->next);
            return 1;
        }
        e = e->next;
    }

    fprintf(stderr, "ERROR: El nombre de la columna no existe: %s\n", key);
    return 0;
}

uint8_t AgregarElemento(struct Table * hash, uint8_t * key ,uint8_t * elemento)
{
    uint32_t h = ht_calc_hash(key) % hash->columna;
    struct hash_elem_t * e = hash->table[h];

    while(e != NULL)
    {
        if(strcmp(e->column_name, key) == 0)
        {
            if(e->Lista_Elementos == NULL)
            {
                e->Lista_Elementos = init_lista();
                if(e->Lista_Elementos == NULL)
                    return 0;
            }
			
            InsertValor(e->Lista_Elementos, elemento);
            hash->size_fila++;

            if(hash->size_fila > hash->fila)
            {
                fprintf(stderr, "ERROR: definiste %d filas para la columna %s, pero has sobrepasado ese numero\n", hash->fila, key);
                return 0;
            }

             return 1;
        }

        e = e->next;
    }

    fprintf(stderr, "ERROR: el nombre de la columna no existe: %s\n", key);
    return 0;
}

struct Table * ht_create(uint32_t size)
{
    struct Table * hash = (struct Table *)malloc(sizeof(struct Table));
    if(hash == NULL)
    {
        fprintf(stderr, "ERROR: ocurrio un inconveniente en la heap\n");
        return NULL;
    }

    if((hash->table = malloc(size*sizeof(struct hash_elem_t*))) == NULL)
    {
        free(hash);
        fprintf(stderr, "ERROR: ocurrio un inconveniente en la heap\n");
        return NULL;
    }

    uint32_t i = 0;
    for(i=0;i<size;i++)
    {
        hash->table[i] = NULL;
    }
    return hash;
}

uint32_t ht_calc_hash(uint8_t * key)
{
    uint32_t h = 5381;
    while(*(key++))
        h = ((h << 5) + h) + (*key);

    return h;
}

uint8_t AgregarIteracionColumna(struct Table * hash, uint8_t * key)
{
    if(hash->ListaColumnas == NULL)
    {
        hash->ListaColumnas = init_lista();
        if(hash->ListaColumnas == NULL)
            return 0;
    }

    InsertValor(hash->ListaColumnas, key);

    return 1;
}

uint8_t AgregarColumna(struct Table * hash, uint8_t * key)
{
    uint32_t h = ht_calc_hash(key) % hash->columna;
    struct hash_elem_t * e = hash->table[h];

    while(e != NULL)
    {
        if(strcmp(e->column_name, key) == 0)
        {
            fprintf(stderr,"ERROR: El nombre de la columna ya existe: %s\n", key);
            return 0;
        }

        e = e->next;
    }

    if((e = malloc(sizeof(struct hash_elem_t))) == NULL)
    {
        printf("ERROR: ocurrio un inconveniente en la heap\n");
        return 0;
    }

    e->column_name = WMalloc(key);
    if(e->column_name == NULL)
        return 0;
    hash->size_columna++;

    if(hash->size_columna > hash->columna)
    {
        fprintf(stderr, "ERROR: definiste %d columnas, pero has sobrepasado ese numero\n", hash->columna);
        return 0;
    }

    if(!AgregarIteracionColumna(hash, key))
        return 0;

    e->next = hash->table[h];
    hash->table[h] = e;

    return 1;
}

void * ht_remove(struct Table * hash, uint8_t * key)
{
    uint32_t h = ht_calc_hash(key) % hash->columna;
    struct hash_elem_t * e = hash->table[h];
    struct hash_elem_t * prev = NULL;

    while(e != NULL)
    {
        if(strcmp(e->column_name, key) == 0)
        {
            void * data = e->column_name;

            if(prev != NULL)
                prev->next = e->next;
            else
                hash->table[h] = e->next;
            if(e->Lista_Elementos != NULL)
            {
                destroy_list(e->Lista_Elementos->next);
                free(e->Lista_Elementos);
            }
            free(e);
            e = NULL;
            return data;
        }
        prev = e;
        e = e->next;
    }

    return 0;
}

uint8_t ht_get(struct Table * hash, uint8_t * key)
{
    uint32_t h = ht_calc_hash(key) % hash->columna;
    struct hash_elem_t * e = hash->table[h];

    while(e != NULL)
    {
        if(strcmp(e->column_name, key) == 0)
        {
            printf("Si existe: %s\n", e->column_name);
            return 1;
        }

        e = e->next;
    }

    printf("El nombre de la columna no existe: %s\n", key);
    return 0;
}

struct hash_elem_t * ht_iterate(struct hash_elem_it * iterator)
{
    while(iterator->elem == NULL)
    {
        if(iterator->index < iterator->ht->columna - 1)
        {
            iterator->index++;
            iterator->elem = iterator->ht->table[iterator->index];
        }
        else
            return NULL;
    }

    struct hash_elem_t * e = iterator->elem;
    if(e)
        iterator->elem = e->next;
    return e;
}

uint8_t * ht_iterate_keys(struct hash_elem_it * iterator)
{
    struct hash_elem_t * e = ht_iterate(iterator);
    return(e == NULL ? NULL : e->column_name);
}

void ht_clear(struct Table * hash, int free_data)
{
    struct hash_elem_it it = HT_ITERATOR(hash);
    uint8_t * k = ht_iterate_keys(&it);

    while(k != NULL)
    {
        free_data ? free(ht_remove(hash, k)) : ht_remove(hash, k);
        k = ht_iterate_keys(&it);
    }
}

void ht_destroy(struct Table * hash)
{
    ht_clear(hash, 1);
    if(hash->ListaColumnas != NULL)
    {
        destroy_list(hash->ListaColumnas->next);
        free(hash->ListaColumnas);
    }
    free(hash->table);
    free(hash);
}
