#ifndef __item_h__
#define __item_h__

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

typedef struct item item_t;

typedef struct storage storage_t;


char *get_shelf(storage_t *storage);

int get_amount(storage_t *storage);

storage_t *make_storage(char *shelf, int amount);

char *get_name(item_t *item);

char *get_shelf_nr(item_t *item);

item_t *make_item(char *name, char *desc, int price, storage_t *storage);

item_t *item_on_shelf(char *name, char *desc, int price, char *shelf, int amount);

item_t *input_item();

void print_item(item_t *item);

void print_menu();

item_t *edit_item_name(item_t *item);

item_t *edit_item_desc(item_t *item);

item_t *edit_item_price(item_t *item);

item_t *edit_item_shelf(item_t *item);

item_t *edit_item_amount(item_t *item);

item_t *increase_item_amount(item_t *item);

char *get_item_shelf(item_t *item);

char *get_item_name(item_t *item);




#endif
