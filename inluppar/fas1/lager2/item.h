#ifndef __item_h__
#define __item_h__

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "tree.h"

typedef struct item item_t;

typedef struct storage storage_t;

typedef struct action action_t;

action_t *action_new(void);

/// undo changes
///
/// \param tree pointer to tree
/// \param action pointer to action
void undo_changes(tree_t *tree, action_t *action);

/// free an item
///
/// \param item pointer to item
void item_free(item_t *item);

/// get shelf
///
/// \param storage pointer to storage
/// \returns: shelf
char *get_shelf(storage_t *storage);

/// get amount
///
/// \param storage pointer to storage
/// \returns: amount
int get_amount(storage_t *storage);

/// make storage
///
/// \param shelf name of shelf
/// \param amount amount
/// \returns: storage
storage_t *make_storage(char *shelf, int amount);

/// get storage for adding an item
///
/// \param item pointer to item
/// \param index index
/// \returns: storage
storage_t *get_storage_add(item_t *item, int index);

/// get name of item
///
/// \param item pointer to item
/// \returns name of item
char *get_name(item_t *item);

/// length of item list
///
/// \param item pointer to item
/// \returns: list length
int item_list_length(item_t *item);

/// get shelf number
///
/// \param item pointer to item
/// \param index index
/// \returns: shlef number
char *get_shelf_nr(item_t *item, int index);

/// get amount of storage
///
/// \param item pointer to item
/// \param index index
/// \returns: amount of storage
int *get_storage_amount(item_t *item, int index);

/// get description of item
///
/// \param item pointer to item
/// \returns: description of item
char *get_description (item_t *item);

/// get price of item
///
/// \param item pointer to item
/// \returns: price
int get_price (item_t *item);

//int get_amount_from_item(item_t *item);

/// make an item
///
/// \param name item name
/// \param desc item description
/// \param price item price
/// \param storage item storage
/// \returns: item with info
item_t *make_item(char *name, char *desc, int price, storage_t *storage);

/// Extract list of items
///
/// \param item pointer to item
/// \returns: a item list
list_t *get_item_list(item_t *item);

/// put an item on shelf
///
/// \param name item name
/// \param desc item description
/// \param price item price
/// \param shelf item shelf
/// \param amount item amount
/// \returns: an item that is placed on shelf
item_t *item_on_shelf(char *name, char *desc, int price, char *shelf, int amount);

/// questions for creating an item
///
/// \returns: an item
item_t *input_item();

/// print info about an item
///
/// \param item pointer to item
void print_item(item_t *item);

/// print a storage list
///
/// \param list pointer to list
void print_list_storage(list_t *list);

/// edit item name
///
/// \param item pointer to item
/// \returns: an name-edited item
item_t *edit_item_name(item_t *item);

/// edit item description
///
/// \param item pointer to item
/// \returns: an edited item
item_t *edit_item_desc(item_t *item);

/// edit item price
///
/// \param item pointer to item
/// \returns: an edited item
item_t *edit_item_price(item_t *item);

/// edit item storage
///
/// \param tree pointer to tree
/// \param item pointer to item
/// \returns: edited item
item_t *edit_item_storage(tree_t *tree, item_t *item);

/// print current amount of an item
///
/// \param item pointer to item
/// \param index item index
void  print_current_amount(item_t *item, int index);

/// increase amount of item
///
/// \param item pointer to item
/// \param index item index
/// \param add_amount amount that you wanna increase
/// \returns: an item that has increased amount
item_t *increase_item_amount(item_t *item, int index, int add_amount);

/// get item name
///
/// \param item pointer to item
/// \returns: item name
char *get_item_name(item_t *item);

/// copy an item
///
/// \param item pointer to item
/// \returns: a copy of an item
item_t *copy_item(item_t *item);

/// check if an specific item in the tree
///
/// \param db pointer to tree
/// \param name item name
/// \returns: true or false
bool is_item_in_db(tree_t *db, char *name) ;

/// a list of shelves
///
/// \param db pointer to tree
/// \returns: a list
list_t *extract_shelves(tree_t *db);

/// amount of pages
///
/// \param length length of list
/// \returns: amount of pages
int amount_of_pages(int length);

/// get a void pointer that points an item
///
/// \param db pointer to tree
/// \param name item name
/// \returns: a void pointer to an item data
void *item_spec(tree_t *db, char *name);

/// display data of an item
///
/// \param tree pointer to tree
/// \param keys pointer to list of keys
/// \param item_index index
/// \returns: an item
item_t *display_item(tree_t *tree, list_t *keys, int item_index);

/// get item from a tree
///
/// \param tree pointer to tree
/// \param keys pointer to list of keys
/// \param item_index index
/// \returns: an item
item_t *get_item(tree_t *tree, list_t *keys, int item_index);

/// loop for edit menu
///
/// \param db pointer to tree
/// \param item pointer to item
/// \returns: true or false
bool edit_menu_loop(tree_t *db, item_t *item);

/// helper for listing items
///
/// \param db pointer to tree
/// \param index index of item
/// \param page page number
/// \returns: true or false
bool aux_list_items(tree_t *db, int index, int page);

/// list items
///
/// \param db pointer to tree
void list_items(tree_t *db);

/// remove an item
///
/// \param db pointer to tree
void remove_item(tree_t *db);

/// check if a specific shelf is taken or not
///
/// \param db pointer to tree
/// \param shelf shelf name
/// \returns: true or false
bool is_shelf_taken_add(tree_t *db, char *shelf);

/// ask questions for a new item
///
/// \param name item name
/// \param shelf item shelf
/// \returns: a new item with info
item_t *ask_new_item_desc_price_amount(char *name, char *shelf);

/// change action to add an item
///
/// \param item pointer to item
/// \param action pointer to action
void change_action_to_add_item(item_t *item, action_t *action);

/// ask for adding new item
///
/// \param db pointer to tree
/// \param item pointer to item
/// \param action pointer to action
void ask_add_new_item(tree_t *db, item_t *item, action_t *action);

/// change action for editing storage
///
/// \param item pointer to item
/// \param index index of item
/// \param add_amount amount for adding
/// \param action pointer to action
void change_action_to_edit_storage(item_t *item, int index, int add_amount, action_t *action);

/// ask question for adding amount for a specific shelf
///
/// \param item pointer to item
/// \param action pointer to action
void ask_add_amount_to_given_shelf(item_t *item, action_t *action);

/// change action for adding storage
///
/// \param current pointer to current item
/// \param action pointer to action
void change_action_to_add_storage(item_t *current, action_t *action);

/// ask question for adding a new shelf for a current item
///
/// \param current pointer to current item
/// \param item_list pointer to item list
/// \param shelf shelf name
/// \param action pointer to action
void ask_add_new_shelf_to_current_item(item_t *current, list_t *item_list, char *shelf, action_t *action);

/// Add a new item to tree
///
/// \param db pointer to tree
/// \param name item name
/// \param action pointer to action
void add_new_item_to_db(tree_t *db, char *name, action_t *action);

/// ask question for a new storage for a specific item
///
/// \param db pointer to tree
/// \param name item name
/// \param action pointer to action
void ask_new_storage_to_item(tree_t *db, char *name, action_t *action);

/// add new shelf or increase amount for a specific item
///
/// \param db pointer to tree
/// \param name item name
/// \param action pointer to action
void add_new_shelf_or_increase_amount_to_item(tree_t *db, char *name, action_t *action);

/// Aaa an item
///
/// \param db pointer to tree
/// \param action pointer to action
void add_goods(tree_t *db, action_t *action);




#endif
