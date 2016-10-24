#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "item.h"
#include "utils.h"
#include "list.h"

typedef struct item item_t;

typedef struct storage storage_t;

struct item    // tree
{
  char *name;
  char *description;
  int price;
  storage_t *storage;   //storage
  list_t *list; // lista med storage
};

struct storage
{
  char *shelf;    // hyllnummer
  int amount;
};

storage_t *make_storage(char *shelf, int amount)
{
  storage_t *storage= calloc(1, sizeof(storage));
  if (storage != NULL)
    {
      storage->shelf = shelf;
      storage->amount = amount;
    }
  return storage;
}

void item_free(item_t *item)
{
    if (item != NULL)
    {
        free(item->storage);
        free(item->description);
        free(item->name);
        free(item);
    }
    return;
}


char *get_shelf(storage_t *storage)
{
  return storage->shelf;
}

int get_amount(storage_t *storage)
{
  return storage->amount;
}

int get_amount_from_item(item_t *item)
{
  storage_t *storage = item->storage;
  int amount = storage->amount;
  return amount;
}

storage_t *get_storage(item_t *item)
{
  return item->storage;
}

char *get_name(item_t *item)
{
  char *name = item->name;
  return name;
}

int item_list_length(item_t *item)
{
  return list_length(item->list);
}
  
char *get_shelf_nr(item_t *item, int index)
{
  list_t *list = item->list;
  storage_t *storage = list_get(list, index);
  return storage->shelf;
}

int *get_storage_amount(item_t *item, int index)
{
  list_t *list = item->list;
  storage_t *storage = list_get(list, index);
  return &storage->amount;
}

char *get_description (item_t *item)
{
  char *description = item->description;
  return description;
}

int get_price (item_t *item)
{
  if (item != NULL)
    {
      return item->price;
    }

  else //item == NULL
    {
      return 0;
    }
}

item_t *make_item(char *name, char *desc, int price, storage_t *storage)
{
  item_t *item = calloc(1, sizeof(item_t));
  if (item != NULL)
    {
      item->name = name;
      item->description = desc;
      item->price = price;
      item->list = list_new();
      list_append(item->list, storage);
    }
  return item;
}

list_t *get_item_list(item_t *item)
{
  return item->list;
}

//make item  with shelf location
item_t *item_on_shelf(char *name, char *desc, int price, char *shelf, int amount)
{
  storage_t *storage = make_storage(shelf, amount);
  
  return make_item(name, desc, price, storage);
}


item_t *input_item()
{
  char *name, *desc;
  int price;
  char *shelf;
  int amount;

  name = ask_question_string("Enter the product name?\n");
  
  desc = ask_question_string("Describe the product\n");
  
  price = ask_question_int("Enter the price?\n");
  
  shelf = ask_question_shelf("Enter the shelf nr.\n");

  amount = ask_question_int("Enter the amount\n");

  item_t *item = item_on_shelf(name, desc, price, shelf, amount);

  return item;
}



void print_item(item_t *item)
{
  int q, r; //qutient, remainder
  q = (item->price)/100;
  r = (item->price)%100;
  char *name = item->name;
  char *description = item->description;
  
 
 

  printf("\n"
         "Name: %s\n"
         "Description: %s\n"
         "Price: %d.%d kr\n"
         "Shelf:\t\tAmount:\n",
         name, description, q, r);
  print_list_storage(item->list);
}

void print_list_storage(list_t *list)
{
  int len = list_length(list);

  for(int i = 0; i<len; ++i)
    {
      storage_t *storage = list_get(list, i);

      printf("%d. %s\t\t%d\n", i+1, storage->shelf, storage->amount);
    }
}

item_t *edit_item_name(item_t *item) //Ändra i trädets ordning också?
{
  //print old name
  item_t *old_item = item; //behövs gamla item för att ångra?
  char *old_name = old_item->name;
  printf("\nCurrent name: %s\n", old_name);
  printf("--------------------------------------------------------\n");
  // ask for new name
  char *new_name = ask_question_string("Enter new name: ");
  
  item->name = new_name;
  printf("\nNew name is: %s\n", new_name);
  return item;
}

item_t *edit_item_desc(item_t *item)
{
  //print old description
  item_t *old_item = item;
  char *old_desc = old_item->description;
  printf("\nCurrent description: %s\n", old_desc);
  printf("--------------------------------------------------------\n");
  //ask for new description
  char *new_desc = ask_question_string("Enter new description: ");
  //insert new description
  item->description = new_desc;
  printf("\nNew description is: %s\n", new_desc);
  return item;
}

item_t *edit_item_price(item_t *item)
{
  //print old price
  item_t *old_item = item;
  int old_price = old_item->price;
  printf("\nCurrent price: %d\n", old_price);
  printf("--------------------------------------------------------\n");
  //ask for new price
  int new_price = ask_question_int("Enter new price: ");
  //insert new price
  item->price = new_price;
  printf("\nNew price is: %d\n", new_price);
  return item;
}

item_t *edit_item_shelf(tree_t *tree, item_t *item)
{
  //print old shelf
  list_t *shelves_taken = list_node_shelf(tree);
  //int length = list_length(shelves_taken);
  item_t *old_item = item;
  char *old_shelf = get_shelf(old_item->storage); //old_item->storage_control->storage_nr;
  printf("\nCurrent shelf: %s\n", old_shelf);
  printf("--------------------------------------------------------\n");
  //ask for new shelf
  char *new_shelf; // = ask_question_shelf("Enter new shelf: ");
  //check if shelf is available
  bool is_shelf_avail;// = is_shelf_taken(new_shelf, shelves_taken);
  do
    {
      new_shelf = ask_question_shelf("Enter new shelf: ");
      is_shelf_avail = is_shelf_taken(new_shelf, shelves_taken);
      if(is_shelf_avail == true)
        {
          printf("Shelf %s is already taken\n", new_shelf);
        }
    }
  while(is_shelf_avail);
  
  //insert new shelf
  item->storage->shelf = new_shelf;
  printf("\nNew shelf is: %s\n", new_shelf);
  return item;
}

item_t *edit_item_amount(item_t *item)
{
  //print old amount
  item_t *old_item = item;
  int old_amount = get_amount(old_item->storage); //old_item->storage_control->amount;
  printf("\nCurrent amount: %d\n", old_amount);
  printf("--------------------------------------------------------\n");
  //ask for new amount
  int new_amount = ask_question_int("Enter new amount: ");
  //insert new amount
  item->storage->amount = new_amount;
  printf("\nNew amount is: %d\n", new_amount);
  return item;
}

void  print_current_amount(item_t *item, int index)
{
   int *old_amount = get_storage_amount(item, index); 
   printf("\nCurrent amount: %d\n", *old_amount);
   printf("--------------------------------------------------------\n");
}

// increase item amount and display item
item_t *increase_item_amount(item_t *item, int index, int add_amount)
{
    int *old_amount = get_storage_amount(item, index); 
    
    *old_amount = *old_amount + add_amount;
    int new_amount = *old_amount;
    printf("\nNew amount is: %d\n", new_amount);
    return item;
}

char *get_item_shelf(item_t *item)
{
  char *shelf;
  
  shelf = item->storage->shelf;
  return shelf;
}



char *get_item_name(item_t *item)
{
  char *name = item->name;
  return name;
}

item_t *copy_item(item_t *item)
{
  if (item == NULL)
    {
      return NULL;
    }

  else // item != NULL
    {
      char *original_name = get_item_name(item);
      char *copy_name = strdup(original_name);

      char *original_description = get_description(item);
      char *copy_description = strdup(original_description);

      int original_price = get_price(item);
      
      char *original_shelf = get_item_shelf(item);
      char *copy_shelf = strdup(original_shelf);

      int original_amount = get_amount_from_item(item);

      item_t *copy = item_on_shelf(copy_name, copy_description, original_price, copy_shelf, original_amount);

      return copy;
      
    }
}










